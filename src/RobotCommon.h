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
 * RobotCommon.h
 *
 *  Created on: Oct 01, 2015
 *      Author: brad
 */

#ifndef ROBOTCOMMON_H_
#define ROBOTCOMMON_H_

#include <string>
#include <iostream>
#include <cctype>
#include <thread>
#include <chrono>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <X11/extensions/XTest.h>
#include "VirtualTyperInterface.h"

namespace stellad {
// Used to type to X11 screen
class RobotCommon : public VirtualTyperInterface {
  Display* xdisplay;
  // Doesn't call sync to the xdisplay
  virtual void typeCharNoSync(const char charactor, const int msdelaybetw = 0,
                              const int msdelayafter = 0);
public:
  RobotCommon();
  virtual ~RobotCommon();

  // Type string to the screen
  // string the actual string to print to the screen
  // msdelaybetw time in ms between key press and key release
  // msdelayafter time in ms after releasing key
  virtual void typeString(const std::string string,
                          const int msdelaybetw = 0, const int msdelayafter = 0);
                          
  // Type character to the screen
  // chr the actual character to print to the screen
  // msdelaybetw time in ms between key press and key release
  // msdelayafter time in ms after releasing key
  virtual void typeChar(const char chr,
                        const int msdelaybetw = 0, const int msdelayafter = 0);
};

} /* namespace stellad */

#endif /* ROBOTCOMMON_H_ */
