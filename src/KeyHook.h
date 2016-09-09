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
 * KeyHook.h
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#ifndef SRC_KEYHOOK_H_
#define SRC_KEYHOOK_H_
#include <string>
#include <vector>
#include <mutex>
#include <thread>
#include <inttypes.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <uiohook.h>
#include <algorithm>

extern std::mutex keyboard_queue_mutex;
extern std::vector<keyboard_event_data> keyboard_queue;

namespace stellad {
//! Hooks to the keyboard of the user in order to transfer data back to the
//! dispatcher, also maintains a thread to prevent blocking
class KeyHook {
 public:
  KeyHook();
  virtual ~KeyHook();

  //! Converts the keyboard_event_data struct from the uiohook lib to strings
  virtual std::string keyToMacroCode(keyboard_event_data key);

  //! Gets a vector buffer of keys
  virtual std::vector<keyboard_event_data>* getBuffer();
  virtual bool keysDown();
  static void runHook(KeyHook* kh);
  //! Sets up the uiohook on the back end and starts the threadHook thread
  virtual int setHook();

 private:
  //> Buffer of keyboard_keys
  std::vector<keyboard_event_data> transfer_queue;
  //> Thread to maintain for the backend stuff
  std::thread threadHook;
};


} /* namespace stellad */
extern bool lastReleased;
void dispatch_proc(uiohook_event* const event);
bool logger_proc(unsigned int level, const char *format, ...);

#endif  // SRC_KEYHOOK_H_
