#include "Lexer.hpp"

namespace {
    void lexer_lex(std::istringstream& iss, Lexer& lexer) {
        std::cout << iss.str() << std::endl;
    }
}

std::istream& operator >>(std::istream& is, Lexer& lexer) {
    std::istream::sentry sentry{is};  //trims leading whitespace
    if (sentry) {
        std::istreambuf_iterator<char> start(is), end;
        std::string input_str(start, end);
        std::istringstream iss{input_str};
        lexer_lex(iss, lexer);
    } else {
        is.setstate(is.rdstate() | std::ios_base::failbit);
    }
    return is;
}

std::istringstream& operator >>(std::istringstream& iss, Lexer& lexer) {
    std::istringstream::sentry sentry{iss};  //trims leading whitespace
    if (sentry) {
        lexer_lex(iss, lexer);
    } else {
        iss.setstate(iss.rdstate() | std::ios_base::failbit);
    }
    return iss;
}