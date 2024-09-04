#include "Lexer.hpp"

namespace {
    void lex_token(Lexer& lexer, const TokenType& type, const std::string& token_string) {
        lexer.pushback_token(LexToken {type, token_string});
    }

    void lex(std::istringstream& iss, Lexer& lexer) {
        std::string_view str_view {iss.view()};
        size_t current_pos{0}, str_length {str_view.length()};
        while (current_pos < str_length) {
            char current_char {str_view[current_pos]};
            if (std::isspace(current_char)) {
                ++current_pos;
                continue;
            } else if (current_char == '{') {
                ++current_pos;
                lex_token(lexer, TokenType::LEFT_BRACE, "{");
                continue;
            } else if (current_char == '}') {
                ++current_pos;
                lex_token(lexer, TokenType::RIGHT_BRACE, "}");
                continue;
            } else if (current_char == '[') {
                ++current_pos;
                lex_token(lexer, TokenType::LEFT_BRACKET, "[");
                continue;
            } else if (current_char == ']') {
                ++current_pos;
                lex_token(lexer, TokenType::RIGHT_BRACKET, "]");
                continue;
            } else if (current_char == ':') {
                ++current_pos;
                lex_token(lexer, TokenType::COLON, ":");
                continue;
            } else if (current_char == ',') {
                ++current_pos;
                lex_token(lexer, TokenType::RIGHT_BRACE, ",");
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