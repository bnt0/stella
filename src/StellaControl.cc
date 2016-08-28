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
 * StellaControl.cc
 *
 *  Created on: 2015-10-17
 *      Author: brad
 */

#include "StellaControl.h"

namespace stella {
namespace ctrl {
  const std::string kHelpString =
  "Usage: stella-config ACTION OPTIONS VALUEOPT...\n"
  "       stella-config {-s | --sys-action} {shutdown|reload|ignore|status|save|list}\n\n"
  "       Main operation mode:\n\n"
  "        -I --interactive         ignore all other options and switch to interactive\n"
  "        -h --help                ignore all other options and display this text\n\n"
  "         ACTION := {-S --shortcut|-t --setting}\n"
  "        OPTIONS := {-a -add|-r --remove|-m --modify}\n"
  "       VALUEOPT := {-k --key|-v --value|-e --enabled|-M --mode}";

  void printHelpAndDie() {
    std::cout << stella::ctrl::kHelpString << std::endl;
    exit(EXIT_SUCCESS);
  }

  stellad::proto::Control_SysAction sysActionHandler(const std::string& opt) {
    std::string lowerstr = stella::ctrl::tolower(opt);
    if (lowerstr == "shutdown")
      return stellad::proto::Control_SysAction_SHUTDOWN;
    if (lowerstr == "reload")
      return stellad::proto::Control_SysAction_RELOAD;
    if (lowerstr == "ignore")
      return stellad::proto::Control_SysAction_IGNORE;
    if (lowerstr == "status")
      return stellad::proto::Control_SysAction_STATUS;
    if (lowerstr == "save")
      return stellad::proto::Control_SysAction_SAVE;
    if (lowerstr == "list")
      return stellad::proto::Control_SysAction_LIST;
    if (lowerstr == "response")
      return stellad::proto::Control_SysAction_RESPONSE;

    return stellad::proto::Control_SysAction_OTHER;
  }

  std::string tolower(const std::string& opt) {
    std::string data = opt;
    std::transform(data.begin(), data.end(), data.begin(), ::tolower);
    return data;
  }


  void compileCommandAndDie(
      stella::ctrl::Type type, const std::string& key, const std::string &value,
      stellad::proto::Action action, bool enabled,
      stellad::proto::ShortcutDefinition_Mode mde) {
		std::string command = compileCommand(type, key, value, action, enabled,
				mde);
			if (command.compare("") == 0) {
				exit(EXIT_FAILURE);
			}
			if (sendMessage(command)) {
				exit(EXIT_SUCCESS);
			}
			exit(EXIT_FAILURE);
	}
		

  std::string compileCommand(
      stella::ctrl::Type type, const std::string& key, const std::string &value,
      stellad::proto::Action action, bool enabled,
      stellad::proto::ShortcutDefinition_Mode mde) {
    stellad::proto::Control stream;
    stream.set_action(stellad::proto::Control_SysAction_OTHER);
    if (type == stella::ctrl::Type::ShortcutDefinition) {
      stellad::proto::ShortcutDefinition * sd = stream.add_shortcuts();
      sd->set_key(key);
      sd->set_action(action);
      sd->set_value(value);
      sd->set_enabled(enabled);
      sd->set_mode(mde);
    } else if (type == stella::ctrl::Type::Setting) {
      stellad::proto::Setting * sd = stream.add_settings();
      sd->set_key(key);
      sd->set_act(action);
      sd->set_val(value);
    } else if (type == stella::ctrl::Type::SysAction) {
      std::cerr << "Type set to SysAction, invalid function" << std::endl;
			return "";
    } else {
      std::cerr << "No type set" << std::endl;
			return "";
    }

    return stream.SerializeAsString();
  }

  bool sendMessage(std::string streamstring) {
    std::string configdir = stellad::utils::findConfig();
    if (configdir == "/") {
      std::cerr << "Unable to find reasonable config directory" << std::endl;
      return false;
    }
    configdir += "stellad/control-pipe";
    if (!stellad::utils::pipe_exists(configdir)) {
      std::cerr << "Unable to find pipe in config directory: " << configdir
          << std::endl;
      return false;
    }
    std::ofstream pipectrl;
    pipectrl.open(configdir, std::ios::out | std::ios::binary);
    if (pipectrl.is_open()) {
      pipectrl << streamstring;
      pipectrl.close();
    } else {
      std::cerr << "Pipe failed to open" << std::endl;
      return false;
    }
    return true;
  }

  std::string setCallbackReader() {
    std::string callbackfile = stellad::utils::findConfig();
    if (callbackfile == "/") {
      std::cerr << "Unable to find reasonable config directory" << std::endl;
      return "";
    }
    callbackfile += "stellad/callback-pipe";
    if (!stellad::utils::pipe_exists(callbackfile)) {
      if (mkfifo(callbackfile.c_str(), S_IRUSR | S_IWUSR) == -1 && errno != EEXIST) {
        std::cerr << "Problem making the fifo" << std::endl;
        return "";
      }
    }
    return callbackfile;
  }

