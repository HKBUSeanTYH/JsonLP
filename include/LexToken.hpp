#ifndef LEX_TOKEN_DEF
#define LEX_TOKEN_DEF
#include <string>
#include "TokenType.hpp"

struct LexToken {
    TokenType token_type;
    std::string value;

    LexToken() = delete;
    explicit LexToken(const TokenType t, const std::string s) : token_type{t}, value{s} {};
    friend std::ostream& operator<<(std::ostream&, LexToken&);
};

#endif