#ifndef JSON_ERROR_DEF
#define JSON_ERROR_DEF
#include <optional>
enum PossibleExceptions {
    JsonSyntaxException,  // missing/extra commas, improper use of quotes, mismatched brackets/braces
    DataTypeMismatchException,  //incorrect data types(?)
    MalformedJsonException // trailing commas, unescaped (special) characters
};
using JsonLexerParserException = std::optional<PossibleExceptions>;
#endif