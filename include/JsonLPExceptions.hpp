#ifndef JSON_LEXER_PARSER_EXCEPTIONS_DEF
#define JSON_LEXER_PARSER_EXCEPTIONS_DEF
#include <optional>
enum PossibleExceptions {
    JsonSyntaxException,  // missing/extra commas, improper use of quotes, mismatched brackets/braces
    DataTypeMismatchException,  //incorrect data types(?)
    MalformedJsonException // trailing commas, unescaped (special) characters
};
using JsonLPException = std::optional<PossibleExceptions>;
#endif