#include "Scanner.h"
#include "ErrorHandler.h"

std::unordered_map<std::string, TokenType> Scanner::keywords = {
    { "and", TokenType::AND },
    { "class", TokenType::CLASS },
    { "else", TokenType::ELSE },
    { "false", TokenType::FALSE },
    { "for", TokenType::FOR },
    { "fun", TokenType::FUN },
    { "if", TokenType::IF },
    { "nil", TokenType::NIL },
    { "or", TokenType::OR },
    { "print", TokenType::PRINT },
    { "return", TokenType::RETURN },
    { "super", TokenType::SUPER },
    { "this", TokenType::THIS },
    { "true", TokenType::TRUE },
    { "var", TokenType::VAR },
    { "while", TokenType::WHILE }
};

std::ostream& operator<<(std::ostream& output, const Token& token)
{
    output << "Token: { " << std::endl;
    output << "\tlexeme: " << token.lexeme << std::endl;
    if (token.literal.has_value()) {

        output << "\tliteral: " << token.literal.value() << std::endl;
    }
    output << "\tline " << token.line << std::endl;
    output << "}" << std::endl;

    return output;
}

Scanner::Scanner(std::string&& source_)
    : source(std::move(source_))
{
}

std::vector<Token> Scanner::ScanTokens()
{
    while (!IsAtEnd()) {
        start = current;
        ScanToken();
    }

    tokens.emplace_back(TokenType::ENDOF, "", line);

    return tokens;
}

void Scanner::ScanToken()
{
    char c = Advance();
    switch (c) {
    case '(':
        AddToken(TokenType::LEFT_PAREN);
        break;
    case ')':
        AddToken(TokenType::RIGHT_PAREN);
        break;
    case '{':
        AddToken(TokenType::LEFT_BRACE);
        break;
    case '}':
        AddToken(TokenType::RIGHT_BRACE);
        break;
    case ',':
        AddToken(TokenType::COMMA);
        break;
    case '.':
        AddToken(TokenType::DOT);
        break;
    case '-':
        AddToken(TokenType::MINUS);
        break;
    case '+':
        AddToken(TokenType::PLUS);
        break;
    case ';':
        AddToken(TokenType::SEMICOLON);
        break;
    case '*':
        AddToken(TokenType::STAR);
        break;
    case '!':
        AddToken(Match('=') ? TokenType::BANG_EQUAL : TokenType::BANG);
        break;
    case '=':
        AddToken(Match('=') ? TokenType::EQUAL_EQUAL : TokenType::EQUAL);
        break;
    case '<':
        AddToken(Match('=') ? TokenType::LESS_EQUAL : TokenType::LESS);
        break;
    case '>':
        AddToken(Match('=') ? TokenType::GREATER_EQUAL : TokenType::GREATER);
        break;
    case '/':
        if (Match('/')) {
            while (Peek() != '\n' && !IsAtEnd())
                ++current;
        } else {
            AddToken(TokenType::SLASH);
        }
        break;
    case ' ':
    case '\r':
    case '\t':
        // Ignore whitespace.
        break;
    case '\n':
        line++;
        break;
    case '"':
        String();
        break;
    default:
        if (IsDigit(c)) {
            Number();
        } else if (IsAlpha(c)) {
            Identifier();
        } else {
            error(line, "Unexpected character.");
        }
    }
}

void Scanner::AddToken(const TokenType& type)
{
    tokens.push_back({ type, source.substr(start, current - start), line });
}

void Scanner::AddToken(const TokenType& type, Literal&& literal_)
{
    tokens.emplace_back(type, source.substr(start, current - start), line, std::move(literal_));
}

bool Scanner::IsAtEnd() const
{
    return current >= source.length();
}

char Scanner::Advance()
{
    return source.at(current++);
}

bool Scanner::Match(const char& expected)
{
    if (IsAtEnd())
        return false;

    if (source.at(current) != expected)
        return false;

    ++current;
    return true;
}

char Scanner::Peek()
{
    if (IsAtEnd())
        return '\0';
    return source.at(current);
}

char Scanner::PeekNext()
{
    if (current + 1 >= source.length())
        return '\0';
    return source.at(current + 1);
}

void Scanner::String()
{
    while (Peek() != '"' && !IsAtEnd()) {
        if (Peek() == '\n')
            line++;

        ++current;
    }

    if (IsAtEnd()) {
        error(line, "Unterminated string.");
        return;
    }

    // Trim the surrounding quotes.
    std::string literal_value = source.substr(start + 1, current - start - 1);

    // The closing ".
    ++current;

    AddToken(TokenType::STRING, Literal { std::move(literal_value) });
}

void Scanner::Number()
{
    while (IsDigit(Peek()))
        ++current;

    // Look for a fractional part.
    if (Peek() == '.' && IsDigit(PeekNext())) {
        // Consume the "."
        Advance();

        while (IsDigit(Peek()))
            Advance();
    }

    AddToken(TokenType::NUMBER, Literal { atof(source.substr(start, current).c_str()) });
}

void Scanner::Identifier()
{
    while (IsAlphaNumeric(Peek()))
        Advance();

    TokenType type = TokenType::IDENTIFIER;

    std::string text = source.substr(start, current - start);
    auto typeIt = keywords.find(text);
    if (typeIt != keywords.end())
        type = typeIt->second;

    AddToken(type);
}

bool Scanner::IsDigit(char c) const
{
    return c >= '0' && c <= '9';
}

bool Scanner::IsAlpha(char c) const
{
    return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
}

bool Scanner::IsAlphaNumeric(char c) const
{
    return IsAlpha(c) || IsDigit(c);
}
