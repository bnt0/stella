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
 * JSONFileModel.cc
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#include "JSONFileModel.h"

namespace stellad {

JSONFileModel::JSONFileModel() {
}

JSONFileModel::~JSONFileModel() {
}

void JSONFileModel::loadFromFile(
    const std::string& fileLocation,
    std::vector<stellad::ShortcutDefinition>& saveableShortcuts,
    std::map<const std::string, std::string>& settings) {
  Json::Value root;
  Json::Reader reader;
  Json::Value settArray;
  Json::Value shortcuts;

  std::ifstream file(fileLocation, std::ifstream::binary);
  bool parsingSuccessful = reader.parse(file, root);
  if (!parsingSuccessful) {
    // report to the user the failure and their locations in the document.
    std::cerr  << "Failed to parse configuration\n"
               << reader.getFormattedErrorMessages() << std::endl;
  }
  settArray = root["settings"];
  shortcuts = root["shortcuts"];

  // Load definitions
  if (shortcuts != 0) {
    for (int index = 0; index < shortcuts.size(); ++index) {
      stellad::ShortcutDefinition temp = stellad::ShortcutDefinition(
          shortcuts[index]["key"].asString(),
          shortcuts[index]["value"].asString(),
          shortcuts[index]["enabled"].asBool(),
          shortcuts[index]["mode"].asInt());
      saveableShortcuts.push_back(temp);
    }
  }
  // Load settings
  if (settArray != 0) {  // Not sure if this is requred
    std::string settingName;
    for (int index = 0; index < shortcuts.size(); ++index) {
      if (!settArray[index].getMemberNames().empty()) {
        settingName = settArray[index].getMemberNames()[0];
        settings[settingName] = settArray[index][settingName].asString();
      }
    }
  }
}

void JSONFileModel::saveToFile(
    const std::string& fileLocation,
    std::vector<stellad::ShortcutDefinition>* saveableShortcuts,
    std::map<const std::string, std::string> settings) {
  using std::map;
  using std::vector;
  using std::string;
  using std::ofstream;
  using stellad::ShortcutDefinition;

  Json::Value root;
  Json::Value settArray;
  Json::Value shortcuts;

  for (map<const string, string>::iterator it = settings.begin();
       it != settings.end(); ++it) {
    Json::Value sets = Json::Value();
    sets[it->first] = it->second;
    settArray.append(sets);
  }

  for (vector<ShortcutDefinition>::iterator it = saveableShortcuts->begin();
       it != saveableShortcuts->end(); ++it) {
    Json::Value sets = Json::Value();
    sets["key"] = it->getKey();
    sets["value"] = it->getValue();
    sets["mode"] = it->getMode();
    sets["enabled"] = it->isEnabled();
    shortcuts.append(sets);
  }

  root["formatVersion"] = "1.0";
  root["settings"] = settArray;
  root["shortcuts"] = shortcuts;

  Json::StyledWriter styledWriter;

  ofstream file;
  file.open(fileLocation.c_str());
  file << styledWriter.write(root);
  file.close();
}

} /* namespace stellad */
