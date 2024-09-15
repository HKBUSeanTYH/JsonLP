#include <iostream>
#include <sstream>
#include "Lexer.hpp"
#include "Parser.hpp"
#include "JsonNode.hpp"

int main() {
    Lexer lexer{};
    Parser parser{};
    // std::ifstream iss("./resources/temp.json");
    std::istringstream iss("{\"test\": \"temp\"}");
    iss >> lexer;
    std::cout << lexer << std::endl;
    auto result {parser.parse(lexer.get_tokens())};
    std::visit(overloaded {[](auto& any){ std::cout << "Exception" << std::endl; }, [](const JsonNode& node){ std::cout << node << std::endl; } }, result);
    lexer.clear_tokens();

    iss.str("{\"test\": 0.123}");
    iss >> lexer;
    std::cout << lexer << std::endl;
    auto result2 {parser.parse(lexer.get_tokens())};
    std::visit(overloaded {[](auto& any){ std::cout << "Exception" << std::endl; }, [](const JsonNode& node){ std::cout << node << std::endl; } }, result2);
    lexer.clear_tokens();

    iss.str("789");
    iss >> lexer;
    std::cout << lexer << std::endl;
    auto result3 {parser.parse(lexer.get_tokens())};
    std::visit(overloaded {[](auto& any){ std::cout << "Exception" << std::endl; }, [](const JsonNode& node){ std::cout << node << std::endl; } }, result3);
    lexer.clear_tokens();
}