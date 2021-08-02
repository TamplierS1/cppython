#ifndef ERROR_H
#define ERROR_H

#include "token.h"
#include "vm.h"

namespace cppython
{
class CompileError
{
public:
    // Report error to the user.
    void report() const;

    std::string m_msg;
    Token m_where;
};

class RuntimeError
{
public:
    // Report error to the user.
    void report() const;

    std::string m_msg;
    Chunk m_where;
    int m_line;
};
}

#endif  // ERROR_H
