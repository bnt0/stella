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
 * Keyhook.cc
 *
 *  Created on: Jul 22, 2015
 *      Author: brad
 */

#include "KeyHook.h"

int keysdown;
std::mutex keyboard_queue_mutex;
std::vector<keyboard_event_data> keyboard_queue;

namespace stellad {

KeyHook::KeyHook() {
}

KeyHook::~KeyHook() {
}

std::vector<keyboard_event_data>* KeyHook::getBuffer() {
  using std::vector;
  vector<keyboard_event_data>* buffer = new vector<keyboard_event_data>;
  keyboard_queue_mutex.lock();
  buffer->swap(keyboard_queue);
  keyboard_queue_mutex.unlock();
  return buffer;
}

int KeyHook::keysDown() {
  keyboard_queue_mutex.lock();
  int copy = keysdown;
  keyboard_queue_mutex.unlock();
  return copy;
}

void KeyHook::runHook(KeyHook* kh) {
  int status = hook_run();
	switch (status) {
	case UIOHOOK_SUCCESS:
	// Everything is ok.
	break;

	// System level errors.
	case UIOHOOK_ERROR_OUT_OF_MEMORY:
	logger_proc(LOG_LEVEL_ERROR, "Failed to allocate memory. (%#X)", status);
	break;


	// X11 specific errors.
	case UIOHOOK_ERROR_X_OPEN_DISPLAY:
	logger_proc(LOG_LEVEL_ERROR, "Failed to open X11 display. (%#X)", status);
	break;

	case UIOHOOK_ERROR_X_RECORD_NOT_FOUND:
	logger_proc(LOG_LEVEL_ERROR, "Unable to locate XRecord extension. (%#X)", status);
	break;

	case UIOHOOK_ERROR_X_RECORD_ALLOC_RANGE:
	logger_proc(LOG_LEVEL_ERROR, "Unable to allocate XRecord range. (%#X)", status);
	break;

	case UIOHOOK_ERROR_X_RECORD_CREATE_CONTEXT:
	logger_proc(LOG_LEVEL_ERROR, "Unable to allocate XRecord context. (%#X)", status);
	break;

	case UIOHOOK_ERROR_X_RECORD_ENABLE_CONTEXT:
	logger_proc(LOG_LEVEL_ERROR, "Failed to enable XRecord context. (%#X)", status);
	break;


	// Windows specific errors.
	case UIOHOOK_ERROR_SET_WINDOWS_HOOK_EX:
	logger_proc(LOG_LEVEL_ERROR, "Failed to register low level windows hook. (%#X)", status);
	break;


	// Darwin specific errors.
	case UIOHOOK_ERROR_AXAPI_DISABLED:
	logger_proc(LOG_LEVEL_ERROR, "Failed to enable access for assistive devices. (%#X)", status);
	break;

	case UIOHOOK_ERROR_CREATE_EVENT_PORT:
	logger_proc(LOG_LEVEL_ERROR, "Failed to create apple event port. (%#X)", status);
	break;

	case UIOHOOK_ERROR_CREATE_RUN_LOOP_SOURCE:
	logger_proc(LOG_LEVEL_ERROR, "Failed to create apple run loop source. (%#X)", status);
	break;

	case UIOHOOK_ERROR_GET_RUNLOOP:
	logger_proc(LOG_LEVEL_ERROR, "Failed to acquire apple run loop. (%#X)", status);
	break;

	case UIOHOOK_ERROR_CREATE_OBSERVER:
	logger_proc(LOG_LEVEL_ERROR, "Failed to create apple run loop observer. (%#X)", status);
	break;

	// Default error.
	case UIOHOOK_FAILURE:
	default:
	logger_proc(LOG_LEVEL_ERROR, "An unknown hook error occurred. (%#X)", status);
	break;
	}
}

int KeyHook::setHook() {
  hook_set_logger_proc(&logger_proc);
  hook_set_dispatch_proc(&dispatch_proc);
  threadHook = std::thread(runHook, this);

  return 0;//status;
}

std::string KeyHook::keyToMacroCode(keyboard_event_data key) {
  if (key.keychar == 0xffff) {// This is a KeyRelease event
    switch (key.keycode){
      case VC_ESCAPE: return "$ESC$";
      case VC_F1: return "$F1$";
      case VC_F2: return "$F2$";
      case VC_F3: return "$F3$";
      case VC_F4: return "$F4$";
      case VC_F5: return "$F5$";
      case VC_F6: return "$F6$";
      case VC_F7: return "$F7$";
      case VC_F8: return "$F8$";
      case VC_F9: return "$F9$";
      case VC_F10: return "$F10$";
      case VC_F11: return "$F11$";
      case VC_F12: return "$F12$";
      case VC_BACKSPACE: return "$BS$";
      case VC_TAB: return "$TAB$";
      case VC_CAPS_LOCK: return "$CAPS$";
      case VC_ENTER: return "$ENTER$";
      case VC_PRINTSCREEN: return "$PRTSC$";
      case VC_SCROLL_LOCK: return "$SCRLK$";
      case VC_PAUSE: return "$PAUSE$";
      case VC_INSERT: return "$INSERT$";
      case VC_DELETE: return "$DELETE$";
      case VC_HOME: return "$HOME$";
      case VC_END: return "$END$";
      case VC_PAGE_DOWN: return "$PAGEDW$";
      case VC_PAGE_UP: return "$PAGEUP$";
      case VC_UP: return "$UP$";
      case VC_LEFT: return "$LEFT$";
      case VC_RIGHT: return "$RIGHT$";
      case VC_DOWN: return "$DOWN$";

      //Keypad buttons are not typed however should behave the same as typed
      case VC_NUM_LOCK: return "$NUMLK$";
      case VC_KP_DIVIDE: return "/";
      case VC_KP_MULTIPLY: return "*";
      case VC_KP_SUBTRACT: return "-";
      case VC_KP_ADD: return "+";
      case VC_KP_ENTER: return "$ENTER$";
      case VC_KP_SEPARATOR: return ".";
      case VC_KP_1: return "1";
      case VC_KP_2: return "2";
      case VC_KP_3: return "3";
      case VC_KP_4: return "4";
      case VC_KP_5: return "5";
      case VC_KP_6: return "6";
      case VC_KP_7: return "7";
      case VC_KP_8: return "8";
      case VC_KP_9: return "9";
      case VC_KP_0: return "0";
      case VC_KP_COMMA: return ",";
      //Keypad end

      //We don't include shift as it's used to modify KeyType events
      case VC_CONTROL_L:
      case VC_CONTROL_R: return "$CTRL$";
      case VC_ALT_L:
      case VC_ALT_R: return "$ALT$";
      case VC_META_L:
      case VC_META_R: return "$WIN$";
      case VC_CONTEXT_MENU: return "$CONTEXT$";
    }
    return "";
  } else {
      if (key.rawcode == '$') return "$$";
      if (key.rawcode >= ' ' && key.rawcode <= '~') { // Covert char to str
          return std::string(1, (char)key.rawcode);
      }
      return "";
  }
}

} /* namespace stellad */

