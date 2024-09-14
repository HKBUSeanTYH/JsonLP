#include "Parser.hpp"

JsonParsingResult Parser::parseValue(const std::vector<LexToken>& tokens) {
    if (tokens.size() > 1) {
        //first token must be left brace or left bracket
    } else if (tokens.size() == 1) {
        //token must be a value type token
    } else {
        return JsonParsingResult{JsonLPExceptions::JsonSyntaxException};
    }
}