  std::string waitForCallback(const std::string& fifoloc) {
    std::ifstream ifs(fifoloc, std::ifstream::in);
    std::string result = std::string((std::istreambuf_iterator<char>(ifs)),
        std::istreambuf_iterator<char>());
    ifs.close();
    return result;
  }

  void writeToostream(std::ostream& os, const std::string& input) {
    stellad::proto::Control result = stellad::proto::Control();
    if (!result.ParseFromString(input)) {
      std::cerr << "Failed to parse Control message from buffer" << std::endl;
      return;
    }
    if (result.has_action()
        && result.action() == stellad::proto::Control_SysAction_RESPONSE) {
      // Write data
      std::cout << "####### Writing reply from stellad #######" << std::endl;
      if (result.shortcuts_size() != 0)
        std::cout << "Printing shortcuts" << std::endl;
      for (int i = 0; i < result.shortcuts_size(); ++i) {
        const stellad::proto::ShortcutDefinition& crkey = result.shortcuts(i);
        std::cout
            << "Key: `" << (crkey.has_key() ? crkey.key() : "none")
            << "` Value: `" << (crkey.has_value() ? crkey.value() : "none")
            << "` Enabled? `" << (crkey.has_enabled() ? (crkey.enabled() ? "true" : "false") : "none")
            << "` Mode: `" << "Unimplemented`"
            << std::endl;
      }
      if (result.settings_size() != 0)
        std::cout << "####### Printing shortcuts #######";
      for (int i = 0; i < result.settings_size(); ++i) {
        const stellad::proto::Setting& crkey = result.settings(i);
        std::cout
            << "Key: " << (crkey.has_key() ? crkey.key() : "none")
            << " Value: " << (crkey.has_val() ? crkey.val() : "none")
            << std::endl;
      }

    } else if (result.has_action() &&
	       result.action() == stellad::proto::Control_SysAction_STATUS) {
      std::cout << "####### Writing reply from stellad #######" << std::endl;
      std::cout << (result.status() == true
		    ? "Enabled" : "Disabled") << std::endl;
    }
  }

const std::string helptext = "h) this text\n"
	"a) add new shortcut\n"
	"m) modify shortcut\n"
	"r) remove shortcut\n"
	"l) list all shortcuts\n"
	"s) save settings";

void interactiveopt(char c) {
	using namespace stellad::proto;
	std::string works, key, value;
	bool enabled = false;
	ShortcutDefinition_Mode mode;

	stellad::proto::Control mes;
	std::string result;
	switch(c) {
		
		case 'a':
		case 'm':
			do {
				std::cout << "Specify key: ";
				getline(std::cin, works);
			} while (works.compare("") == 0);
			key = works;
			do {
				std::cout << "Specify value: ";
				getline(std::cin, works);
			} while (works.compare("") == 0);
			value = works;
			do {
				std::cout << "Specify enabled t/f [t] ";
				getline(std::cin, works);
			} while (works.compare("t") != 0 &&  works.compare("f") != 0 &&
					works.compare("") != 0);
			enabled = works.compare("t") == 0 || works.compare("") == 0;
			do {
				std::cout << "Specify mode 0/0 [0] ";
				getline(std::cin, works);
			} while (works.compare("0") != 0 && works.compare("") != 0);
			mode = ShortcutDefinition_Mode_DEFAULT;
			works = compileCommand(stella::ctrl::Type::ShortcutDefinition, 
					key, value,	c == 'a' ? Action::ADD : Action::MODIFY, enabled,
					ShortcutDefinition_Mode_DEFAULT);
			if(!sendMessage(works))
				std::cout << "Message failed to send" << std::endl;
			break;
		case 'r':
			do {
				std::cout << "Specify key: ";
				getline(std::cin, works);
			} while (works.compare("") == 0);
			key = works;
			works = compileCommand(stella::ctrl::Type::ShortcutDefinition,
					key, "", Action::REM, false, ShortcutDefinition_Mode_DEFAULT);
			if(!sendMessage(works))
				std::cout << "Message failed to send" << std::endl;
			break;
		case 'l':
			mes.set_action(Control_SysAction_LIST);
			if(!sendMessage(mes.SerializeAsString()))
				std::cout << "Message failed to send" << std::endl;
			result = waitForCallback(setCallbackReader());
			writeToostream(std::cout, result);
			break;
		default:
			break;
	}
	
}

void interactive() {
	std::string command;
	std::cout << helptext << std::endl;
	stellad::proto::Control mes;
	while (getline(std::cin, command)) {
		std::cout << "[> ";
		switch (command[0]) {
		case 'a':
		case 'm':
		case 'r':
		case 'l':
			interactiveopt(command[0]);
			break;
		case 's':
			mes.set_action(stellad::proto::Control_SysAction_SAVE); 
				if(!sendMessage(mes.SerializeAsString()))
					std::cout << "Stella setting save failed!" << std::endl;
				else
					std::cout << "Saved!" << std::endl;
			break;
		default:
			std::cout << helptext << std::endl;
		}
	}
}

} /* namespace ctrl */
} /* namespace stella */

