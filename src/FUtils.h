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
 * FUTils.h
 *
 *  Created on: 2015-10-15
 *      Author: brad
 */


#ifndef SRC_FUTILS_H_
#define SRC_FUTILS_H_

#include <string>
#include <sstream>
#include <sys/stat.h>
#include <unistd.h>  // Homedir
#include <sys/types.h>  // Homedir
#include <pwd.h>  // Homedir

namespace stellad {
namespace utils {

  // Finds the config directory
  // @return a string containing the config directory, or "/"
  std::string findConfig();

  // Checks if a pipe exists
  // @param filename path to the file to check.
  // @return true if the folder exists, false otherwise.
  bool pipe_exists(std::string pipename);

  // Checks if a file exists
  // @param filename path to the file to check.
  // @return true if the folder exists, false otherwise.
  bool file_exists(std::string foldername);

  // Checks if a folder exists
  // @param foldername path to the folder to check.
  // @return true if the folder exists, false otherwise.
  bool folder_exists(std::string foldername);
} /* namespace utils */
} /* namespace stellad */

#endif  // SRC_FUTILS_H_
