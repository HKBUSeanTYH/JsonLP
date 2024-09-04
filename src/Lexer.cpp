#include "Lexer.hpp"

namespace {
    void lex_left_brace(Lexer& lexer) {
        lexer.pushback_token(LexToken {TokenType::LEFT_BRACE, "{"});
    }

    void lex_right_brace(Lexer& lexer) {
        lexer.pushback_token(LexToken {TokenType::RIGHT_BRACE, "}"});
    }

    void lex_left_bracket(Lexer& lexer) {
        lexer.pushback_token(LexToken {TokenType::LEFT_BRACKET, "["});
    }

    void lex_right_bracket(Lexer& lexer) {
        lexer.pushback_token(LexToken {TokenType::RIGHT_BRACKET, "]"});
    }

    void lex_colon(Lexer& lexer) {
        lexer.pushback_token(LexToken {TokenType::COLON, ":"});
    }

    void lex_comma(Lexer& lexer) {
        lexer.pushback_token(LexToken {TokenType::RIGHT_BRACE, ","});
    }

    void lex(std::istringstream& iss, Lexer& lexer) {
        std::string_view str_view {iss.view()};
        size_t current_pos{0}, str_length {str_view.length()};
        while (current_pos < str_length) {
            char current_char {str_view[current_pos]};
            if (std::isspace(current_char)) {
                ++current_pos;
                continue;
            }
        }
    }
}

void Lexer::pushback_token(const LexToken& token) {
    this->tokens.push_back(token);
}

std::istream& operator >>(std::istream& is, Lexer& lexer) {
    std::istream::sentry sentry{is};  //trims leading whitespace
    if (sentry) {
        std::istreambuf_iterator<char> start(is), end;
        std::string input_str(start, end);
        std::istringstream iss{input_str};
        lex(iss, lexer);
    } else {
        is.setstate(is.rdstate() | std::ios_base::failbit);
    }
    return is;
}

std::istringstream& operator >>(std::istringstream& iss, Lexer& lexer) {
    std::istringstream::sentry sentry{iss};  //trims leading whitespace
    if (sentry) {
        lex(iss, lexer);
    } else {
        iss.setstate(iss.rdstate() | std::ios_base::failbit);
    }
    return iss;
}