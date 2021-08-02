#ifndef VALUE_H
#define VALUE_H

#include <utility>
#include <variant>
#include <string>

namespace cppython
{
// The order of the types should NOT BE CHANGED.
using Val = std::variant<int, double, bool, std::string>;

struct Chunk;
class Value
{
public:
    explicit Value(Val value)
        : m_val(std::move(value))
    {
    }

    [[nodiscard]] Val& get()
    {
        return m_val;
    }
    // 'add' assumes the `Value`s have correct types.
    // Error handling should be done by the caller.
    static Value add(const Value& val1, const Value& val2);

    // Prints the current value to the console.
    void print() const;

private:
    Val m_val;
};

}

#endif  // VALUE_H
