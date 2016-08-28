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
 * ModularDataModel.h
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#ifndef SRC_MODULARDATAMODEL_H_
#define SRC_MODULARDATAMODEL_H_

#include <iostream>
#include "ShortcutDefinition.h"
#include "MapModel.h"
#include "JSONFileModel.h"

namespace stellad {

// Handles JSONFileModel and MapModel interactions middle man
class ModularDataModel {
 private:
    JSONFileModel fileMod;
    MapModel memMod;
    std::map<const std::string, std::string> settings;

 public:
  ModularDataModel();
  ~ModularDataModel();

  // Returns a pointer to a Shortcut defintion after searching the store
  // currentKeyString is searched fully for substrings that contain any key
  stellad::ShortcutDefinition* checkForKeys(const std::string&
      currentKeyString);

  // Insert the key into the memory map
  // insertSD we copy the SD into the mm
  void insertKey(const stellad::ShortcutDefinition& insertSD);

  // Based on the keyDelete.key field we delete from the mm
  void removeKey(const stellad::ShortcutDefinition& keyDelete);

  // Pass up a vector copy up to display
  const std::vector<ShortcutDefinition>* getAllKeys();

  // Access the JSONFileModel and load the keys from the fileLocation
  const void loadKeysFromFile(const std::string& fileLocation);

  // Access the JSONFileModel and save the keys to the fileLocation
  const void saveKeysFromFile(const std::string& fileLocation);
};

} /* namespace stellad */

#endif  // SRC_MODULARDATAMODEL_H_
