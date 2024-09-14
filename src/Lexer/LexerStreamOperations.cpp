#include "Lexer.hpp"
#include "NumericString.hpp"
#include "JsonLPExceptions.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string_view>
#include <algorithm>

namespace {
    void lex_token(Lexer& lexer, const TokenType& type, const std::string token_string) {
        lexer.pushback_token(LexToken {type, token_string});
    }

    PossibleExceptions validate_and_extract_numeric (Lexer& lexer, const std::string_view& sv, const size_t& str_length , size_t& current_pos) {
        bool floating_point_found = false, exponential_found = false;
        size_t starting_pos {current_pos};
        if (NumericString::is_plus_minus_or_floating_point(sv[current_pos])) {
            if (sv[current_pos] == '.') {
                floating_point_found = true;
            }
            if (!std::isdigit(sv[current_pos+1])) {
                return JsonLPExceptions::MalformedJsonException;
            } 
            current_pos += 2;
        }

        while (current_pos < str_length) {
            char current_char {sv[current_pos]};
            if (std::isdigit(current_char)) {
                ++current_pos;
            } else if (current_char == 'e') {
                if (!exponential_found && (NumericString::is_plus_minus_or_digit(sv[current_pos+1]))) {  
                    //if an exponent symbol is not found and + - or digit is after exponent
                    exponential_found = true;
                    current_pos += 2;
                } else {
                    return JsonLPExceptions::MalformedJsonException;
                }
            } else if (current_char == '.' && !floating_point_found) {
                //if floating point and no floating points seen before
                floating_point_found = true;
                if (!std::isdigit(sv[current_pos+1])) {
                    //floating point must be followed by digit
                    return JsonLPExceptions::MalformedJsonException;
                } 
                current_pos += 2;
            } else if (current_char == ',' || current_char == '}' || current_char == ']' || std::isspace(current_char)) {
                //if valid ending delimiter
                if (exponential_found || floating_point_found) {
                    lex_token(lexer, TokenType::FLOATING_POINT, std::string{sv.substr(starting_pos, current_pos-starting_pos)});
                } else {
                    lex_token(lexer, TokenType::INTEGRAL, std::string{sv.substr(starting_pos, current_pos-starting_pos)});
                }
                return {};  //finished lexing numeric, break out
            } else {
                return JsonLPExceptions::MalformedJsonException; //invalid characters
            }
        }
        //if somehow string ended without breaking out, lex the token first and decide if it is malformed later
        //as the string could be completely numeric - "1234"
        if (exponential_found || floating_point_found) {
            lex_token(lexer, TokenType::FLOATING_POINT, std::string{sv.substr(starting_pos, current_pos-starting_pos)});
        } else {
            lex_token(lexer, TokenType::INTEGRAL, std::string{sv.substr(starting_pos, current_pos-starting_pos)});
        }
        return {};
    }