bool logger_proc(unsigned int level, const char *format, ...) {
  bool status = false;

  va_list args;
  switch (level) {
#ifdef USE_DEBUG
  case LOG_LEVEL_DEBUG:
  case LOG_LEVEL_INFO:
    va_start(args, format);
    status = vfprintf(stdout, format, args) >= 0;
    va_end(args);
    break;
#endif

  case LOG_LEVEL_WARN:
  case LOG_LEVEL_ERROR:
    va_start(args, format);
    status = vfprintf(stderr, format, args) >= 0;
    va_end(args);
    break;
  }

  return status;
}

void dispatch_proc(uiohook_event * const event) {
  switch (event->type) {
    case EVENT_KEY_PRESSED: 
      keyboard_queue_mutex.lock();
      keyboard_queue.push_back((event->data).keyboard);
      keyboard_queue_mutex.unlock();
      keysdown++;
      break;
    case EVENT_KEY_RELEASED:
      keysdown--;
      keysdown = std::max(keysdown, 0);
      break;
    case EVENT_KEY_TYPED:
      keyboard_queue_mutex.lock();
      keyboard_queue.push_back((event->data).keyboard);
      keyboard_queue_mutex.unlock();
      break;
    case EVENT_MOUSE_PRESSED:
    case EVENT_MOUSE_RELEASED:
    case EVENT_MOUSE_CLICKED:
    case EVENT_MOUSE_MOVED:
    case EVENT_MOUSE_DRAGGED:
    case EVENT_MOUSE_WHEEL:
    default:
      break;
  }
}
