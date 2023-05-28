#pragma once

#include <string>
#include <vector>

namespace Klang {
    /**
     * @brief Enumerates the different types of tokens.
     *
     */
    enum class TokenType {
        Literal,     // String, number, boolean, etc.
        Identifier,  // Variable name, function name, etc.
        Keyword,     // while, if, elif, else, etc.
        Operator,    // +, -, *, /, %, etc.
        Punctuation, // '(', ')', '{', '}', ',', etc.
    };

    /**
     * @brief Token.
     *
     */
    struct Token {
        std::string value;
        TokenType type;
    };

    /**
     * @brief Tokenize the string
     *
     * @param source
     * @return std::vector<Token>
     */
    std::vector<Token> tokenize(std::string source);
} // namespace Klang