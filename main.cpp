#include <fstream>
#include <iostream>
#include <string>

#include "lox.h"

using std::string;

void runFile(string path) {
  std::ifstream ifs{path};
  std::string source_code = "";
  std::string line;
  while (std::getline(ifs, line)) {
    source_code += line;
  }
  lox::Lox lox;
  lox.run(source_code);
}

void runPrompt() {
  string line;

  lox::Lox lox;

  for (;;) {
    std::cout << "> \n";
    if (!std::getline(std::cin, line)) break;
    lox.run(line);
  }
}

auto main(int argc, char** argv) -> int {
  if (argc > 2) {
    std::cout << "Usage: cpplox [script]\n";
    return 64;
  } else if (argc == 2) {
    runFile(argv[1]);
  } else {
    runPrompt();
  }
}
