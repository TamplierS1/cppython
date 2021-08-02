#ifndef VM_H
#define VM_H

#include <cctype>
#include <vector>
#include <cassert>
#include <array>
#include <stack>
#include <optional>

#include "common.h"

namespace cppython
{
// C-style enums are easier to use here.
enum OpCode
{
    OpAdd,
    OpSubtract,
    OpMultiply,
    OpDivide,
    OpConstant,
    OpPrint,
};

struct Instruction
{
    // All instructions are 32-bit.
    std::array<byte, 4> code;
    int line;
};

struct Chunk
{
    std::vector<Instruction> code;
    std::vector<Value> constants;
};

class Vm
{
public:
    // The returned bool indicates whether an error happened
    // or not.
    bool execute(const Chunk& code);

private:
    Instruction read_instruction()
    {
        assert(!is_end() && "Ran out of instructions.");
        return m_code.code[m_ip++];
    }
    Value read_constant(int index)
    {
        return m_code.constants[index];
    }
    Value pop_stack()
    {
        assert(!m_stack.empty() && "Stack is empty.");

        auto value = m_stack.top();
        m_stack.pop();
        return value;
    }
    Value peak_stack()
    {
        assert(!m_stack.empty() && "Stack is empty.");

        return m_stack.top();
    }
    constexpr void push_stack(const Value& val)
    {
        m_stack.push(val);
    }
    [[nodiscard]] constexpr bool is_end() const noexcept
    {
        return m_ip >= m_code.code.size();
    }

    bool error(std::string_view msg, int line);

    Chunk m_code;
    std::stack<Value> m_stack;
    int m_ip = 0;
};
}

#endif  // VM_H
