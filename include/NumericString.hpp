#ifndef NUMERIC_STRING_DEF
#define NUMERIC_STRING_DEF
#include <cctype>
namespace NumericString {
    bool is_plus_or_minus(char c);

    bool is_plus_minus_or_digit(char c);

    bool is_plus_minus_or_floating_point (char c);

    bool is_valid_numeric_string_start(char c);
}
#endif