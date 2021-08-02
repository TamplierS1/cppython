#include <sstream>
#include <fstream>
#include "lexer.h"

namespace cppython
{
std::optional<std::vector<Token>> Lexer::read_file(std::string_view path)
{
    std::ifstream input_file{path.data()};
    input_file.exceptions(std::ifstream::badbit | std::ifstream::failbit);

    // Read the whole file into `m_source`
    std::ostringstream source;
    source << input_file.rdbuf();
    m_source = source.str();

    auto error = scan_file();
    if (error.has_value())
    {
        return std::nullopt;
    }
    return m_tokens;
}

std::optional<CompileError> Lexer::scan_file()
{
    while (!is_end())
    {
        auto error = scan();
        if (error.has_value())
        {
            return error;
        }
        m_start = m_current;
    }
    return std::nullopt;
}

std::optional<CompileError> Lexer::scan()
{
    char c = advance();
    switch (c)
    {
        case '+':
            add_token(TokenType::Plus);
            break;
        case '-':
            add_token(TokenType::Minus);
            break;
        case '*':
            add_token(TokenType::Star);
            break;
        case '/':
            add_token(TokenType::Slash);
            break;
        case '(':
            add_token(TokenType::LeftParen);
        case ')':
            add_token(TokenType::RightParen);
        case ' ':
        case '\t':
        case '\r':
        case '\n':
            break;
        default:
            if (std::isdigit(c))
            {
                number();
            }
            else
            {
                Token token{TokenType::Error, current_lexeme()};
                auto e = CompileError{"Unexpected character.", token};
                e.report();
                return e;
            }
    }

    return std::nullopt;
}

void Lexer::add_token(TokenType type, const std::optional<Value>& value) noexcept
{
    m_tokens.emplace_back(type, current_lexeme(), value);
    m_start = m_current - (m_current - m_start);
}

void Lexer::number()
{
    while (std::isdigit(peek()))
    {
        advance();
    }

    // Handle decimals.
    if (peek() == '.' && std::isdigit(peek_next()))
    {
        advance();
        while (std::isdigit(peek()))
        {
            advance();
        }

        add_token(TokenType::Number, Value{std::stod(current_lexeme())});
    }
    else
    {
        add_token(TokenType::Number, Value{std::stoi(current_lexeme())});
    }
}
}
