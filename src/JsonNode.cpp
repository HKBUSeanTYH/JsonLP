#include "JsonNode.hpp"

std::ostream& operator <<(std::ostream& os, JsonNode& json_val) {
    std::visit(overloaded{
        [&os](std::monostate &){ os << "Empty JsonValue"; }, // An uninitialized json object, probably an error
        [&os](std::nullptr_t &){ os << "null";},
        [&os](auto & val){ os << val;},
        [&os](std::vector<JsonNode> &vec){
            os << "[ ";
            for (size_t i = 0; i < vec.size(); ++i) {
                if (i != 0) {
                    os << ", ";
                }
                os << vec[i];
            }
            os << " ]";
        },
        [&os](std::map<std::string, JsonNode> & val){
            os << "{ ";
            auto begin = val.begin();
            for (auto i = val.begin(); i != val.end();++i) {
                if (i != begin) {
                    os << ", ";
                }
                os << "(" <<i->first << ":" << i->second << ")";
            }
            os << " }";
        }
    }, json_val);

    return os;
}