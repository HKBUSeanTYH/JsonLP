#include <iostream>
#include <Lexer.hpp>

int main() {
    // std::cout << "Hello World from JsonLP\n";
    Lexer lexer{};
    std::ifstream test2("./resources/temp.json");
    // std::istringstream test2("{\"test\": \"temp\"}");
    test2 >> lexer;

    std::cout << lexer;
}