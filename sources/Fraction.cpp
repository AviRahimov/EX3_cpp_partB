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

// binary operators
Fraction Fraction::operator+(const Fraction &other) const
{
    int new_mone = (mone * other.mechane) + (other.mone * mechane);
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane);
    check_overflow('+', mone * other.getDenominator(), other.getNumerator() * mechane, new_mone);
    return Fraction(new_mone / gcd, new_mechane / gcd);
}

Fraction Fraction::operator-(const Fraction &other) const
{
    int new_mone = (mone * other.mechane) - (other.mone * mechane);
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane);
    check_overflow('-', mone * other.mechane, other.mone * mechane, new_mone);
    return Fraction(new_mone / gcd, new_mechane / gcd);
    // return *this + (other * -1);
}

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

Fraction Fraction::operator/(const Fraction &other) const
{
    if (other.getNumerator() == 0)
    {
        throw runtime_error("Fraction can't be divided by zero");
    }
    Fraction inverse(other.getDenominator(), other.getNumerator());
    return *this * inverse;
}

// comparison operators
bool Fraction::operator>(const Fraction &other) const
{
    return other < *this;
}

bool Fraction::operator<(const Fraction &other) const
{
    int to_divide = abs(this->getDenominator() * other.getDenominator());
    int first_frac = (to_divide * this->getNumerator()) / this->getDenominator();
    int second_frac = (to_divide * other.getNumerator()) / other.getDenominator();
    return first_frac < second_frac;
}

bool Fraction::operator>=(const Fraction &other) const
{
    return ((mone * other.mechane) >= (other.mone * mechane));
}

bool Fraction::operator<=(const Fraction &other) const
{
    return other >= *this;
}

// increment and decrement operators
Fraction &Fraction::operator++()
{
    mone = mone + mechane;
    return *this;
}

const Fraction Fraction::operator++(int dummy_flag_for_postfix_increment)
{
    Fraction temp(*this);
    mone = mone + mechane;
    return temp;
}

Fraction &Fraction::operator--()
{
    mone = mone - mechane;
    return *this;
}

const Fraction Fraction::operator--(int dummy_flag_for_postfix_decrement)
{
    Fraction temp(*this);
    mone = mone - mechane;
    return temp;
}

// friend global comparison operators
bool ariel::operator>(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 > curr_value;
}

bool ariel::operator<(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 < curr_value;
}

bool ariel::operator>=(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 >= curr_value;
}

bool ariel::operator<=(float f1, const Fraction &f2)
{
    float curr_value = FractionToFloat(f2);
    return f1 <= curr_value;
}

bool ariel::operator>(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value > f1;
}

bool ariel::operator<(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value < f1;
}

bool ariel::operator>=(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value >= f1;
}

bool ariel::operator<=(const Fraction &f2, float f1)
{
    float curr_value = FractionToFloat(f2);
    return curr_value <= f1;
}

// friend global binary operators
bool ariel::operator==(const Fraction &f1, const Fraction &f2)
{
    float first_frac = FractionToFloat(f1);
    float second_frac = FractionToFloat(f2);
    return first_frac == second_frac;
}

Fraction ariel::operator+(float f1, const Fraction &f2)
{
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 + f2);
    return result;
}

Fraction ariel::operator-(float f1, const Fraction &f2)
{
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 - f2);
    return result;
}

Fraction ariel::operator*(float f1, const Fraction &f2)
{
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 * f2);
    return result;
}

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

Fraction ariel::operator+(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 + Frac_f1);
    return result;
}

Fraction ariel::operator-(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 - Frac_f1);
    return result;
}

Fraction ariel::operator*(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 * Frac_f1);
    return result;
}

Fraction ariel::operator/(const Fraction &f2, float f1)
{
    Fraction Frac_f1(f1);
    Fraction result(f2 / Frac_f1);
    return result;
}

// friend global IO operators
ostream &ariel::operator<<(ostream &output, const Fraction &f)
{
    // Output the fraction to the output stream in the format "numerator/denominator"
    output << f.getNumerator() << "/" << f.getDenominator();
    return output;
}

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

int Fraction::getNumerator() const
{
    return this->mone;
}

int Fraction::getDenominator() const
{
    return this->mechane;
}

float ariel::FractionToFloat(const Fraction &a)
{
    float numerator_a = (float)a.getNumerator();
    float denominator_a = (float)a.getDenominator();
    float fraction_float = numerator_a / denominator_a;
    return round(fraction_float * 1000) / 1000;
}

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