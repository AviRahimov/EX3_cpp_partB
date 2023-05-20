#include "Fraction.hpp"
#include <algorithm>
#include <cmath>
#include <limits>
using namespace ariel;
using namespace std;

int MAX_INT = numeric_limits<int>::max();
int MIN_INT = numeric_limits<int>::min();

Fraction::Fraction()
{
    this->mechane = 1;
    this->mone = 1;
}

Fraction::Fraction(int numerator, int denominator)
{
    if (denominator == 0)
    {
        throw invalid_argument("Fraction can't be divided by zero");
    }
    int gcd = abs(__gcd(numerator, denominator));
    if ((numerator < 0 && denominator < 0) || (numerator > 0 && denominator < 0))
    {
        this->mone = -numerator / gcd;
        this->mechane = -denominator / gcd;
    }
    else
    {
        this->mone = numerator / gcd;
        this->mechane = denominator / gcd;
    }
}

Fraction::Fraction(float num)
{
    // Convert the float to a fraction
    int val = num * 1000;
    int gcd = __gcd(val, 1000);
    this->mone = val / gcd;
    this->mechane = 1000 / gcd;
}

// Binary operators

/**
 * @brief Addition operator for fractions.
 * @param other The fraction to add.
 * @return The sum of the fractions.
 */
Fraction Fraction::operator+(const Fraction &other) const
{
    int new_mone = (mone * other.mechane) + (other.mone * mechane);
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane);
    check_overflow('+', mone * other.getDenominator(), other.getNumerator() * mechane, new_mone);
    return Fraction(new_mone / gcd, new_mechane / gcd);
}

/**
 * @brief Subtraction operator for fractions.
 * @param other The fraction to subtract.
 * @return The difference between the fractions.
 */
Fraction Fraction::operator-(const Fraction &other) const
{
    int new_mone = (mone * other.mechane) - (other.mone * mechane);
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane);
    check_overflow('-', mone * other.mechane, other.mone * mechane, new_mone);
    return Fraction(new_mone / gcd, new_mechane / gcd);
    // return *this + (other * -1);
}

/**
 * @brief Multiplication operator for fractions.
 * @param other The fraction to multiply by.
 * @return The product of the fractions.
 */
Fraction Fraction::operator*(const Fraction &other) const
{
    int new_mone = mone * other.mone;
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane);

    Fraction res(new_mone / gcd, new_mechane / gcd);
    check_overflow('*', mone, other.getNumerator(), new_mone);
    check_overflow('*', mechane, other.getDenominator(), new_mechane);
    return res;
}

/**
 * @brief Division operator for fractions.
 * @param other The fraction to divide by.
 * @return The quotient of the fractions.
 */
Fraction Fraction::operator/(const Fraction &other) const
{
    if (other.getNumerator() == 0)
    {
        throw runtime_error("Fraction can't be divided by zero");
    }
    Fraction inverse(other.getDenominator(), other.getNumerator());
    return *this * inverse;
}

// Comparison operators

/**
 * @brief Greater than operator for fractions.
 * @param other The fraction to compare against.
 * @return True if this fraction is greater than the other fraction, false otherwise.
 */
bool Fraction::operator>(const Fraction &other) const
{
    return other < *this;
}

/**
 * @brief Less than operator for fractions.
 * @param other The fraction to compare against.
 * @return True if this fraction is less than the other fraction, false otherwise.
 */
bool Fraction::operator<(const Fraction &other) const
{
    int to_divide = abs(this->getDenominator() * other.getDenominator());
    int first_frac = (to_divide * this->getNumerator()) / this->getDenominator();
    int second_frac = (to_divide * other.getNumerator()) / other.getDenominator();
    return first_frac < second_frac;
}

/**
 * @brief Greater than or equal to operator for fractions.
 * @param other The fraction to compare against.
 * @return True if this fraction is greater than or equal to the other fraction, false otherwise.
 */
bool Fraction::operator>=(const Fraction &other) const
{
    return ((mone * other.mechane) >= (other.mone * mechane));
}

/**
 * @brief Less than or equal to operator for fractions.
 * @param other The fraction to compare against.
 * @return True if this fraction is less than or equal to the other fraction, false otherwise.
 */
bool Fraction::operator<=(const Fraction &other) const
{
    return other >= *this;
}

// Increment and decrement operators

/**
 * @brief Prefix increment operator.
 * @return The incremented fraction.
 */
Fraction &Fraction::operator++()
{
    mone = mone + mechane;
    return *this;
}

/**
 * @brief Postfix increment operator.
 * @param dummy_flag_for_postfix_increment Dummy parameter to differentiate from prefix increment.
 * @return The original fraction before increment.
 */
