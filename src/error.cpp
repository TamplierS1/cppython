#include <fmt/color.h>

#include "error.h"

namespace cppython
{
void CompileError::report() const
{
    // TODO: calculate the line and the column of the token.
    //    fmt::print("\n[{}, {}]", m_where->line(), m_where->column());
    fmt::print(fmt::emphasis::italic | fg(fmt::color::red), " Error at '");
    fmt::print(fmt::emphasis::bold | fg(fmt::color::white), "{}", m_where.lexeme());
    fmt::print(fmt::emphasis::italic | fg(fmt::color::red), "': {}\n\n", m_msg);
    //        fmt::print(fg(fmt::color::dark_olive_green), "\t{}\n\n", src_str);
}

void RuntimeError::report() const
{
    fmt::print("\n[{}]", m_line);
    fmt::print(fmt::emphasis::italic | fg(fmt::color::red), " Error: ");
    fmt::print(fmt::emphasis::italic | fg(fmt::color::red), " {}\n\n", m_msg);

    // TODO: print the chunk that caused the error.
    //    for (auto instr : m_where.m_code)
    //    {
    //        fmt::print(fmt::emphasis::bold | fg(fmt::color::white), "{}", instr.m_line);
    //        fmt::print(fmt::emphasis::bold | fg(fmt::color::white), " {}", instr.);
    //
    //    }
}
}
