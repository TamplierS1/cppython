#include <cstddef>

#include <fmt/core.h>

#include "vm.h"
#include "error.h"

namespace cppython
{
bool Vm::execute(const Chunk& code)
{
#define OPCODE 0

    m_code = code;

    while (!is_end())
    {
        auto instr = read_instruction();
        switch (instr.code[OPCODE])
        {
            case OpAdd:
            {
                Value op2 = pop_stack();
                Value op1 = pop_stack();
                if (op1.get().index() <= 2 && op2.get().index() <= 2)
                {
                    push_stack(Value::add(op1, op2));
                }
                else
                    return error("Can only add together 'int', 'float' and 'bool'",
                                 instr.line);
                break;
            }
            case OpConstant:
            {
                Value constant = read_constant(instr.code[OPCODE + 1]);
                push_stack(constant);
                break;
            }
            case OpPrint:
            {
                peak_stack().print();
                break;
            }
            default:
                return error("Unknown upcode", instr.line);
        }
    }
#undef OPCODE
    return false;
}

bool Vm::error(std::string_view msg, int line)
{
    auto e = RuntimeError{msg.data(), m_code, line};
    e.report();
    return true;
}

}
