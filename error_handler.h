#ifndef CPPLOX_ERROR_HANDLER_H
#define CPPLOX_ERROR_HANDLER_H

#include <string>

namespace lox {

class ErrorHandler {
public:
  void report(int line, std::string where, std::string message);

  void error(int line, std::string message);

private:
  bool hadError_ = false;
};

} // namespace lox

#endif //CPPLOX_ERROR_HANDLER_H
