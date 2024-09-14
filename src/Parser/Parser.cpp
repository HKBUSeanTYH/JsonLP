#include "Parser.hpp"

namespace {
    template<class T>
    void eraseAtIndex(std::deque<T>& vec,size_t& idx) {
        vec.erase(vec.begin() + idx);
    }
}

JsonParsingResult Parser::parseValue(std::deque<LexToken>& tokens) {
    size_t vec_size {tokens.size()};
    if (vec_size > 1) {
        if (tokens[0].token_type == TokenType::LEFT_BRACE && tokens[vec_size-1].token_type == TokenType::RIGHT_BRACE) {
            
        } else if (tokens[0].token_type == TokenType::LEFT_BRACKET && tokens[vec_size-1].token_type == TokenType::RIGHT_BRACKET) {

        } else {
            return JsonParsingResult{JsonLPExceptions::JsonSyntaxException};
        }
    } else if (vec_size == 1) {
        //token must be a value type token
    } else {
        return JsonParsingResult{JsonLPExceptions::JsonSyntaxException};
    }
}