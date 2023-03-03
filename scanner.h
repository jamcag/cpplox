#ifndef CPPLOX_SCANNER_H
#define CPPLOX_SCANNER_H

#include <string>
#include <vector>
#include <unordered_map>

#include "token.h"
#include "token_type.h"

namespace lox {

class Scanner {
public:
  explicit Scanner(std::string source, ErrorHandler& errorHandler);

  std::vector<Token> scanTokens();


private:
  void scanToken();
  void number();
  void identifier();
  void string();
  bool match(char expected);
  char peek();
  char peekNext();
  bool isAlpha(char c);
  bool isAlphaNumeric(char c);
  bool isDigit(char c);
  bool isAtEnd();
  char advance();
  void addToken(TokenType type);
  void addToken(TokenType type, std::any literal);

  const std::string source_;
  std::vector<Token> tokens_;
  int start_ = 0;
  int current_ = 0;
  int line_ = 1;
  ErrorHandler& errorHandler_;

  using enum lox::TokenType;
  std::unordered_map<std::string, TokenType> keywords_ = {
      {"and",    And},
      {"class",  Class},
      {"else",   Else},
      {"false",  False},
      {"for",    For},
      {"fun",    Fun},
      {"if",     If},
      {"nil",    Nil},
      {"or",     Or},
      {"print",  Print},
      {"return", Return},
      {"super",  Super},
      {"this",   This},
      {"true",   True},
      {"var",    Var},
      {"while",  While}
  };
};

}
#endif //CPPLOX_SCANNER_H
