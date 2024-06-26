/// \ref http://www.sunshine2k.de/articles/coding/fp/sunfp.html

#include "Fixed.hpp"
#include <cmath>
#include <iostream>
#include <stdint.h>
#include <string>

/*
================================================================================
==================== Constructors, Assignments, Destructor =====================
================================================================================
*/

Fixed::Fixed() : value_(0)
{
    // std::cout << "Fixed: standard constructor.\n";
}

Fixed::Fixed(const Fixed& other) : value_(other.value_)
{
    // std::cout << "Fixed: copy constructor.\n";
}

/// @brief
/// @param value
Fixed::Fixed(const int value) : value_(value << fractional_bits_)
{
    // std::cout << "Fixed: int constructor: " << value << ".\n";
}

Fixed::Fixed(const float value)
{
    // std::cout << "Fixed: float constructor: " << value << "\n";

    int   integer_part    = (int)value;
    float fractional_part = value - integer_part;

    value_ = integer_part << Fixed::fractional_bits_;
    value_ += (int)(fractional_part * Fixed::fixed_unit_one_
                    + (value >= 0 ? 0.5F : -0.5F));
    // adding the 0.5 at the end helps to reduce the error
}

/// @brief (a).operator= (b)
/// @param other The Fixed object to copy from.
/// @return This object after copy.
Fixed& Fixed::operator=(const Fixed& other)
{
    // std::cout << "Fixed: copy assignment operator.\n";
    this->value_ = other.value_;
    return *this;
}

Fixed::~Fixed()
{
    // std::cout << "Fixed: destructor.\n";
}

int Fixed::getRawBits() const
{
    // std::cout << "Fixed: getRawBits\n";
    return value_;
}

void Fixed::setRawBits(const int raw)
{
    // std::cout << "Fixed: setRawBits\n";
    value_ = raw;
}

float Fixed::toFloat() const
{
    return float(value_) / float(Fixed::fixed_unit_one_);
}

/// @brief        0xWWWWWWFF: Whole and fraction
///        Index    3 2 1 0
///               0x00WWWWWW
///        Index    3 2 1 0
/// @return
int Fixed::toInt() const
{
    return value_ >> Fixed::fractional_bits_;
}

void Fixed::printValue(std::ostream& stream) const
{
    int integer_part = toInt();
    stream << integer_part;
    int fractional_part =
        std::abs(value_ - (integer_part * Fixed::fixed_unit_one_));
    if (!fractional_part)
        return;
    stream << '.';
    if (((int64_t)fractional_part * (int64_t)390625) <= (int64_t)390625)
        stream << "00";
    else if (((int64_t)fractional_part * (int64_t)390625) <= (int64_t)3906250)
        stream << "0";
    stream << (int64_t)fractional_part * (int64_t)390625;
    // smallest unit of 8 bits fraction is 2^(-8) = 0.00390625
    // 390625 is hence chosen as the base for calculating the fractional
    // representation
}

/*
================================================================================
============================== Operator Overload ===============================
================================================================================
*/

/// @brief Overload stream `<<` for Fixed class: prints value
/// @param stream
/// @param fixed
/// @return
/// @note https://en.cppreference.com/w/cpp/language/operators
std::ostream& operator<<(std::ostream& stream, const Fixed& fixed)
{
    fixed.printValue(stream);
    return stream;
}

