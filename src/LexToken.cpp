#include "LexToken.hpp"

std::ostream& operator<<(std::ostream& os, LexToken& token) {
    using namespace std::string_literals;
    os << "{ \""s << token.value << "\" }"s;
    return os;
}