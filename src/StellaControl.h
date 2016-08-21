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
 * StellaControl.h
 *
 *  Created on: 2015-10-17
 *      Author: brad
 */


#ifndef STELLACONTROL_H_
#define STELLACONTROL_H_

#include <getopt.h>
#include <fstream>
#include <iostream>
#include <string>
#include <algorithm>
#include "protoc/command.pb.h"
#include "FUtils.h"

namespace stella {
namespace ctrl {
// enum Type refers to the type of message to send
enum Type {
  Null,
  ShortcutDefinition,
  Setting,
  SysAction
};
// Prints usage to std::cout then ends program
void printHelpAndDie();

// Returns a SysAction that is equal to the opt
stellad::proto::Control_SysAction sysActionHandler(const std::string& opt);

// Quick function to string to lower
std::string tolower(const std::string& opt);

// Makes a command to compile and sends to the stellad pipecontrol, if it fails
// it will end the program
// type of message to send
// key of Shortcut definition or Key for shortcut
// value of SD or shortcut
// action shortcut or setting, or sysaction
// enable true or false
void compileCommandAndDie(
    stella::ctrl::Type type, const std::string& key, const std::string &value,
    stellad::proto::Action action, bool enabled,
    stellad::proto::ShortcutDefinition_Mode mde);


std::string compileCommand(
    stella::ctrl::Type type, const std::string& key, const std::string &value,
    stellad::proto::Action action, bool enabled,
    stellad::proto::ShortcutDefinition_Mode mde);

// Sends a string (must be stream) to the pipecontrol
// streamstring the binary stream to send to the pipecontrol
bool sendMessage(std::string streamstring);

std::string setCallbackReader();

std::string waitForCallback(const std::string& fifoloc);

void writeToostream(std::ostream& os, const std::string& input);
void interactiveopt(char c);
// Interactive mode
void interactive();

} /* namespace ctrl */
} /* namespace stella */

int main(int argc, char* argv[]);

#endif /* STELLACONTROL_H_ */
