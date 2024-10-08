#ifndef PARSER_DEF
#define PARSER_DEF
#include <vector>
#include <variant>
#include "LexToken.hpp"
#include "JsonLPExceptions.hpp"
#include "JsonNode.hpp"

//TODO: JsonNode/JsonVariant class
using JsonParsingResult = std::variant<std::monostate, PossibleExceptions, JsonNode>;

class Parser {
    public:
        JsonParsingResult parse(std::vector<LexToken>&);
};
#endif