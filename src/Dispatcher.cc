/* Copyright 2016 Bradley Kennedy
 *                                                                              
 * This file is part of Stella.                                                        
 *                                                                                     
 *    Stella is free software: you can redistribute it and/or modify                   
 *    it under the terms of the GNU General Public License as published by             
 *    the Free Software Foundation, either version 3 of the License, or                
 *    (at your option) any later version.                                              
 *                                                                                     
 *    Stella is distributed in the hope that it will be useful,                        
 *    but WITHOUT ANY WARRANTY; without even the implied warranty of                   
 *    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                    
 *    GNU General Public License for more details.                                     
 *                                                                                     
 *    You should have received a copy of the GNU General Public License                
 *    along with Stella.  If not, see <http://www.gnu.org/licenses/>.     
 *
 * Dispatcher.cc
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#include "Dispatcher.h"
#include "FUtils.h"
#include "protoc/command.pb.h"

#include <iomanip>
#include <chrono>
#include <uiohook.h>
#include <vector>

namespace stellad {

const int kWorkingStrMin = 48;
const int kWorkingStrMax = 64;

// Constants for the number of milliseconds to sleep between / after inputs
const int kTimebetweenkey = 0;
const int kTimeafterkey = 0;
const int kTimeafterdel = 0;

Dispatcher::Dispatcher() : currStatus(stellad::StatusDis::Ready) {
  configGlobal = stellad::utils::findConfig();

  configGlobal += "stellad/";
  std::cout << "Using configuration directory " << configGlobal << std::endl;
  mkdir(configGlobal.c_str(), 0755);
  if (utils::file_exists(configGlobal + "stellad-keys.json")) {
    dataStore.loadKeysFromFile(configGlobal + "stellad-keys.json");
  } else {
    // Makes new file
    dataStore.saveKeysFromFile(configGlobal + "stellad-keys.json");
  }

  pipeReader = new PipeReader(configGlobal + "control-pipe");
}

Dispatcher::~Dispatcher() {
  delete pipeReader;
}

void Dispatcher::tick() {
  pipeReader->readAll();
  if (pipeReader->ready) {
    manageSettings();
    pipeReader->ready = false;
  }
  std::vector<keyboard_event_data>* buffer = keyHook.getBuffer();
  for (std::vector<keyboard_event_data>::iterator it = buffer->begin();
       it != buffer->end(); ++it) {
    workingString += keyHook.keyToMacroCode((*it));
    using stellad::kWorkingStrMin;
    using stellad::kWorkingStrMax;
    // If the workingString is greater then max, cut it down to the min length
  }
  if (workingString.length() > kWorkingStrMax) {
    workingString =
        workingString.substr(workingString.length() - kWorkingStrMin);
  }
  stellad::ShortcutDefinition* found = dataStore.checkForKeys(workingString);

  using stellad::kTimeafterkey;
  using stellad::kTimebetweenkey;
  using stellad::kTimeafterdel;
  if (keyHook.keysDown() && found != nullptr) {
    std::cout << "You typed " << found->getKey() << " -> "
        << found->getValue() << std::endl;  // Debug code will change to log
    robot.typeString(std::string(found->getKey().length(), '\b'), 0, 0);
    std::this_thread::sleep_for(std::chrono::milliseconds(kTimeafterdel));
    robot.typeString(found->getValue(), kTimebetweenkey, kTimeafterkey);
    delete found;
    workingString.clear();
  }
  delete buffer;
}

void Dispatcher::manageSettings() {
  stellad::proto::Control * temp = pipeReader->getCommandBuff();
  std::cout << "We recieved a message" << std::endl;
  if (temp == nullptr) return;
  switch (temp->action()) {
    case stellad::proto::Control::OTHER:
      break;
    case stellad::proto::Control::SHUTDOWN:
      std::cout << "Received command to SHUTDOWN" << std::endl;
      break;
    case stellad::proto::Control::RELOAD:
      std::cout << "Received command to RELOAD" << std::endl;
      dataStore.loadKeysFromFile(configGlobal + "stellad-keys.json");
      break;
    case stellad::proto::Control::IGNORE:
      std::cout << "Received command to IGNORE" << std::endl;
      currStatus = (currStatus == StatusDis::Ready ? StatusDis::Ignore :
          StatusDis::Ready);
      break;
    case stellad::proto::Control::STATUS: {
      std::cout << "Received command to STATUS" << std::endl;
      stellad::proto::Control * msgs = new stellad::proto::Control();
      msgs->set_action(stellad::proto::Control::STATUS);
      if (currStatus == StatusDis::Ignore)
        msgs->set_status(false);
      sendResponse(configGlobal + "callback-pipe", msgs->SerializeAsString());
      delete msgs;
      break;
    }
    case stellad::proto::Control::SAVE:
      std::cout << "Received command to SAVE" << std::endl;
      dataStore.saveKeysFromFile(configGlobal + "stellad-keys.json");
      break;
    case stellad::proto::Control::LIST:
      stellad::proto::Control * msgc = allShortcutsandSettings();
      sendResponse(configGlobal + "callback-pipe", msgc->SerializeAsString());
      delete msgc;
      break;
  }
  for (int i = 0; i < temp->shortcuts_size(); ++i) {
    const stellad::proto::ShortcutDefinition * copy = &(temp->shortcuts(i));
    switch (copy->action()) {
      case stellad::proto::ADD:
        dataStore.insertKey(stellad::ShortcutDefinition(
            copy->key(), copy->value(),
            copy->has_enabled() ? copy->enabled() : false,
            copy->has_mode() ? copy->mode() : MODE_DEFAULT));
        std::cout << "Added a shortcut definition with \"" << copy->key() <<
            "\" -> \"" << copy->value() << "\"" << std::endl;
        break;
      case stellad::proto::REM:
        dataStore.removeKey(stellad::ShortcutDefinition(
            copy->key(), copy->value(),
            copy->has_enabled() ? copy->enabled() : false,
            copy->has_mode() ? copy->mode() : MODE_DEFAULT));
        std::cout << "Removed a shortcut definition with \"" << copy->key() <<
            "\"" << std::endl;
        break;
      case stellad::proto::MODIFY:
        // Remove old key
        dataStore.removeKey(stellad::ShortcutDefinition(
            copy->key(), copy->value(),
            copy->has_enabled() ? copy->enabled() : false,
            copy->has_mode() ? copy->mode() : MODE_DEFAULT));
        // Add new key
        dataStore.insertKey(stellad::ShortcutDefinition(
            copy->key(), copy->value(),
            copy->has_enabled() ? copy->enabled() : false,
            copy->has_mode() ? copy->mode() : MODE_DEFAULT));
        break;
      default:
        std::cerr << "Action was not one specified by the protocol"
            << std::endl;
        break;
    }
  }
  // TODO(brad)  Memory leak here if settings are sent, commented for now
  // for (int i = 0; i < temp->settings_size(); ++i) {
  //  const stellad::proto::Setting * copy = &(temp->settings(i));
  //  // TODO(brad) We need an interface for settings changes, ignore for now
  //}
  delete temp;
  std::cout << "Returning to main loop" << std::endl;
}

bool Dispatcher::sendResponse(const std::string& filename,
                              const std::string& streamstring) {
  if (!stellad::utils::pipe_exists(filename)) {
    std::cerr << "Unable to find pipe in config directory: " << filename
        << std::endl;
    return false;
  }
  std::ofstream pipectrl;
  pipectrl.open(filename, std::ios::out | std::ios::binary);
  if (pipectrl.is_open()) {
    pipectrl << streamstring;
    pipectrl.close();
  } else {
    std::cerr << "Pipe failed to open" << std::endl;
    return false;
  }
  return true;
}

stellad::proto::Control * Dispatcher::allShortcutsandSettings() {
  stellad::proto::Control * result = new stellad::proto::Control();
  const std::vector<ShortcutDefinition> * allkeys = dataStore.getAllKeys();
  result->set_action(::stellad::proto::Control_SysAction_RESPONSE);

  for (std::vector<ShortcutDefinition>::const_iterator it = allkeys->begin();
       it != allkeys->end(); ++it) {
    stellad::proto::ShortcutDefinition * newsd = result->add_shortcuts();
    newsd->set_action(::stellad::proto::Action::MODIFY);
    newsd->set_key(it->getKey());
    newsd->set_value(it->getValue());
    newsd->set_enabled(it->isEnabled());
    // TODO(brad) change this if we add more modes
    newsd->set_mode(::stellad::proto::ShortcutDefinition_Mode_DEFAULT);
  }
  // TODO(brad) no settings for now, probably should just copy map
  // for (std::map<const std::string, std::string> it = )
  delete allkeys;
  return result;
}

void Dispatcher::endDaemon() {
}

void Dispatcher::startDaemon() {
  std::cout << "Setting up Hook." << std::endl;
  keyHook.setHook();
  std::cout << "Hook set." << std::endl;
}

} /* namespace stellad */
