 /*                                                                              
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
 * ModularDataModel.cc
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#include "ModularDataModel.h"

namespace stellad {

ModularDataModel::ModularDataModel() {
}

ModularDataModel::~ModularDataModel() {
}

stellad::ShortcutDefinition* ModularDataModel::checkForKeys(
    const std::string& currentKeyString) {
    return memMod.checkForKeys(currentKeyString);
}

void ModularDataModel::insertKey(const stellad::ShortcutDefinition& insertSD) {
  memMod.insertKey(insertSD);
}

void ModularDataModel::removeKey(const stellad::ShortcutDefinition& keyDelete) {
  memMod.removeKey(keyDelete);
}

const std::vector<ShortcutDefinition>* ModularDataModel::getAllKeys() {
  return memMod.getAllKeys();
}

const void ModularDataModel::loadKeysFromFile(const std::string& fileLocation) {
  using std::vector;
  using stellad::ShortcutDefinition;
  vector<ShortcutDefinition> shortcuts;

  // Clear old settings
  memMod = stellad::MapModel();
  settings = std::map<const std::string, std::string>();
  // Load new settings from file
  fileMod.loadFromFile(fileLocation, shortcuts, settings);
  for (vector<ShortcutDefinition>::iterator it = shortcuts.begin();
       it != shortcuts.end(); ++it) {
    insertKey(*it);
  }
}

const void ModularDataModel::saveKeysFromFile(const std::string& fileLocation) {
    fileMod.saveToFile(fileLocation, memMod.getAllKeys(), settings);
}

} /* namespace stellad */
