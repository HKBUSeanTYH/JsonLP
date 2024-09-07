#include <iostream>
#include <Lexer.hpp>

int main() {
    // std::cout << "Hello World from JsonLP\n";
    Lexer lexer{};
    // std::ifstream iss("./resources/temp.json");
    std::istringstream iss("{\"test\": \"temp\"}");
    iss >> lexer;
    std::cout << lexer << std::endl;
    lexer.clear_tokens();

    iss.str("{\"test\": 0.123}");
    iss >> lexer;
    std::cout << lexer << std::endl;
    lexer.clear_tokens();

    iss.str("789");
    iss >> lexer;
    std::cout << lexer << std::endl;
    lexer.clear_tokens();
}