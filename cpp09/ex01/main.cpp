#include "RPN.hpp"
#include <iostream>

int main(int argc, const char* argv[])
{
    if (argc == 1)
        return 0;
    else if (argc > 2)
    {
        std::cerr << "error\n";
        return 1;
    }

    RPN rpn;
    try
    {
        rpn.calculate(argv[1]);  
    }
    catch(const std::exception& e)
    {
        std::cerr << "error: " << e.what() << "\n";
        return 1;
    }
    return 0;
}
