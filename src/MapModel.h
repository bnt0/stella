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
 * MapModel.h
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#ifndef SRC_MAPMODEL_H_
#define SRC_MAPMODEL_H_

#include <string>
#include <vector>
#include <iostream>
#include <map>

#include "ShortcutDefinition.h"

namespace stellad {
//! MapModel manages the ShortcutDefinition and provides search operations
//! for the working string
class MapModel {
  std::map<std::string, stellad::ShortcutDefinition> mapShortcuts;
 public:
  MapModel();
  MapModel(const MapModel& clone);
  virtual ~MapModel();

  //! Supply long string and we find the best matching string (longest)
  //! \return first ShortcutDefinition we find
  stellad::ShortcutDefinition* checkForKeys(
      const std::string& currentKeyString);

  //! insertSD ShortcutDefinition to add into the MDM
  void insertKey(const stellad::ShortcutDefinition& insertSD);

  //! keyDelete ShortcutDefinition to remove from the MDM by key
  void removeKey(const stellad::ShortcutDefinition& keyDelete);

  //! \returns a vector copy of all the keys in the store
  std::vector<stellad::ShortcutDefinition>* getAllKeys();
};

} /* namespace stellad */

#endif  // SRC_MAPMODEL_H_
