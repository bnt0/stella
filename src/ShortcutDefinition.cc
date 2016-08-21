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
 * ShortcutDefinition.cc
 *
 *  Created on: Apr 28, 2015
 *      Author: brad
 */

#include "ShortcutDefinition.h"

namespace stellad {
ShortcutDefinition::ShortcutDefinition(
      const std::string& key, const std::string& value,
      const bool& enabled, const int& mode) {
  this->mode = mode;
  this->enabled = enabled;
  this->key = key;
  this->value = value;

}

ShortcutDefinition::ShortcutDefinition(const ShortcutDefinition & clone){
  key = clone.key;
  value = clone.value;
  enabled = clone.enabled;
  mode = clone.mode;
}

ShortcutDefinition::ShortcutDefinition() {
  key = "";
  value = "";
  enabled = false;
  mode = MODE_DEFAULT;
}

const std::string& ShortcutDefinition::getKey() const {
  return key;
}

bool ShortcutDefinition::isEnabled() const {
  return enabled;
}

int ShortcutDefinition::getMode() const {
  return mode;
}

const std::string& ShortcutDefinition::getValue() const {
  return value;
}

ShortcutDefinition::~ShortcutDefinition() {
}

} /* namespace stellad */
