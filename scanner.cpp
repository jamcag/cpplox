#include <optional>

#include "lox.h"
#include "scanner.h"

using enum lox::TokenType;

namespace lox {

Scanner::Scanner(std::string source, ErrorHandler& errorHandler) : source_(source), errorHandler_(errorHandler) {}

auto Scanner::scanTokens() -> std::vector<Token> {
  while (!isAtEnd()) {
    start_ = current_;
    scanToken();
  }

  tokens_.emplace_back(Eof, "", std::nullopt, line_);
  return tokens_;
}

auto Scanner::scanToken() -> void {
  char c = advance();
  switch(c) {
    case '(': addToken(LeftParen); break;
    case ')': addToken(RightParen); break;
    case '{': addToken(LeftBrace); break;
    case '}': addToken(RightBrace); break;
    case ',': addToken(Comma); break;
    case '.': addToken(Dot); break;
    case '-': addToken(Minus); break;
    case '+': addToken(Plus); break;
    case ';': addToken(Semicolon); break;
    case '*': addToken(Star); break;
    case '!':
      addToken(match('=') ? BangEqual : Bang);
      break;
    case '=':
      addToken(match('=') ? EqualEqual : Equal);
    case '<':
      addToken(match('=') ? LessEqual : Less);
    case '>':
      addToken(match('=') ? GreaterEqual : Greater);
    case '/':
      if (match('/')) {
        while (peek() != '\n' && !isAtEnd()) advance();
      } else {
        addToken(Slash);
      }
      break;

    case ' ':
    case '\r':
    case '\t':
      // Ignore whitespace.
      break;

    case '\n':
      line_++;
      break;

    case '"': string(); break;

    default:
      if (isDigit(c)) {
        number();
      } else if (isAlpha(c)) {
        identifier();
      } else {
        errorHandler_.error(line_, "Unexpected character.");
      }
  }
}

auto Scanner::number() -> void {
  while (isDigit(peek())) advance();

  if (peek() == '.' && isDigit(peekNext())) {
    // Consume the "."
    advance();
    while (isDigit(peek())) advance();
  }

  addToken(Number,
           std::stod(source_.substr(start_, current_)));
}

auto Scanner::identifier() -> void {
  while (isAlphaNumeric(peek())) advance();

  std::string text = source_.substr(start_, current_);
  if (keywords_.contains(text)) {
    addToken(keywords_[text]);
  } else {
    addToken(Identifier);
  }
}

auto Scanner::string() -> void {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n') line_++;
    advance();
  }

  if (isAtEnd()) {
    errorHandler_.error(line_, "Unterminated string");
    return;
  }

  // The closing ".
  advance();

  // Trim the surrounding quotes.
  std::string value = source_.substr(start_ + 1, current_ - 1);
  addToken(String, value);
}

auto Scanner::match(char expected) -> bool {
  if (isAtEnd()) return false;
  if (source_.at(current_) != expected) return false;

  current_++;
  return true;
}

auto Scanner::peek() -> char {
  if (isAtEnd()) return '\0';
  return source_.at(current_);
}

auto Scanner::peekNext() -> char {
  if (current_ + 1 >= source_.length()) return '\0';
  return source_.at(current_ + 1);
}

auto Scanner::isAlpha(char c) -> bool {
  return (c >= 'a' && c <= 'z') ||
         (c >= 'A' && c <= 'Z') ||
         c == '_';
}

auto Scanner::isAlphaNumeric(char c) -> bool {
  return isAlpha(c) || isDigit(c);
}

auto Scanner::isDigit(char c) -> bool {
  return c >= '0' && c <= '9';
}

auto Scanner::isAtEnd() -> bool {
  return current_ >= source_.length();
}

auto Scanner::advance() -> char {
  return source_.at(current_++);
}

auto Scanner::addToken(TokenType type) -> void {
  addToken(type, std::nullopt);
}

auto Scanner::addToken(TokenType type, std::any literal) -> void {
  std::string text = source_.substr(start_, current_);
  tokens_.emplace_back(type, text, literal, line_);
}

} // namespace lox