    PossibleExceptions lex(std::istringstream& iss, Lexer& lexer) {
        using namespace std::literals;
        std::string_view str_view {iss.view()};
        size_t current_pos{0}, str_length {str_view.length()};
        while (current_pos < str_length) {
            char current_char {str_view[current_pos]};
            if (std::isspace(current_char)) {
                ++current_pos;
            } else if (current_char == '{') {
                lex_token(lexer, TokenType::LEFT_BRACE, "{");
                lexer.push_stack(TokenType::LEFT_BRACE);
                ++current_pos;
            } else if (current_char == '}') {
                if (!lexer.is_stack_empty() && lexer.check_token_type(TokenType::LEFT_BRACE)) {
                    lexer.pop_stack();
                    lex_token(lexer, TokenType::RIGHT_BRACE, "}");
                    ++current_pos;
                } else {
                    return JsonLPExceptions::MalformedJsonException;
                }
            } else if (current_char == '[') {
                lex_token(lexer, TokenType::LEFT_BRACKET, "[");
                lexer.push_stack(TokenType::LEFT_BRACKET);
                ++current_pos;
            } else if (current_char == ']') {
                if (!lexer.is_stack_empty() && lexer.check_token_type(TokenType::LEFT_BRACKET)) {
                    lexer.pop_stack();
                    lex_token(lexer, TokenType::RIGHT_BRACKET, "]");
                    ++current_pos;
                } else {
                    return JsonLPExceptions::MalformedJsonException;
                }
            } else if (current_char == ':') {
                lex_token(lexer, TokenType::COLON, ":");
                ++current_pos;
            } else if (current_char == ',') {
                lex_token(lexer, TokenType::COMMA, ",");
                ++current_pos;
            } else if (current_char == '"') {
                size_t opening_idx {++current_pos};
                while(current_pos < str_length && str_view[current_pos] != '"') {
                    ++current_pos;
                }
                if (current_pos < str_length && str_view[current_pos] == '"') { // check string has closing
                    lex_token(lexer, TokenType::STRING, std::string{str_view.substr(opening_idx, current_pos - opening_idx)});
                    ++current_pos;
                } else {
                    return JsonLPExceptions::MalformedJsonException;
                }                
            } else if (current_char == 't' && str_view.substr(current_pos, 4) == "true"sv) {
                lex_token(lexer, TokenType::BOOLEAN, "true");
                current_pos += 4;
            } else if (current_char == 'f' && str_view.substr(current_pos, 5) == "false"sv) {
                lex_token(lexer, TokenType::BOOLEAN, "false");
                current_pos += 5;
            } else if (current_char == 'n' && str_view.substr(current_pos, 4) == "null"sv) {
                lex_token(lexer, TokenType::NULL_TYPE, "null");
                current_pos += 4;
            } else if (NumericString::is_valid_numeric_string_start(current_char)) {
                PossibleExceptions output {validate_and_extract_numeric(lexer, str_view, str_length, current_pos)};
                if (output.has_value()) {
                    return output;
                }
            } else {
                return JsonLPExceptions::MalformedJsonException;
            }
        }
        return lexer.is_stack_empty() ? std::nullopt : PossibleExceptions{JsonLPExceptions::MalformedJsonException};
    }
}

std::istream& operator >>(std::istream& is, Lexer& lexer) {
    std::istream::sentry sentry{is};  //trims leading whitespace
    if (sentry) {
        std::istreambuf_iterator<char> start(is), end;
        std::string input_str(start, end);
        std::istringstream iss{input_str};
        PossibleExceptions output {lex(iss, lexer)};
        if (output.has_value()) {
            iss.setstate(iss.rdstate() | std::ios_base::failbit);
        } 
    } else {
        is.setstate(is.rdstate() | std::ios_base::failbit);
    }
    return is;
}

std::istringstream& operator >>(std::istringstream& iss, Lexer& lexer) {
    std::istringstream::sentry sentry{iss};  //trims leading whitespace
    if (sentry) {
        PossibleExceptions output {lex(iss, lexer)};
        if (output.has_value()) {
            iss.setstate(iss.rdstate() | std::ios_base::failbit);
        } 
    } else {
        iss.setstate(iss.rdstate() | std::ios_base::failbit);
    }
    return iss;
}

std::ostream& operator<<(std::ostream& os, Lexer& lexer) {
    std::ostream::sentry sentry {os};
    if (sentry) {
        using namespace std::string_literals;
        os << "[ "s;
        if (lexer.tokens.size() >= 1) {
            if (lexer.tokens.size() > 1) {
                std::for_each_n(lexer.tokens.begin(), lexer.tokens.size()-1, [&os](LexToken& token){ os << token << ", "s; });
            }
            os << lexer.tokens.at(lexer.tokens.size()-1);
        }
        os << " ]"s;
    } else {
        os.setstate(os.rdstate() | std::ios_base::failbit);
    }
    return os;
}