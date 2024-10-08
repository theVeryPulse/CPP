#include "RPN.hpp"
#include <iostream>
#include <stdexcept>
#include <sstream>
#include <cstdlib>

struct Operation
{
    char symbol;
    int (*perform)(int, int);
};

const std::string RPN::valid_symbols_ = "+-*/";

RPN::RPN()
{
}

RPN::~RPN()
{
}

RPN::RPN(const RPN& other) : tokens_(other.tokens_)
{
}

RPN& RPN::operator=(const RPN& other)
{
    if (this != &other)
        tokens_ = other.tokens_;
    return *this;
}

// =============================================================================
//  Internal Helper Functions
// =============================================================================

static std::deque<std::string> split(const std::string& s, char delimiter)
{
    size_t                  start = s.find_first_not_of(delimiter);
    size_t                  end;
    std::deque<std::string> splitted;

    while ((end = s.find(delimiter, start)) != std::string::npos)
    {
        // std::cout << "Found -> " << s.substr(start, end - start) << "\n";
        splitted.push_back(s.substr(start, end - start));
        start = s.find_first_of(delimiter, start);
        start = s.find_first_not_of(delimiter, start);
    }
    if (s[start] != '\0')
        splitted.push_back(s.substr(start));
    return splitted;
}

// clang-format off
static int add(int a, int b)      { return a + b; }
static int minus(int a, int b)    { return a - b; }
static int divide(int a, int b)   { return a / b; }
static int multiply(int a, int b) { return a * b; }
// clang-format on

static int performOperation(const std::string& str, int value1, int value2)
{
    static const Operation table[] = {
        {'+', &add}, {'-', &minus}, {'*', &multiply}, {'/', &divide}};
    for (const Operation* operation = table; operation < table + 4; ++operation)
    {
        if (str[0] == operation->symbol && str.length() == 1)
        {
            std::cout << value1 << " " << str[0] << " " << value2 << "\n";
            return operation->perform(value1, value2);
        }
    }
    throw std::invalid_argument("Invalid operator: " + str);
    return 0;
}

template <typename T>
static std::ostream& operator<<(std::ostream& os, std::deque<T> split)
{
    os << "{";
    for (typename std::deque<T>::const_iterator entry = split.begin();
         entry != split.end(); ++entry)
    {
        if (entry != split.begin())
            os << ", ";
        os << *entry;
    }
    os << "}";
    return os;
}

static bool numberOK(const std::string& str)
{
    std::stringstream ss(str);
    int               result;
    return (ss >> result >> std::ws).eof();
}

// =============================================================================
// Public Method
// =============================================================================

void RPN::calculate(const std::string& input)
{
    std::deque<int> values;
    tokens_ = split(input, ' ');

    while (!tokens_.empty())
    {
        std::cout << "To process: " << tokens_ << "\n";
        std::cout << "Stack: " << values << "\n";

        const std::string& token = tokens_.front();
        if (token.length() == 1
            && valid_symbols_.find(token[0]) != std::string::npos)
        // take two values from stack and perform operations
        {
            if (values.size() < 2)
                throw std::runtime_error("Not enough values in stack.");
            int value_a = values.front();
            values.pop_front();
            int value_b = values.front();
            values.pop_front();
            int result = performOperation(token, value_a, value_b);
            values.push_front(result);
        }
        else if (numberOK(*tokens_.begin()))
        // save the integer value into stack
        {
            std::stringstream ss(*tokens_.begin());
            int               value;
            ss >> value;
            values.push_back(value);
        }
        else
            throw std::runtime_error("Invalid token: " + token);
        tokens_.pop_front();
    }
    std::cout << " => " << *values.begin() << "\n";
}
