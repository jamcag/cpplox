#include "token.h"

#include <iostream>

namespace lox {

Token::Token(TokenType type, std::string lexeme, std::any literal, int line) :
type_(type), lexeme_(lexeme), literal_(literal), line_(line) {}

std::ostream& operator<<(std::ostream& os, const Token &token) {
  os << static_cast<int>(token.type_);
  os << " ";
  os << token.lexeme_;
  if (token.type_ == TokenType::String) {
    os << " " << std::any_cast<std::string>(token.literal_);
  } else if (token.type_ == TokenType::Number) {
    os << " " << std::any_cast<double>(token.literal_);
  }
  return os;
}

} // namespace lox