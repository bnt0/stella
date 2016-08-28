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
 * MapModel.cc
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#include "MapModel.h"

namespace stellad {

MapModel::MapModel() {
}

MapModel::~MapModel() {
}

stellad::ShortcutDefinition * MapModel::checkForKeys(
    const std::string& currentKeyString) {
  std::string tempS;
  for (int i = 0; i < currentKeyString.length(); i++) {
    tempS = currentKeyString.substr(i);
    std::map<std::string, stellad::ShortcutDefinition>::iterator
        find = mapShortcuts.find(tempS);
    // TODO(brad) Ignore disabled
    if (find != mapShortcuts.end() && find->second.isEnabled()) {
      return new stellad::ShortcutDefinition(find->second);
    }
  }
  return nullptr;
}

void MapModel::insertKey(const stellad::ShortcutDefinition& insertSD) {
  mapShortcuts[insertSD.getKey()] = ShortcutDefinition(insertSD);
}

void MapModel::removeKey(const stellad::ShortcutDefinition& keyDelete) {
  MapModel::mapShortcuts.erase(keyDelete.getKey());
}

std::vector<stellad::ShortcutDefinition>* MapModel::getAllKeys() {
  using stellad::ShortcutDefinition;
  using std::map;
  using std::vector;
  using std::string;
  map<string, ShortcutDefinition>* m = &(this->mapShortcuts);
  vector<ShortcutDefinition>* result
    = new vector<ShortcutDefinition>;
  for (auto it = m->begin(); it != m->end(); ++it) {
    result->push_back(it->second);
  }
  return result;
}

} /* namespace stellad */
