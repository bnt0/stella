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
 * RobotCommon.cc
 *
 *  Created on: Oct 01, 2015
 *      Author: brad
 */

#include "RobotCommon.h"

namespace stellad {

RobotCommon::RobotCommon() {
  int  event_basep, error_basep, majorp, minorp;
  if (!(xdisplay = XOpenDisplay(NULL))) {
		std::cerr << "Unable to open display for Robot" << std::endl;
    exit(1);
  }
  XTestGrabControl(xdisplay, True);
  XSynchronize(xdisplay, True);

}

RobotCommon::~RobotCommon() {
  XCloseDisplay(xdisplay);
}

void RobotCommon::typeCharNoSync (const char chr,
      const int msdelaybetw, const int msdelayafter) {
  int isUpper = 0;
  std::string uppSpecial = "!@#$%^&*()_+}{\":\?<>~|";
  KeySym keysym;
  if (isupper(chr) || uppSpecial.find_first_of(chr) != std::string::npos) {
    isUpper = 1;
  }
  if (chr > 0x7E) {
    return;
  }
  if (chr >= 0x20) {
    keysym = (KeySym) chr;
  } else if (chr == '\b') {
    keysym = XK_BackSpace;
  } else {
      //... // Exercise left to the reader :-)
  }
  if (isUpper) {
    XTestFakeKeyEvent(xdisplay,
                      XKeysymToKeycode(xdisplay, XK_Shift_L),
                      True,
                      CurrentTime);
  }
  // Down
  XTestFakeKeyEvent(xdisplay,
                    XKeysymToKeycode(xdisplay, keysym),
                    True,
                    CurrentTime);
  if (msdelaybetw) {
    std::this_thread::sleep_for (std::chrono::milliseconds(msdelaybetw));
  }
  // Up
  XTestFakeKeyEvent(xdisplay,
                    XKeysymToKeycode(xdisplay, keysym),
                    False,
                    CurrentTime);
  if (isUpper) {
    XTestFakeKeyEvent(xdisplay,
                      XKeysymToKeycode(xdisplay, XK_Shift_L),
                      False,
                      CurrentTime);
  }
  if (msdelayafter)
    std::this_thread::sleep_for (std::chrono::milliseconds(msdelayafter));
}

void RobotCommon::typeString(const std::string stringi,
      const int msdelaybetw, const int msdelayafter) {
  using std::string;
  for (string::const_iterator i = stringi.begin(); i != stringi.end(); ++i) {
    typeCharNoSync((*i), msdelaybetw, msdelayafter);
  }

}
void RobotCommon::typeChar(const char chr,
      const int msdelaybetw, const int msdelayafter) {
  typeCharNoSync(chr, msdelaybetw, msdelayafter);
}
} /* namespace stellad */
