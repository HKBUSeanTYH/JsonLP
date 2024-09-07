#include "NumericString.hpp"

namespace NumericString {
    bool is_plus_or_minus(const char& c) {
        return (c == '+' || c == '-');
    }

    bool is_plus_minus_or_digit(const char& c) {
        return (std::isdigit(c) || is_plus_or_minus(c));
    }

    bool is_plus_minus_or_floating_point (const char& c) { 
        return (c == '.' || is_plus_or_minus(c));
    }

    bool is_plus_minus_floating_or_exponent(const char& c) { 
        return (c == 'e' || is_plus_minus_or_floating_point(c));
    }

    bool is_valid_numeric_string_start(const char& c) { 
        return (std::isdigit(c) || is_plus_minus_or_floating_point(c));
    }

    bool valid_numeric_string_characters(const char& c) {
        return (std::isdigit(c) || is_plus_minus_floating_or_exponent(c));
    }
}