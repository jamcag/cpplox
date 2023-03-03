#include <iostream>

#include "lox.h"

namespace lox {

auto Lox::run(std::string source) -> void {
  Scanner scanner = Scanner(source, errorHandler_);
  std::vector<Token> tokens = scanner.scanTokens();

  for (Token token: tokens) {
    std::cout << token << "\n";
  }
};

}
