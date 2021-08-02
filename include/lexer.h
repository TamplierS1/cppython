#ifndef LEXER_H
#define LEXER_H

#include <string>
#include <vector>
#include <optional>

#include "token.h"
#include "error.h"

namespace cppython
{
class Lexer
{
public:
    // Reads the contents of the file `path`.
    // Returns a vector of tokens or nothing, if an error happened.
    std::optional<std::vector<Token>> read_file(std::string_view path);

private:
    // Splits the source into tokens.
    std::optional<CompileError> scan_file();
    std::optional<CompileError> scan();

    void add_token(TokenType type,
                   const std::optional<Value>& value = std::nullopt) noexcept;

    constexpr char advance() noexcept
    {
        if (is_end())
        {
            return '\0';
        }
        return m_source[m_current++];
    }
    constexpr char peek() noexcept
    {
        if (is_end())
        {
            return '\0';
        }
        return m_source[m_current];
    }
    constexpr char peek_next() noexcept
    {
        if (m_current + 1 >= m_source.length())
        {
            return '\0';
        }
        return m_source[m_current + 1];
    }
    constexpr bool is_end() noexcept
    {
        return m_current >= m_source.length();
    }
    [[nodiscard]] std::string current_lexeme() const noexcept
    {
        return m_source.substr(m_start, m_current - m_start);
    }

    void number();

    std::vector<Token> m_tokens;
    std::string m_source;
    // Position of the character that is being tokenized.
    int m_current = 0;
    // Start of the current lexeme.
    int m_start = 0;
};

}

#endif  // LEXER_H