int main(int argc, char* argv[]) {
  int currarg; // current arg
  char option_index = 0;
  // time for some serious c
  using namespace stellad::proto;

  Control_SysAction sysopt = Control_SysAction_OTHER;
  stella::ctrl::Type type = stella::ctrl::Type::Null;
  std::string key;
  bool actionset = false;
  Action action = Action::ADD;
  std::string value;
  bool enabled = false;
  bool interactiveflag = false;
  ShortcutDefinition_Mode mde = ShortcutDefinition_Mode_DEFAULT;
  if (argc == 1)
    stella::ctrl::printHelpAndDie();
  while(true) {
   int option_index = 0;
    static struct option long_opts[] = {
      {"sys-action", required_argument, 0, 's'},
      {"shortcut",   no_argument, 0, 'S'},
      {"setting",    no_argument, 0, 't'},
      {"add",        no_argument, 0, 'a'},
      {"remove",     no_argument, 0, 'r'},
      {"modify",     no_argument, 0, 'm'},
      {"key",        required_argument, 0, 'k'},
      {"value",      required_argument, 0, 'v'},
      {"enabled",    required_argument, 0, 'e'},
      {"mode",       required_argument, 0, 'M'},
      {"interactive", no_argument, 0, 'I'},
      {"help",       no_argument, 0, 'h'},
      {0     ,       0, 0, 0}
    };

    currarg = getopt_long(
        argc, argv, "StarmIhs:k:v:e:m:", long_opts, &option_index);
    if (currarg == -1) break;

    switch (currarg) {
      case 0:
        break;
      case 's':
        if (type != stella::ctrl::Type::Null) {
          std::cerr << "You may only specify one of --shortcut, --sys-action, "
              << "or --setting" << std::endl;
          exit(EXIT_FAILURE);
        }
        type = stella::ctrl::Type::SysAction;
        sysopt = stella::ctrl::sysActionHandler(optarg);
        break;
      case 'S':
        if (type != stella::ctrl::Type::Null) {
          std::cerr << "You may only specify one of --shortcut, --sys-action, "
              << "or --setting" << std::endl;
          exit(EXIT_FAILURE);
        }
        type = stella::ctrl::Type::ShortcutDefinition;
        break;
      case 't': // Setting
        if (type != stella::ctrl::Type::Null) {
          std::cerr << "You may only specify one of --shortcut, --sys-action, "
              << "or --setting" << std::endl;
          exit(EXIT_FAILURE);
        }
        type = stella::ctrl::Type::ShortcutDefinition;
        break;
      case 'a':
        if (actionset) {
          std::cerr << "You may only specify one of --add, --remove, "
            <<  "or --modify" << std::endl;
          exit(EXIT_FAILURE);
        }
        action = Action::ADD;
        actionset = true;
        break;
      case 'r':
        if (actionset) {
          std::cerr << "You may only specify one of --add, --remove, "
              << "or --modify" << std::endl;
          exit(EXIT_FAILURE);
        }
        action = Action::REM;
        actionset = true;
        break;
      case 'm':
        if (actionset) {
          std::cerr << "You may only specify one of --add, --remove, "
              << "or --modify" << std::endl;
          exit(EXIT_FAILURE);
        }
        action = Action::MODIFY;
        actionset = true;
        break;
      case 'k':
        key = std::string(optarg);
        break;
      case 'v':
        value = std::string(optarg);
        break;
      case 'e':
        enabled = (std::string("true").
            compare(stella::ctrl::tolower(optarg)) == 0);
        break;
      case 'M': // option is ignored for now
        //switch (optarg) {
        //  case "DEFAULT":
        //    break;
        //  default:
        //    break;
        //}
        break;
      case 'I':
        interactiveflag = true;
				break;
      case 'h':
        stella::ctrl::printHelpAndDie();
        break;
    }
  }
  if (interactiveflag) {
		stella::ctrl::interactive();
		exit(EXIT_SUCCESS);
  }
  if (type == stella::ctrl::Type::ShortcutDefinition) {
    stella::ctrl::compileCommandAndDie(
        type, key, value, action, enabled, mde);
  } else if (type == stella::ctrl::Type::Setting) {
    stella::ctrl::compileCommandAndDie(
        type, key, value, action, false,
        stellad::proto::ShortcutDefinition_Mode_DEFAULT);
  } else if (type == stella::ctrl::Type::SysAction) {
    stellad::proto::Control mes;
    mes.set_action(sysopt);
    if (sysopt != stellad::proto::Control_SysAction_LIST &&
	sysopt != stellad::proto::Control_SysAction_STATUS) {
      exit(stella::ctrl::sendMessage(mes.SerializeAsString()) ?
          EXIT_SUCCESS : EXIT_FAILURE);
    } else {
      std::string callbackfile = stella::ctrl::setCallbackReader();
      if(!stella::ctrl::sendMessage(mes.SerializeAsString())) {
        std::cerr << "Problem writing to control socket" << std::endl;
        exit(EXIT_FAILURE);
      }
      std::string result = stella::ctrl::waitForCallback(callbackfile);
      stella::ctrl::writeToostream(std::cout, result);
      exit(EXIT_SUCCESS);
    }
  }

}
