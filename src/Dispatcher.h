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
 * Dispatcher.h
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#ifndef SRC_DISPATCHER_H_
#define SRC_DISPATCHER_H_

#include "KeyHook.h"
#include "ModularDataModel.h"
#include "PipeReader.h"
#include "RobotCommon.h"

#include <string>

namespace stellad {
extern const int kWorkingStrMin;
extern const int kWorkingStrMax;

enum StatusDis {
  Ready, Ignore,
};

/*!
 * Dispatcher handles all the data interactions between the different components
 * Holds all children classes as members, maintains the mainloop tick();
 */
class Dispatcher {
 public:
  //! Gets the configuration, if it can't find it, it builds the directory
  //! structure, then it makes or read stellad-keys.json file and builds a
  //! new PipeReader
  Dispatcher();

  //! Cleans up pointer member objects
  virtual ~Dispatcher();

  //! Checks if the PipeReader has a stream and calls manageSettings if it does
  //! gets KeyHook buffer and chekcs it against the datastore if we find anything
  //! we use the robot to type the string to the screen
  void tick();

  //! Set the PipeReader to end, and then attempt to join the thread back
  void endDaemon();

  //! Set the KeyHook and then spawns a PipeReader thread
  void startDaemon();

 private:

  //! Polls the PipeReader for the command buffer pointer
  //! If the Control buffer is a SysAction from stellad::proto then performs
  //! the next action. Then it takes any shortcut, or settings options
  //! and it inserts them into the ModularDataModel
  void manageSettings();

  //! \param [in] filename   the full path to the pipe
  //! \returns true if the response was sent
  bool sendResponse(const std::string& filename, 
                    const std::string& streamstring);

  //! Returns a new Control object with all the settings in it
  stellad::proto::Control * allShortcutsandSettings();

  //> Cut length of the working string
  const int kWorkingStrMin = 48;
  //> Maximum length of the working string before we cut it
  const int kWorkingStrMax = 64;

  KeyHook keyHook;
  ModularDataModel dataStore;
  RobotCommon robot;
  PipeReader *pipeReader;
  std::thread piperThread;
  std::string workingString;
  std::string configGlobal;
  Status currStatus;
};

}  // namespace stellad

#endif  // SRC_DISPATCHER_H_