const Fraction Fraction::operator++(int dummy_flag_for_postfix_increment)
{
    Fraction temp(*this);
    mone = mone + mechane;
    return temp;
}

/**
 * @brief Prefix decrement operator.
 * @return The decremented fraction.
 */
Fraction &Fraction::operator--()
{
    mone = mone - mechane;
    return *this;
}

/**
 * @brief Postfix decrement operator.
 * @param dummy_flag_for_postfix_decrement Dummy parameter to differentiate from prefix decrement.
 * @return The original fraction before decrement.
 */
const Fraction Fraction::operator--(int dummy_flag_for_postfix_decrement)
{
    Fraction temp(*this);
    mone = mone - mechane;
    return temp;
}

// Friend global comparison operators

/**
 * @brief Greater than operator for float and fraction.
 * @param f1 The float to compare against.
 * @param f2 The fraction to compare.
 * @return True if the float is greater than the fraction, false otherwise.
 */
bool ariel::operator>(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 > curr_value;
}

/**
 * @brief Less than operator for float and fraction.
 * @param f1 The float to compare against.
 * @param f2 The fraction to compare.
 * @return True if the float is less than the fraction, false otherwise.
 */
bool ariel::operator<(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 < curr_value;
}

/**
 * @brief Greater than or equal to operator for float and fraction.
 * @param f1 The float to compare against.
 * @param f2 The fraction to compare.
 * @return True if the float is greater than or equal to the fraction, false otherwise.
 */
bool ariel::operator>=(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 >= curr_value;
}

/**
 * @brief Less than or equal to operator for float and fraction.
 * @param f1 The float to compare against.
 * @param f2 The fraction to compare.
 * @return True if the float is less than or equal to the fraction, false otherwise.
 */
bool ariel::operator<=(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 <= curr_value;
}

/**
 * @brief Greater than operator for fraction and float.
 * @param f2 The fraction to compare.
 * @param f1 The float to compare against.
 * @return True if the fraction is greater than the float, false otherwise.
 */
bool ariel::operator>(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value > f1;
}

/**
 * @brief Less than operator for fraction and float.
 * @param f2 The fraction to compare.
 * @param f1 The float to compare against.
 * @return True if the fraction is less than the float, false otherwise.
 */
bool ariel::operator<(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value < f1;
}

/**
 * @brief Greater than or equal to operator for fraction and float.
 * @param f2 The fraction to compare.
 * @param f1 The float to compare against.
 * @return True if the fraction is greater than or equal to the float, false otherwise.
 */
bool ariel::operator>=(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value >= f1;
}

/**
 * @brief Less than or equal to operator for fraction and float.
 * @param f2 The fraction to compare.
 * @param f1 The float to compare against.
 * @return True if the fraction is less than or equal to the float, false otherwise.
 */
bool ariel::operator<=(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value <= f1;
}

// Friend global binary operators

/**
 * @brief Equal to operator for two fractions.
 * @param f1 The first fraction to compare.
 * @param f2 The second fraction to compare.
 * @return True if the fractions are equal, false otherwise.
 */
bool ariel::operator==(const Fraction &f1, const Fraction &f2)
{
    float first_frac = FractionToFloat(f1);
    float second_frac = FractionToFloat(f2);
    return first_frac == second_frac;
}

/**
 * @brief Addition operator for float and fraction.
 * @param f1 The float to add.
 * @param f2 The fraction to add.
 * @return The result of the addition as a fraction.
 */
Fraction ariel::operator+(float f1, const Fraction &f2)
{
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 + f2);
    return result;
}

/**
 * @brief Subtraction operator for float and fraction.
 * @param f1 The float to subtract.
 * @param f2 The fraction to subtract.
 * @return The result of the subtraction as a fraction.
 */
Fraction ariel::operator-(float f1, const Fraction &f2)
{
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 - f2);
    return result;
}

/**
 * @brief Multiplication operator for float and fraction.
 * @param f1 The float to multiply.
 * @param f2 The fraction to multiply.
 * @return The result of the multiplication as a fraction.
 */
Fraction ariel::operator*(float f1, const Fraction &f2)
{
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 * f2);
    return result;
}

/**
 * @brief Division operator for float and fraction.
 * @param f1 The float to divide.
 * @param f2 The fraction to divide.
 * @return The result of the division as a fraction.
 */
/**
 * @brief Divide a floating-point value by a fraction.
 * @param f1 The floating-point value to divide.
 * @param f2 The fraction to divide by.
 * @return The result of the division as a fraction.
 * @throws runtime_error if the denominator of the fraction is zero.
 */
