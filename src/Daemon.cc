#include "Dispatcher.h"
#include <chrono>
#include <thread>

int main(int argc, const char* argv[]);

//! Main loop of the stellad daemon
int main(int argc, const char* argv[]) {
  stellad::Dispatcher dispatcher;
  dispatcher.startDaemon();
  while (true) {
    dispatcher.tick();
    std::this_thread::sleep_for(std::chrono::milliseconds(2));
  }
  dispatcher.endDaemon();
  return 0;
}
