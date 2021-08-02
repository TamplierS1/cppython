#include <cassert>

#include <fmt/core.h>

#include "value.h"

namespace cppython
{
Value Value::add(const Value& val1, const Value& val2)
{
    assert(val1.m_val.index() <= 2 && val2.m_val.index() <= 2 &&
           "Invalid types to "
           "`Value::add'.");

    // This is the best way I know to do this.
    // Still looks bad though.
    switch (val1.m_val.index())
    {
        case 0:
        {
            switch (val2.m_val.index())
            {
                case 0:
                    return Value{std::get<0>(val1.m_val) + std::get<0>(val2.m_val)};
                case 1:
                    return Value{std::get<0>(val1.m_val) + std::get<1>(val2.m_val)};
                case 2:
                    return Value{std::get<0>(val1.m_val) + std::get<2>(val2.m_val)};
            }
        }
        case 1:
        {
            switch (val2.m_val.index())
            {
                case 0:
                    return Value{std::get<1>(val1.m_val) + std::get<0>(val2.m_val)};
                case 1:
                    return Value{std::get<1>(val1.m_val) + std::get<1>(val2.m_val)};
                case 2:
                    return Value{std::get<1>(val1.m_val) + std::get<2>(val2.m_val)};
            }
        }
        case 2:
        {
            switch (val2.m_val.index())
            {
                case 0:
                    return Value{std::get<2>(val1.m_val) + std::get<0>(val2.m_val)};
                case 1:
                    return Value{std::get<2>(val1.m_val) + std::get<1>(val2.m_val)};
                case 2:
                    return Value{std::get<2>(val1.m_val) + std::get<2>(val2.m_val)};
            }
        }
    }
}

void Value::print() const
{
    switch (m_val.index())
    {
        case 0:
            fmt::print("{}", std::get<int>(m_val));
            break;
        case 1:
            fmt::print("{}", std::get<double>(m_val));
            break;
        case 2:
            fmt::print("{}", std::get<bool>(m_val));
            break;
        case 3:
            fmt::print("{}", std::get<std::string>(m_val));
            break;
    }
}

}
