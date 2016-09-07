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
 * FUTils.cc
 *
 *  Created on: 2015-10-15
 *      Author: brad
 */

#include "FUtils.h"

namespace stellad {
namespace utils {

  std::string findConfig() {
    std::string configdir;
    // This codebase was meant to be multiplatform, but that fell out
    // You can see some remnants here
    #ifdef __linux__
    char *xdgconf = getenv("XDG_CONFIG_HOME");
    if (xdgconf == nullptr) {
      xdgconf = getenv("HOME");
      if (xdgconf != nullptr) {
        configdir = std::string(xdgconf) + "/.config/";
      }
    }
    if (xdgconf == nullptr) {
      // TODO(brad) cpplint recommended using getpwuid_r here
      struct passwd *pw = getpwuid(getuid());
      const char *homedir = pw->pw_dir;
      configdir = std::string(homedir) + "/.config/";
    }
    #endif /*__linux__*/
    return configdir;
  }

  bool pipe_exists(std::string pipename) {
    struct stat st;
    stat(pipename.c_str(), &st);
    return ((st.st_mode & S_IFMT) == S_IFIFO);
  }

  bool file_exists(std::string filename) {
    struct stat st;
    stat(filename.c_str(), &st);
    return ((st.st_mode & S_IFMT) == S_IFREG);
  }

  bool folder_exists(std::string foldername) {
    struct stat st;
    stat(foldername.c_str(), &st);
    return st.st_mode & S_IFDIR;
  }

} /* namespace utils */
} /* namespace stellad */
