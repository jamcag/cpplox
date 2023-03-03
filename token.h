#ifndef CPPLOX_TOKEN_H
#define CPPLOX_TOKEN_H

#include "token_type.h"

#include <any>
#include <string>

namespace lox {

class Token {
public:
  Token(TokenType type, std::string lexeme, std::any literal, int line);
  friend std::ostream& operator<<(std::ostream&, const Token& token);
private:
  TokenType type_;
  std::string lexeme_;
  std::any literal_;
  int line_;
};

}
#endif //CPPLOX_TOKEN_H
