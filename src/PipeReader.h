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
 * PipeReader.h
 *
 *  Created on: Oct 06, 2015
 *      Author: brad
 */

#ifndef SRC_PIPEREADER_H_
#define SRC_PIPEREADER_H_

#include <fcntl.h>  // FIFO
#include <sys/stat.h>  // FIFO
#include <sys/types.h>  // FIFO
#include <sys/select.h>
#include <unistd.h>  // FIFO, signal, timer?
#include <errno.h>  // Errors from open()
#include <stdlib.h>  // uh?
#include <signal.h>  // Catch signal
#include <string>  // String formal parameters
#include <iostream>  // std::cout
#include <fstream>  // Filestream
#include <functional>
#include <thread>

#include "protoc/command.pb.h"

namespace stellad {
// Handles all interactions with IPC pipe reader
class PipeReader {
 private:
  std::string * buffer;
  std::string fileloc;
  void run();

 public:
  bool ready;
  // Not to be used
  PipeReader();

  // Creates a PipeReader with specified fileloc, when the pipe is opened
  // it should create the pipe in the specified location
  explicit PipeReader(std::string fileloc);
  ~PipeReader();

  // Creates a new FIFO, if already present does nothing
  // returns if there was an error or not
  // (that wasn't based on already existing)
  bool openPipe();

  // Reads all the contents of the fifo into a buffer
  void readAll();

  // Returns the command buffer to be used in dispatcher
  stellad::proto::Control * getCommandBuff();

  // Sets call back to be called once the PipeReader receives a message
  void setCallback(std::function<void(bool)> cb);
};
} /* namespace stellad */

#endif  // SRC_PIPEREADER_H_
