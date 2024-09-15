#ifndef JSON_NODE_DEF
#define JSON_NODE_DEF
#include <iostream>
#include <variant>
#include <vector>
#include <string>
#include <map>

class JsonNode;
using JsonVariant = std::variant<std::monostate, std::nullptr_t, int, double, bool, std::string, std::vector<JsonNode>, std::map<std::string, JsonNode>>;
template<class... Ts> 
struct overloaded : Ts... { using Ts::operator()...; };
template<class... Ts> overloaded(Ts...) -> overloaded<Ts...>;

class JsonNode : public JsonVariant {
    friend std::ostream& operator <<(std::ostream&, JsonNode&);
    friend std::ostream& operator <<(std::ostream&, const JsonNode&);
    public:
        using JsonVariant::JsonVariant;
};
#endif