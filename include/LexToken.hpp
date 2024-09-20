#ifndef LEX_TOKEN_DEF
#define LEX_TOKEN_DEF
#include <string>
#include <iostream>
#include "TokenType.hpp"

struct LexToken {
    TokenType token_type;
    std::string value;

    LexToken() = delete;
    explicit LexToken(TokenType t, std::string s) : token_type{t}, value{std::move(s)} {};
    friend std::ostream& operator<<(std::ostream&, LexToken&);
};

#endif