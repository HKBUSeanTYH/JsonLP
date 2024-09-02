#include <iostream>
#include <Lexer.hpp>

int main() {
    std::cout << "Hello World from JsonLP\n";
    Lexer lexer{};
    std::ifstream test2("./resources/temp.json");
    test2 >> lexer;
}