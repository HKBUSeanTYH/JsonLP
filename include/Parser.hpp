#ifndef PARSER_DEF
#define PARSER_DEF
#include <deque>
#include <variant>
#include "LexToken.hpp"
#include "JsonLPExceptions.hpp"
#include "JsonNode.hpp"

//TODO: JsonNode/JsonVariant class
using JsonParsingResult = std::variant<std::monostate, JsonLPExceptions, JsonNode>;

class Parser {
    public:
        JsonParsingResult parseValue(std::deque<LexToken>&);
};
#endif