#include "Harl.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

enum ExitStatus
{
    Success = 0,
    IncorrectArgc
};

enum ComplaintLevel
{
    Debug,
    Info,
    Warning,
    Error
};

static void checkArgc(int argc)
{
    switch (argc)
    {
    case 1:
        std::cout << "No complaint!\n";
        exit(Success);
        break;
    case 2:
        break;
    default:
        std::cerr << "Sorry say that again?\n";
        exit(IncorrectArgc);
    }
}

static ComplaintLevel getComplaintLevel(const char* arg)
{
    std::string level(arg);

    static const std::string levels[4] = {"DEBUG", "INFO", "WARNING", "ERROR"};
    for (int i = 0; i < 4; i++)
    {
        if (level == levels[i])
            return ((ComplaintLevel)i);
    }
    std::cout << "Probably complaining about insignificant problem.\n";
    exit(Success);
}
static void filteredComplain(const Harl& harl, ComplaintLevel complaint_level)
{
    switch (complaint_level)
    {
    case Debug:
        harl.complain("DEBUG");
    case Info:
        harl.complain("INFO");
    case Warning:
        harl.complain("WARNING");
    case Error:
        harl.complain("ERROR");
    default:
        break;
    }
}

int main(int argc, char const* argv[])
{
    checkArgc(argc);
    ComplaintLevel complaint_level = getComplaintLevel(argv[1]);
    Harl           harl;
    filteredComplain(harl, complaint_level);
    return Success;
}
