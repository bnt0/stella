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
 * VirtualTyper.h
 *
 *  Created on: Apr 30, 2015
 *      Author: brad
 */

#ifndef VIRTUALTYPERINTERFACE_H_
#define VIRTUALTYPERINTERFACE_H_

#include <string>

// Interface for typing robot
class VirtualTyperInterface
{
public:
    virtual void typeString(const std::string string,
                            const int msdelaybetw, const int msdelayafter) = 0;
    virtual void typeChar(const char charactor,
                          const int msdelaybetw, const int msdelayafter) = 0;

};

#endif /* VIRTUALTYPERINTERFACE_H_ */
