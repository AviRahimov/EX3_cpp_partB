#ifndef EX3_CPP_FRACTION_HPP
#define EX3_CPP_FRACTION_HPP

#include <iostream>

namespace ariel
{
    class Fraction
    {
    private:
        int mone, mechane;

    public:
        // default constructor
        Fraction();
        // initializer constructor
        Fraction(int numerator, int denominator);
        // Constructor for float to fraction
        Fraction(float num);
        // getters to the members
        int getNumerator() const;
        int getDenominator() const;
        // Auxiliary function
        friend float FractionToFloat(const Fraction &fraction);
        void check_overflow(char operat, int first, int second, int result) const;
        // binary operators
        Fraction operator+(const Fraction &other) const;
        Fraction operator-(const Fraction &other) const;
        Fraction operator*(const Fraction &other) const;
        Fraction operator/(const Fraction &other) const;
        bool operator>(const Fraction &other) const;
        bool operator<(const Fraction &other) const;
        bool operator>=(const Fraction &other) const;
        bool operator<=(const Fraction &other) const;
        Fraction &operator++();
        const Fraction operator++(int dummy_flag_for_postfix_increment);
        Fraction &operator--();
        const Fraction operator--(int dummy_flag_for_postfix_decrement);
        friend bool operator==(const Fraction &frac1, const Fraction &frac2);
        friend Fraction operator+(float frac1, const Fraction &frac2);
        friend Fraction operator-(float frac1, const Fraction &frac2);
        friend Fraction operator*(float frac1, const Fraction &frac2);
        friend Fraction operator/(float frac1, const Fraction &frac2);
        friend Fraction operator+(const Fraction &frac2, float frac1);
        friend Fraction operator-(const Fraction &frac2, float frac1);
        friend Fraction operator*(const Fraction &frac2, float frac1);
        friend Fraction operator/(const Fraction &frac2, float frac1);
        friend bool operator>(float frac1, const Fraction &frac2);
        friend bool operator<(float frac1, const Fraction &frac2);
        friend bool operator>=(float frac1, const Fraction &frac2);
        friend bool operator<=(float frac1, const Fraction &frac2);
        friend bool operator>(const Fraction &frac2, float frac1);
        friend bool operator<(const Fraction &frac2, float frac1);
        friend bool operator>=(const Fraction &frac2, float frac1);
        friend bool operator<=(const Fraction &frac2, float frac1);
        // friend global IO operators
        friend std::ostream &operator<<(std::ostream &output, const Fraction &frac);
        friend std::istream &operator>>(std::istream &input, Fraction &frac);
    }; // end of Fraction class
}

#endif // EX3_CPP_FRACTION_HPP