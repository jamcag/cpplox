#include "error_handler.h"

#include <iostream>

namespace lox {

auto ErrorHandler::error(int line, std::string message) -> void {
  report(line, "", message);
}

auto ErrorHandler::report(int line, std::string where, std::string message) -> void {
  std::cerr << "[line " << line << "] Error" << where << ": " << message << "\n";
  hadError_ = true;
}

} // namespace lox
