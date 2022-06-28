#include "doctest.h"

#include "Scanner.h"

namespace test {

bool compare_float(float x, float y, float epsilon = 0.001f)
{
    if (fabs(x - y) < epsilon)
        return true;
    return false;
}

inline void CompareTokens(const std::vector<Token>& expected, const std::vector<Token>& result)
{
    REQUIRE_EQ(expected.size(), result.size());

    for (size_t i = 0; i < expected.size(); ++i) {
        REQUIRE_EQ(expected[i].type, result[i].type);
        REQUIRE_EQ(expected[i].lexeme, result[i].lexeme);
        REQUIRE_EQ(expected[i].line, result[i].line);
        if (expected[i].literal.has_value() || result[i].literal.has_value()) {
            CHECK(expected[i].literal.has_value());
            CHECK(result[i].literal.has_value());
            REQUIRE_EQ(expected[i].literal->value, result[i].literal->value);
        }
    }
}

TEST_CASE("Scanner: punctuators")
{

    Scanner scanner("(() ) { } , . - + ; * ! != = == < <= > >= / //");

    std::vector<Token> expected = {
        { TokenType::LEFT_PAREN, "(", 1 },
        { TokenType::LEFT_PAREN, "(", 1 },
        { TokenType::RIGHT_PAREN, ")", 1 },
        { TokenType::RIGHT_PAREN, ")", 1 },
        { TokenType::LEFT_BRACE, "{", 1 },
        { TokenType::RIGHT_BRACE, "}", 1 },
        { TokenType::COMMA, ",", 1 },
        { TokenType::DOT, ".", 1 },
        { TokenType::MINUS, "-", 1 },
        { TokenType::PLUS, "+", 1 },
        { TokenType::SEMICOLON, ";", 1 },
        { TokenType::STAR, "*", 1 },
        { TokenType::BANG, "!", 1 },
        { TokenType::BANG_EQUAL, "!=", 1 },
        { TokenType::EQUAL, "=", 1 },
        { TokenType::EQUAL_EQUAL, "==", 1 },
        { TokenType::LESS, "<", 1 },
        { TokenType::LESS_EQUAL, "<=", 1 },
        { TokenType::GREATER, ">", 1 },
        { TokenType::GREATER_EQUAL, ">=", 1 },
        { TokenType::SLASH, "/", 1 },
        { TokenType::ENDOF, "", 1 },
    };

    std::vector<Token>
        tokens = scanner.ScanTokens();

    CompareTokens(expected, tokens);
}

TEST_CASE("Scanner: strings")
{
    Scanner scanner(R"(
    ""
    "string"
    )");

    const auto tokens = scanner.ScanTokens();

    const std::vector<Token> expected = {
        { TokenType::STRING, "\"\"", 2, Literal { "" } },
        { TokenType::STRING, "\"string\"", 3, Literal { "string" } },
        { TokenType::ENDOF, "", 4 }
    };
    CompareTokens(expected, tokens);
}

TEST_CASE("Scanner: numbers")
{
    Scanner scanner(R"(
    123
    123.456
    .456
    123.
    )");

    const auto tokens = scanner.ScanTokens();

    const std::vector<Token> expected = {
        { TokenType::NUMBER, "123", 2, Literal { 123 } },
        { TokenType::NUMBER, "123.456", 3, Literal { 123.456 } },
        { TokenType::DOT, ".", 4 },
        { TokenType::NUMBER, "456", 4, Literal { 456 } },
        { TokenType::NUMBER, "123", 5, Literal { 123 } },
        { TokenType::DOT, ".", 5 },
        { TokenType::ENDOF, "", 6 }
    };
    CompareTokens(expected, tokens);
}

TEST_CASE("Scanner: identifiers")
{
    Scanner scanner(R"(
    andy formless fo _ _123 _abc ab123
    abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_
    )");

    const auto tokens = scanner.ScanTokens();

    const std::vector<Token> expected = {
        { TokenType::IDENTIFIER, "andy", 2 },
        { TokenType::IDENTIFIER, "formless", 2 },
        { TokenType::IDENTIFIER, "fo", 2 },
        { TokenType::IDENTIFIER, "_", 2 },
        { TokenType::IDENTIFIER, "_123", 2 },
        { TokenType::IDENTIFIER, "_abc", 2 },
        { TokenType::IDENTIFIER, "ab123", 2 },
        { TokenType::IDENTIFIER, "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ1234567890_", 3 },
        { TokenType::ENDOF, "", 4 }
    };
    CompareTokens(expected, tokens);
}

} // namespace test
