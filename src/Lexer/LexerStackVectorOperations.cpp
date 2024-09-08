#include "Lexer.hpp"

void Lexer::pushback_token(const LexToken& token) {
    this->tokens.push_back(token);
}

void Lexer::clear_tokens() {
    this->tokens.clear();
}

bool Lexer::is_stack_empty() {
    return this->array_and_object_stack.empty();
}

bool Lexer::check_token_type(const TokenType& type) {
    return this->array_and_object_stack.top() == type;
}

void Lexer::push_stack(const TokenType& type) {
    this->array_and_object_stack.push(type);
}

void Lexer::pop_stack() {
    this->array_and_object_stack.pop();
}

void Lexer::clear_stack() {
    while(!this->is_stack_empty()) {
        this->pop_stack();
    }
}