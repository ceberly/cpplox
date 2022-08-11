#include <iostream>

#include "lox.h"
#include "scanner.h"

#include <unordered_map>

const static std::unordered_map<std::string, TokenType> keywords{
    {"and", AND},   {"class", CLASS}, {"else", ELSE},     {"false", FALSE},
    {"for", FOR},   {"fun", FUN},     {"if", IF},         {"nil", NIL},
    {"or", OR},     {"print", PRINT}, {"return", RETURN}, {"super", SUPER},
    {"this", THIS}, {"true", TRUE},   {"var", VAR},       {"while", WHILE},
};

const std::vector<Token> &Scanner::scanTokens() {
  while (!isAtEnd()) {
    start = current;
    scanToken();
  }

  tokens.push_back({LOX_EOF, std::string_view(""), Literal{nullptr}, line});

  return tokens;
}

void Scanner::addToken(TokenType type, Literal literal) {
  tokens.push_back(
      {type, {source.data() + start, current - start}, literal, line});
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

  Literal literal{nullptr};
  literal.str = {source.data() + start + 1, current - 2 - start};

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

  Literal literal{nullptr};
  literal.number = std::stod(source.substr(start, current - start));

  addToken(NUMBER, std::move(literal));
}

void Scanner::identifier() {
  while (Scanner::isAlphaNumeric(peek()))
    advance();

  auto found = keywords.find(source.substr(start, current - start));
  if (found == keywords.end()) {
    addToken(IDENTIFIER);
    return;
  }

  addToken(found->second);
}
