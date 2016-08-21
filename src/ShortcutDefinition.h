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
 * ShortcutDefinition.h
 *
 *  Created on: Apr 28, 2015
 *      Author: brad
 */

#ifndef SHORTCUTDEFINITION_H_
#define SHORTCUTDEFINITION_H_

#include <string>

namespace stellad {

const int MODE_DEFAULT = 0;

// Just a bunch of data, immutable so thats cool
class ShortcutDefinition {
  std::string key;
  std::string value;
  bool enabled;
  int mode;
public:
  ShortcutDefinition(const std::string& key, const std::string& value,
                     const bool& enabled, const int& mode);
  ShortcutDefinition(const ShortcutDefinition & clone);
  ShortcutDefinition();
  virtual ~ShortcutDefinition();

  const std::string& getKey() const;
  const std::string& getValue() const;
  bool isEnabled() const;
  int getMode() const;
};

} /* namespace stellad */

#endif /* SHORTCUTDEFINITION_H_ */
