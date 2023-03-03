#ifndef CPPLOX_LOX_H
#define CPPLOX_LOX_H

#include <iostream>

#include "error_handler.h"
#include "scanner.h"

namespace lox {

class Lox {
public:
  void run(std::string source);

private:
  ErrorHandler errorHandler_;
};

} // namespace lox

#endif //CPPLOX_LOX_H
