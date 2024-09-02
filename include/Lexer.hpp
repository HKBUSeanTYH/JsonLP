#ifndef LEXER_DEF
#define LEXER_DEF
#include "LexToken.hpp"
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
class Lexer {
    std::vector<LexToken> tokens;
    public:
        Lexer(): tokens{} {};
        friend std::istream& operator>>(std::istream&, Lexer&);
        friend std::istringstream& operator>>(std::istringstream&, Lexer&);
};
#endif