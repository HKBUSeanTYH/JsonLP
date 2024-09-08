#ifndef LEXER_DEF
#define LEXER_DEF
#include "LexToken.hpp"
#include <vector>
#include <stack>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <algorithm>
class Lexer {
    std::vector<LexToken> tokens;
    std::stack<TokenType> array_and_object_stack;
    public:
        Lexer(): tokens{}, array_and_object_stack{} {};
        void pushback_token(const LexToken&);
        void clear_tokens();

        bool is_stack_empty();
        bool check_token_type(const TokenType&);
        void push_stack(const TokenType&);
        void pop_stack();
        void clear_stack();

        friend std::istream& operator>>(std::istream&, Lexer&);
        friend std::istringstream& operator>>(std::istringstream&, Lexer&);
        friend std::ostream& operator<<(std::ostream&, Lexer&);
};
#endif