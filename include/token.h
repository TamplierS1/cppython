#ifndef TOKEN_H
#define TOKEN_H

#include <string_view>
#include <variant>
#include <optional>

#include "common.h"

namespace cppython
{
// clang-format off
enum class TokenType
{
    Number, String, Identifier,
    Plus, Minus, Slash, Star,
    RightParen, LeftParen, Dot,
    Error
};
// clang-format on

class Token
{
public:
    Token(TokenType type, std::string_view lexeme,
          std::optional<Value> value = std::nullopt)
        : m_type(type)
        , m_literal_value(std::move(value))
        , m_lexeme(lexeme)
    {
    }

    [[nodiscard]] constexpr TokenType type() const noexcept
    {
        return m_type;
    }
    [[nodiscard]] std::optional<Value> value() const noexcept
    {
        return m_literal_value;
    }
    [[nodiscard]] constexpr std::string_view lexeme() const noexcept
    {
        return m_lexeme;
    }

private:
    TokenType m_type;
    std::optional<Value> m_literal_value;
    std::string m_lexeme;
};

}

#endif  // TOKEN_H
