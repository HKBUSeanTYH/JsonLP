#include "JsonNode.hpp"

std::ostream& operator <<(std::ostream& os, JsonNode& json_val) {
    std::visit(overloaded{
        [&os](std::monostate &){ os << "Empty JsonValue"; }, // An uninitialized json object, probably an error
        [&os](std::nullptr_t &){ os << "null";},
        [&os](std::string & val){ os << "\"" << val << "\"";},
        [&os](auto & val){ os << val; },
        [&os](std::vector<JsonNode> &vec){
            os << "[ ";
            if (vec.size() >= 1) {
                if (vec.size() > 1) {
                    std::for_each_n(vec.begin(), vec.size()-1, [&os](JsonNode& token){ os << token << ", "; });
                }
                os << vec.at(vec.size()-1);
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
                os << "\"" << i->first << "" << " : " << i->second;
            }
            os << " }";
        }
    }, json_val);

    return os;
}