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
 * JSONFileModel.h
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#ifndef SRC_JSONFILEMODEL_H_
#define SRC_JSONFILEMODEL_H_

#include "ShortcutDefinition.h"

#include <string>
#include <vector>
#include <map>

namespace stellad {
//! JSONFileModel provides functions to write MDM data to a file or read it
class JSONFileModel {
 public:
  JSONFileModel();
  virtual ~JSONFileModel();

  //! Loads ModularDataModel data into the provided objects
  //! \param fileLocation [in] the full path to the file the we are to load
  //! \param saveableShortcuts [out] 
  //!        the shortcuts to be loaded from the JSON file
  //! \param settings [out]
  //!        settings to be loaded from the JSON file
  //! \returns whether loading and parsing was successful
  bool loadFromFile(  // TODO(brad) make these either const ref or pointer
    const std::string& fileLocation,
    std::vector<stellad::ShortcutDefinition>& saveableShortcuts,
    std::map<const std::string, std::string>& settings);

  //! Save ModularDataModel data into the provided objects
  //! \param [in] fileLocation the full path to the file the we are to load
  //! \param [in] saveableShortcuts the shortcuts to be copied into the json file
  //! \param [in] settings settings to be copied into the json file
  //! \returns whether writing to file was successful
  bool saveToFile(const std::string& fileLocation,
                  const std::vector<stellad::ShortcutDefinition>* saveableShortcuts,
                  const std::map<const std::string, std::string>& settings);
};

} /* namespace stellad */

#endif  // SRC_JSONFILEMODEL_H_