Fraction ariel::operator/(float f1, const Fraction &f2)
{
    if (f2.getNumerator() == 0)
    {
        throw runtime_error("Fraction can't be divided by zero");
    }
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 / f2);
    return result;
}

/**
 * @brief Add a floating-point value to a fraction.
 * @param f2 The fraction to add.
 * @param f1 The floating-point value to add.
 * @return The result of the addition as a fraction.
 */
Fraction ariel::operator+(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 + Frac_f1);
    return result;
}

/**
 * @brief Subtract a floating-point value from a fraction.
 * @param f2 The fraction to subtract from.
 * @param f1 The floating-point value to subtract.
 * @return The result of the subtraction as a fraction.
 */
Fraction ariel::operator-(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 - Frac_f1);
    return result;
}

/**
 * @brief Multiply a fraction by a floating-point value.
 * @param f2 The fraction to multiply.
 * @param f1 The floating-point value to multiply.
 * @return The result of the multiplication as a fraction.
 */
Fraction ariel::operator*(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 * Frac_f1);
    return result;
}

/**
 * @brief Divide a fraction by a floating-point value.
 * @param f2 The fraction to divide.
 * @param f1 The floating-point value to divide by.
 * @return The result of the division as a fraction.
 */
Fraction ariel::operator/(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 / Frac_f1);
    return result;
}

/**
 * @brief Overload the output stream operator to output a fraction.
 * @param output The output stream.
 * @param f The fraction to output.
 * @return The output stream after the fraction has been written to it.
 */
ostream &ariel::operator<<(ostream &output, const Fraction &f)
{
    // Output the fraction to the output stream in the format "numerator/denominator"
    output << f.getNumerator() << "/" << f.getDenominator();
    return output;
}

/**
 * @brief Overload the input stream operator to read a fraction.
 * @param input The input stream.
 * @param f The fraction to read.
 * @return The input stream after the fraction has been read from it.
 * @throws runtime_error if the input is not valid.
 */
istream &ariel::operator>>(istream &input, Fraction &f)
{
    // Read the fraction from the input stream in the format "numerator/denominator"
    int numerator = 0;
    int denominator = 1;
    int slash = '/';

    input >> numerator;
    if (input.fail())
    {
        // Input was not a number
        throw runtime_error("The numerator you provide is not valid");
    }

    input >> slash;
    if (input.fail())
    {
        // Input was not in the format "numerator/denominator"
        throw runtime_error("the slash you provide is not valid");
    }

    if (slash == '/')
    {
        input >> denominator;
        if (input.fail() || denominator == 0)
        {
            // Input was not a number
            throw runtime_error("The denominator you provide is not valid");
        }
        Fraction temp(numerator, denominator);
        f.mone = temp.getNumerator();
        f.mechane = temp.getDenominator();
    }
    else
    {
        if (slash == 0)
        {
            throw runtime_error("The denominator you provide is not valid");
        }
        Fraction temp(numerator, slash);
        f.mone = temp.getNumerator();
        f.mechane = temp.getDenominator();
    }
    return input;
}

/**
 * @brief Get the numerator of the fraction.
 * @return The numerator of the fraction.
 */
int Fraction::getNumerator() const
{
    return this->mone;
}

/**
 * @brief Get the denominator of the fraction.
 * @return The denominator of the fraction.
 */
int Fraction::getDenominator() const
{
    return this->mechane;
}

/**
 * @brief Convert a fraction to a floating-point value.
 * @param a The fraction to convert.
 * @return The floating-point representation of the fraction.
 */
float ariel::FractionToFloat(const Fraction &a)
{
    float numerator_a = (float)a.getNumerator();
    float denominator_a = (float)a.getDenominator();
    float fraction_float = numerator_a / denominator_a;
    return round(fraction_float * 1000) / 1000;
}

/**
 * @brief Check for arithmetic overflow in fraction calculations.
 * @param opt The arithmetic operation ('+', '-', '*', or '/').
 * @param a The first operand.
 * @param b The second operand.
 * @param res The result of the arithmetic operation.
 * @throws overflow_error if an overflow occurs.
 */
void Fraction::check_overflow(char opt, int a, int b, int res) const
{
    if ((opt != '-' && a > 1 && b > 1 && (res <= a || res <= b)))
    {
        throw overflow_error("Overflow error");
    }
    else if (opt == '+' && (a < -1 && b < -1 && (res >= a || res >= b)))
    {
        throw overflow_error("Overflow error");
    }
    else if (opt == '-' && (a > 0 && b < 0 && (res <= max(a, b))))
    {
        throw overflow_error("Overflow error");
    }
}
