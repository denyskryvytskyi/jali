#pragma once

#include "Literal.h"

enum class TokenType {
    // Single-character tokens.
    LEFT_PAREN,
    RIGHT_PAREN,
    LEFT_BRACE,
    RIGHT_BRACE,
    COMMA,
    DOT,
    MINUS,
    PLUS,
    SEMICOLON,
    SLASH,
    STAR,

    // One or two character tokens.
    BANG,
    BANG_EQUAL,
    EQUAL,
    EQUAL_EQUAL,
    GREATER,
    GREATER_EQUAL,
    LESS,
    LESS_EQUAL,

    // Literals.
    IDENTIFIER,
    STRING,
    NUMBER,

    // Keywords.
    AND,
    CLASS,
    ELSE,
    FALSE,
    FUN,
    FOR,
    IF,
    NIL,
    OR,
    PRINT,
    RETURN,
    SUPER,
    THIS,
    TRUE,
    VAR,
    WHILE,

    ENDOF
};

struct Token {
    Token(TokenType type_, std::string&& lexeme_, int line_, std::optional<Literal> literal_ = std::nullopt)
        : type(type_)
        , lexeme(std::move(lexeme_))
        , line(line_)
        , literal(std::move(literal_))
    { }

    TokenType type;
    std::string lexeme;
    int line;
    std::optional<Literal> literal;
};

std::ostream& operator<<(std::ostream& output, const Token& token);

class Scanner {
public:
    Scanner(std::string&& source_);

    std::vector<Token> ScanTokens();

private:
    void ScanToken();
    void AddToken(const TokenType& type);
    void AddToken(const TokenType& type, Literal&& literal_);
    bool IsAtEnd() const;
    bool Match(const char& expected);
    char Advance();
    char Peek();
    char PeekNext();
    void String();
    void Number();
    void Identifier();
    bool IsDigit(char c) const;
    bool IsAlpha(char c) const;
    bool IsAlphaNumeric(char c) const;

private:
    std::vector<Token> tokens;
    std::string source;

    int start { 0 };
    int current { 0 };
    int line { 1 };

    static std::unordered_map<std::string, TokenType> keywords;
};
