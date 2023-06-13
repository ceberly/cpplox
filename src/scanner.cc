#include "scanner.h"

#include <unordered_map>

static const std::unordered_map<std::string_view, TokenType> keywords = {
    {"and", AND},   {"class", CLASS}, {"else", ELSE},     {"false", FALSE},
    {"for", FOR},   {"fun", FUN},     {"if", IF},         {"nil", NIL},
    {"or", OR},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
    {"this", THIS}, {"true", TRUE},   {"var", VAR},       {"while", WHILE}};

static inline bool isDigit(const char c) { return c >= '0' && c <= '9'; }
static inline bool isAlpha(const char c) {
  return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

static inline bool isAlphaNumeric(const char c) {
  return isDigit(c) || isAlpha(c);
}

void Scanner::addToken(TokenType type, Token::Literal literal) {
  auto lexeme = source.substr(start, current);
  tokens.push_back(Token{type, lexeme, literal, line});
}

void Scanner::addToken(TokenType type) { addToken(type, std::nullopt); }

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
    error(line, "Unterminated string.");
    return;
  }

  advance();

  addToken(STRING, source.substr(start + 1, current - 1));
}

void Scanner::number() {
  while (isDigit(peek()))
    advance();

  if (peek() == '.' && isDigit(peekNext())) {
    advance();

    while (isDigit(peek()))
      advance();
  }

  addToken(NUMBER, 5.0);
}

void Scanner::identifier() {
  while (isAlphaNumeric(peek()))
    advance();

  auto type = keywords.find(source.substr(start, current));
  if (type == keywords.end()) {
    addToken(IDENTIFIER);
  } else {
    addToken(type->second);
  }
}

void Scanner::scanToken() {
  const char c = advance();

  switch (c) {
  case ' ':
  case '\t':
  case '\r':
    break;
  case '\n':
    line++;
    break;
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
  case '"':
    string();
    break;
  default:
    if (isDigit(c)) {
      number();
    } else if (isAlpha(c)) {
      identifier();
    } else {
      error(line, "Unexpected character.");
    }
    break;
  }
}

void Scanner::report(int line, const char *where, const char *message) {
  hadError = true;

  printf("[line %d] Error%s: %s\n", line, where, message);
}

void Scanner::error(int line, const char *message) {
  report(line, "", message);
}

void Scanner::scanTokens() {
  hadError = false;

  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back(Token{IS_EOF, std::string_view{""}, std::nullopt, line});
}
