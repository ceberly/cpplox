#include "scanner.h"
#include "lox.h"

const std::vector<Token> &Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(
      Token(LOX_EOF, std::string_view(""), std::move(EmptyLiteral), line));

  return tokens;
}

void Scanner::addToken(TokenType type, Literal &&literal) {
  std::string_view s(source.data() + start, current - start);
  tokens.push_back(Token(type, std::move(s), literal, line));
  return;
}

void Scanner::scanToken() {
  char c = advance();

  switch (c) {
  case '(':
    addToken(LEFT_PAREN);
    break;
  case ')':
    addToken(RIGHT_PAREN);
    break;
  case '{':
    addToken(LEFT_BRACE);
    break;
  case '}':
    addToken(RIGHT_BRACE);
    break;
  case ',':
    addToken(COMMA);
    break;
  case '.':
    addToken(DOT);
    break;
  case '-':
    addToken(MINUS);
    break;
  case '+':
    addToken(PLUS);
    break;
  case ';':
    addToken(SEMICOLON);
    break;
  case '*':
    addToken(STAR);
    break;
  case '!':
    addToken(match('=') ? BANG_EQUAL : BANG);
    break;
  case '=':
    addToken(match('=') ? EQUAL_EQUAL : EQUAL);
    break;
  case '<':
    addToken(match('=') ? LESS_EQUAL : LESS);
    break;
  case '>':
    addToken(match('=') ? GREATER_EQUAL : GREATER);
    break;
  case '/':
    if (match('/')) {
      while (peek() != '\n' && !isAtEnd())
        advance();
    } else {
      addToken(SLASH);
    }
    break;
  case ' ':
  case '\r':
  case '\t':
    break;
  case '\n':
    line++;
    break;
  case '"':
    string();
    break;
  default:
    if (Scanner::isDigit(c)) {
      number();
    } else if (Scanner::isAlpha(c)) {
      identifier();
    } else {
      Lox::error(line, "Unexpected character.");
    }

    break;
  }

  return;
}

bool Scanner::match(const char expected) {
  if (isAtEnd())
    return false;
  if (source[current] != expected)
    return false;

  current++;
  return true;
}

void Scanner::string() {
  while (peek() != '"' && !isAtEnd()) {
    if (peek() == '\n')
      line++;
    advance();
  }

  if (isAtEnd()) {
    Lox::error(line, "Unterminated string.");
    return;
  }

  advance();

  Literal literal;
  literal.str = source.substr(start + 1, current - 1).c_str();

  addToken(STRING, std::move(literal));
}

void Scanner::number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek()))
      advance();
  }

  std::string s = source.substr(start, current - start);
  Literal literal;
  literal.number = std::stod(s);

  addToken(NUMBER, std::move(literal));
}
void Scanner::identifier() {
  while (Scanner::isAlphaNumeric(peek()))
    advance();

  addToken(IDENTIFIER);
}
