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
 * PipeReader.cc
 *
 *  Created on: Oct 06, 2015
 *      Author: brad
 */

#include "PipeReader.h"

namespace stellad {
  PipeReader::PipeReader() {
    buffer = new std::string();
    this->fileloc = "/";
  }

  PipeReader::PipeReader(std::string fileloc) : ready(false) {
    buffer = new std::string();
    this->fileloc = fileloc;
    this->openPipe();
  }

  PipeReader::~PipeReader() {
    delete buffer;
  }

  bool PipeReader::openPipe() {
    if (mkfifo(this->fileloc.c_str(), S_IRUSR | S_IWUSR) == -1 &&
         errno != EEXIST) {
      return false;
    }
    return true;
  }

  void PipeReader::readAll() {
    int fd = open(this->fileloc.c_str(), O_RDWR | O_NONBLOCK);
    fd_set rfds;
    struct timeval tv;
    int retval;
    FD_ZERO(&rfds);
    FD_SET(fd, &rfds);
    tv.tv_sec = 0;
    tv.tv_usec = 1000;
    retval = select(fd+1, &rfds, NULL, NULL, &tv);
    if (retval == -1) {
      std::cerr << "Error occured selecting file" << std::endl;
    } else if (retval) {
      int num = 0;
      char buff[64];
      errno = 0;
      do {
        num = read(fd, buff, sizeof(buff));
        if (num < 1)
          break;
        (* buffer) += std::string(buff, num);
      } while (num != 0);
      if (errno != 0 && errno != 11)
        std::cerr << "Error occured while reading " << errno << std::endl;
      this->ready = true;
    }
    close(fd);
  }

  stellad::proto::Control * PipeReader::getCommandBuff() {
    stellad::proto::Control *result = new stellad::proto::Control();
    if (!result->ParseFromString(*buffer)) {
      std::cerr << "Failed to parse Control message from buffer" << std::endl;
      delete buffer;
      buffer = new std::string();
      return nullptr;
    }
    delete buffer;
    buffer = new std::string();
    return result;
  }

} /* namespace stellad */
