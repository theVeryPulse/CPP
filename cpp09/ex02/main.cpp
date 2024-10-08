#include "PmergeMe.hpp"
#include <iostream> // cout
#include <vector> // vector
#include <list> // list
#include <algorithm> // std::sort
#include <sstream> // istringstream
#include <limits> // numeric_limits
#include <stdexcept> // std::invalid_argument ...
#include <ctime>

void printErrMsg(const std::string& msg, bool newline = true)
{
    std::cerr << "error: " << msg;
    if (newline)
        std::cerr << "\n";
}

void checkPositiveInt(const char** argv)
{
    for (const char** arg = argv; *arg != NULL; ++arg)
    {
        for (const char* c = *arg; *c != '\0'; ++c)
        {
            if (!isdigit(*c))
                throw std::invalid_argument(
                    "Arguments must be positive integers.");

            double             value;
            std::istringstream iss(*arg);
            iss >> value;
            if (value > std::numeric_limits<int>::max())
                throw std::invalid_argument("Argument outside integer range: "
                                            + std::string(*arg));
        }
    }
}

template <typename T>
void addIntegersToContainer(T& container, const char** argv)
{
    for (const char** arg = argv; *arg != NULL; ++arg)
        container.push_back(std::atoi(*arg));
}

void checkDuplicates(const std::vector<int>& vec)
{
    std::vector<int> copy(vec);
    std::sort(copy.begin(), copy.end());
    for (std::vector<int>::const_iterator a = copy.begin(),
                                          b = copy.begin() + 1;
         b != copy.end(); ++a, ++b)
    {
        if (*a == *b)
            throw std::invalid_argument("Arguments contain duplicates.");
    }
}

bool isSorted(const std::vector<int>& arg_vec)
{
    std::vector<int> copy(arg_vec);
    std::sort(copy.begin(), copy.end());
    for (std::vector<int>::const_iterator a = arg_vec.begin(), b = copy.begin();
         a != arg_vec.end(); ++a, ++b)
    {
        if (*a != *b)
            return false;
    }
    return true;
}

int main(int argc, const char* argv[])
{
    if (argc == 1)
        return 0;
    const char** nums = argv + 1;
    try
    {
        checkPositiveInt(nums);
    }
    catch (const std::exception& e)
    {
        printErrMsg(e.what());
        return 1;
    }
    if (argc == 2)
        return 0;

    std::vector<int> arg_vec;
    addIntegersToContainer(arg_vec, nums);
    try
    {
        checkDuplicates(arg_vec);
    }
    catch (const std::exception& e)
    {
        printErrMsg(e.what());
        return 1;
    }
    if (isSorted(arg_vec))
    {
        std::cout << "Numbers are already sorted.\n";
        return 0;
    }

    std::list<int> arg_lst;
    addIntegersToContainer(arg_lst, nums);

    std::cout << "Before: " << arg_vec << "\n";

    PmergeMe     pm;
    std::clock_t start;
    std::clock_t end;

    start = std::clock();
    pm.sort(arg_vec, false);
    end = std::clock();
    double vec_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;
    std::cout << "Sorted: " << arg_vec << "\n";

    start = std::clock();
    pm.sort(arg_lst, false);
    end = std::clock();
    double list_time = static_cast<double>(end - start) / CLOCKS_PER_SEC;

    std::cout << "Sorting vector: " << vec_time << "s\n";
    std::cout << "Sorting list: " << list_time << "s\n";
}
