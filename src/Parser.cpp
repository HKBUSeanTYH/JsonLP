#include "Parser.hpp"

namespace {
    JsonParsingResult parseObject(std::vector<LexToken>::const_iterator&, std::vector<LexToken>::const_iterator&);
    JsonParsingResult parseArray(std::vector<LexToken>::const_iterator&, std::vector<LexToken>::const_iterator&);

    JsonParsingResult parseValue(std::vector<LexToken>::const_iterator& curr, std::vector<LexToken>::const_iterator& end) {
        auto& val {*curr};
        if (val.token_type == TokenType::LEFT_BRACE) {
            return parseObject(curr, end);
        } else if (val.token_type == TokenType::LEFT_BRACKET) {
            return parseArray(curr, end);
        } else if (val.token_type == TokenType::BOOLEAN) {
            ++curr;
            return (val.value == "true");
        } else if (val.token_type == TokenType::INTEGRAL) {
            ++curr;
            return std::stoi(val.value);
        } else if (val.token_type == TokenType::FLOATING_POINT) {
            ++curr;
            return std::stod(val.value);
        } else if (val.token_type == TokenType::STRING) {
            ++curr;
            return val.value;
        } else if (val.token_type == TokenType::NULL_TYPE) {
            ++curr;
            return nullptr;
        } else {
            return PossibleExceptions{JsonSyntaxException};
        }
    }

    PossibleExceptions parseKeyValueIntoMap(std::map<std::string, JsonNode>& obj, std::vector<LexToken>::const_iterator& curr, std::vector<LexToken>::const_iterator& end) {
        if ((*curr).token_type != TokenType::STRING) { return JsonSyntaxException; } 
        auto& key {*curr};
        ++curr;
        if ((*curr).token_type != TokenType::COLON) { return JsonSyntaxException; }
        ++curr;
        const auto& val = parseValue(curr, end);
        return std::visit(overloaded { [](const auto&){ std::cout<< "exception"; return PossibleExceptions{JsonSyntaxException}; }, 
            [&obj, &key](const JsonNode& node){ std::cout<< "entered"; obj.emplace(key.value, node); return PossibleExceptions{}; } }, val);
    }
    
    JsonParsingResult parseObject(std::vector<LexToken>::const_iterator& curr, std::vector<LexToken>::const_iterator& end) {
        std::map<std::string, JsonNode> obj{};
        ++curr;
        while (curr != end && (*curr).token_type != TokenType::RIGHT_BRACE) {
            const auto& opt {parseKeyValueIntoMap(obj, curr, end)};
            if (opt.has_value()) {
                return opt;
            }
            if ((*curr).token_type == TokenType::COMMA) {
                ++curr;
                continue;
            }
        }
        if ((*curr).token_type != TokenType::RIGHT_BRACE) { return PossibleExceptions{JsonSyntaxException}; }
        ++curr;
        return obj;
    }

    JsonParsingResult parseArray(std::vector<LexToken>::const_iterator& curr, std::vector<LexToken>::const_iterator& end) {
        std::vector<JsonNode> vec{};
        ++curr;
        while (curr != end && (*curr).token_type != TokenType::RIGHT_BRACKET) {
            const auto& result {parseValue(curr, end)};
            const auto& opt = std::visit(overloaded { [](const auto&){ return PossibleExceptions{JsonSyntaxException}; }, 
                [&vec](const JsonNode& node){ vec.push_back(node); return PossibleExceptions{}; } }, result);
            if (opt.has_value()) {
                return opt;
            }
            if ((*curr).token_type == TokenType::COMMA) {
                ++curr;
                continue;
            }
        }
        if ((*curr).token_type != TokenType::RIGHT_BRACKET) { return PossibleExceptions{JsonSyntaxException}; }
        ++curr;
        return vec;
    }
}

JsonParsingResult Parser::parse(const std::vector<LexToken>& tokens) {
    size_t vec_size {tokens.size()};
    auto curr = tokens.begin();
    auto end = tokens.end();
    if (vec_size > 1) {
        if (tokens[0].token_type == TokenType::LEFT_BRACE && tokens[vec_size-1].token_type == TokenType::RIGHT_BRACE) {
            return parseObject(curr, end);
        } else if (tokens[0].token_type == TokenType::LEFT_BRACKET && tokens[vec_size-1].token_type == TokenType::RIGHT_BRACKET) {
            return parseArray(curr, end);
        } else {
            return JsonParsingResult{PossibleExceptions{JsonSyntaxException}};
        }
    } else if (vec_size == 1) {
        //token must be a value type token
        return parseValue(curr, end);
    } else {
        return JsonParsingResult{PossibleExceptions{JsonSyntaxException}};
    }
}