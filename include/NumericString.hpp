#ifndef NUMERIC_STRING_DEF
#define NUMERIC_STRING_DEF
#include "JsonLexerParserExceptions.hpp"
#include "LexToken.hpp"
#include "Lexer.hpp"
namespace NumericString {
    bool is_plus_or_minus(const char& c);

    bool is_plus_minus_or_digit(const char& c);

    bool is_plus_minus_or_floating_point (const char& c);

    bool is_valid_numeric_string_start(const char& c);
}
#endif