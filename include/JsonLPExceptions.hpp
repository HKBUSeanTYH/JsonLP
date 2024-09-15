#ifndef JSON_LEXER_PARSER_EXCEPTIONS_DEF
#define JSON_LEXER_PARSER_EXCEPTIONS_DEF
#include <optional>
enum JsonLPExceptions {
    JsonSyntaxException,  // missing/extra commas, improper use of quotes, mismatched brackets/braces
    DataTypeMismatchException,  //incorrect data types(?)
    UnexpectedEndOfInputException,
    InvalidNumberFormatException,
    UnclosedStringException

};
using PossibleExceptions = std::optional<JsonLPExceptions>;
#endif