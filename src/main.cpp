#include <fmt/core.h>

#include "lexer.h"
#include "vm.h"

using namespace cppython;

int main(int argc, char** argv)
{
    std::string path;

    if (argc == 2)
    {
        path = argv[1];
    }
    else
    {
        fmt::print("usage: cppython [file_path]");
        return EXIT_FAILURE;
    }

    Lexer lexer;
    auto tokens = lexer.read_file(path);
    if (!tokens.has_value())
    {
        return EXIT_FAILURE;
    }

    Vm vm;
    auto code = Chunk{};
    code.code.emplace_back(Instruction{{OpConstant, 0}, 0});
    code.code.emplace_back(Instruction{{OpConstant, 1}, 0});
    code.code.emplace_back(Instruction{{OpAdd}, 0});
    code.code.emplace_back(Instruction{{OpPrint}, 0});
    code.code.emplace_back(Instruction{{OpConstant, 2}, 0});
    code.code.emplace_back(Instruction{{OpAdd}, 0});
    code.code.emplace_back(Instruction{{OpPrint}, 0});

    code.constants.emplace_back(15);
    code.constants.emplace_back(30);
    code.constants.emplace_back(6);

    vm.execute(code);
    //    for (const auto& token : *tokens)
    //    {
    //        fmt::print("lexeme: {}; type: {}\n", token.lexeme(), token.type());
    //    }
    return EXIT_SUCCESS;
}
