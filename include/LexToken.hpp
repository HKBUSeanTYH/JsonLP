#ifndef LEX_TOKEN_DEF
#define LEX_TOKEN_DEF
#include <string>
#include "TokenType.hpp"

struct LexToken {
    TokenType token_type;
    std::string value;

    LexToken() = delete;
    explicit LexToken(TokenType, std::string);
};

#endif