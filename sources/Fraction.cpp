#include "Fraction.hpp"
#include <algorithm>
#include <cmath>
using namespace ariel;
using namespace std;
#define MAX_NUM 1000000

Fraction::Fraction(){
    this->mechane = 1;
    this->mone = 1;
}

Fraction::Fraction(int numerator, int denominator) : mone(numerator), mechane(denominator){
    if(denominator == 0){
        throw invalid_argument("Fraction can't be divided by zero");
    }
}

Fraction::Fraction(float num){
     // Convert the float to a fraction
    int val = num*1000;
    int gcd = __gcd(val, 1000);
    this->mone = val/gcd;
    this->mechane = 1000/gcd;
}

// binary operators
Fraction Fraction::operator+ (const Fraction& other) const{
    int new_mone = (mone * other.mechane) + (other.mone * mechane);
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane); 
    return Fraction(new_mone/gcd, new_mechane/gcd);
}

Fraction Fraction::operator- (const Fraction& other) const{
    int new_mone = (mone * other.mechane) - (other.mone * mechane);
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane); 
    return Fraction(new_mone/gcd, new_mechane/gcd);
}

Fraction Fraction::operator* (const Fraction& other) const{
    int new_mone = mone * other.mone;
    int new_mechane = mechane * other.mechane;
    int gcd = __gcd(new_mone, new_mechane); 
    return Fraction(new_mone/gcd, new_mechane/gcd);
}

Fraction Fraction::operator/ (const Fraction& other) const{
    int new_mone = mone * other.mechane;
    int new_mechane = mechane * other.mone;
    int gcd = __gcd(new_mone, new_mechane); 
    return Fraction(new_mone/gcd, new_mechane/gcd);
}

// comparison operators
bool Fraction::operator> (const Fraction& other) const{
    return ((mone * other.mechane) > (other.mone * mechane));
}

bool Fraction::operator< (const Fraction& other) const{
    return ((mone * other.mechane) < (other.mone * mechane));
}

bool Fraction::operator>= (const Fraction& other) const{
    return ((mone * other.mechane) >= (other.mone * mechane));
}

bool Fraction::operator<= (const Fraction& other) const{
    return ((mone * other.mechane) <= (other.mone * mechane));
}

// increment and decrement operators
Fraction& Fraction::operator++(){
    mone = mone + mechane;
    return *this;
}

const Fraction Fraction::operator++(int dummy_flag_for_postfix_increment){
    Fraction temp(*this);
    mone = mone + mechane;
    return temp;
}

Fraction& Fraction::operator--(){
    mone = mone - mechane;
    return *this;
}

const Fraction Fraction::operator--(int dummy_flag_for_postfix_decrement){
    Fraction temp(*this);
    mone = mone - mechane;
    return temp;
}

// friend global comparison operators
bool ariel::operator> (float f1, const Fraction& f2){
    float curr_value = FractionToFloat(f2);
    return f1 > curr_value;
}

bool ariel::operator< (float f1, const Fraction& f2){
    float curr_value = FractionToFloat(f2);
    return f1 < curr_value;
}

bool ariel::operator>= (float f1, const Fraction& f2){
    float curr_value = FractionToFloat(f2);
    return f1 >= curr_value;
}

bool ariel::operator<= (float f1, const Fraction& f2){
    float curr_value = FractionToFloat(f2);
    return f1 <= curr_value;
}

bool ariel::operator> (const Fraction& f2, float f1){
    float curr_value = FractionToFloat(f2);
    return curr_value > f1;
}

bool ariel::operator< (const Fraction& f2, float f1){
    float curr_value = FractionToFloat(f2);
    return curr_value < f1;
}

bool ariel::operator>= (const Fraction& f2, float f1){
    float curr_value = FractionToFloat(f2);
    return curr_value >= f1;
}

bool ariel::operator<= (const Fraction& f2, float f1){
    float curr_value = FractionToFloat(f2);
    return curr_value <= f1;
}

// friend global binary operators
bool ariel::operator== (const Fraction& f1, const Fraction& f2){
    int f1_gcd = __gcd(f1.getDenominator(), f1.getNumerator());
    int f2_gcd = __gcd(f2.getDenominator(), f2.getNumerator());
    int reduced_mone_f1 = f1.getNumerator()/f1_gcd;
    int reduced_mechane_f1 = f1.getDenominator()/f1_gcd;
    int reduced_mone_f2 = f2.getNumerator()/f2_gcd;
    int reduced_mechane_f2 = f2.getDenominator()/f2_gcd;
    return (reduced_mone_f1 == reduced_mone_f2 && reduced_mechane_f1 == reduced_mechane_f2);
}

Fraction ariel::operator+ (float f1, const Fraction& f2){
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 + f2);
    return result;
}

Fraction ariel::operator- (float f1, const Fraction& f2){
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 - f2);
    return result;
}

Fraction ariel::operator* (float f1,const Fraction& f2){
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 * f2);
    return result;
}

Fraction ariel::operator/ (float f1, const Fraction& f2){
    Fraction Frac_f1(f1);
    Fraction result(Frac_f1 / f2);
    return result;
}

Fraction ariel::operator+ (const Fraction& f2, float f1){
    Fraction Frac_f1(f1);
    Fraction result(f2 + Frac_f1);
    return result;
}

Fraction ariel::operator- (const Fraction& f2, float f1){
    Fraction Frac_f1(f1);
    Fraction result(f2 - Frac_f1);
    return result;
}

Fraction ariel::operator* (const Fraction& f2, float f1){
    Fraction Frac_f1(f1);
    Fraction result(f2 * Frac_f1);
    return result;
}

Fraction ariel::operator/ (const Fraction& f2, float f1){
    Fraction Frac_f1(f1);
    Fraction result(f2 / Frac_f1);
    return result;
}

// friend global IO operators
std::ostream& ariel::operator<< (std::ostream& output, const Fraction& f){
    // Output the fraction to the output stream in the format "numerator/denominator"
    output << f.getNumerator() << "/" << f.getDenominator();
    return output;
}

std::istream& ariel::operator>> (std::istream& input, Fraction& f){
    // Read the fraction from the input stream in the format "numerator/denominator"
    int numerator = 0;
    int denominator = 1;
    char slash = '/';

    input >> numerator;
    if (input.fail()) {
        // Input was not a number
        throw invalid_argument("The numerator you prvoide is not valid");
    }

    input >> slash;
    if (input.fail()) {
        // Input was not in the format "numerator/denominator"
        throw invalid_argument("The slash between the fraction is not valid");
    }

    input >> denominator;
    if (input.fail()) {
        // Input was not a number
        throw invalid_argument("The denominator you prvoide is not valid");
    }

    f.setNumerator(numerator);
    f.setDenominator(denominator);
    return input;
}

int Fraction::getNumerator() const{
    return this->mone;
}

int Fraction::getDenominator() const{
    return this->mechane;
}

void Fraction::setNumerator(int numerator){
    this->mone = numerator;
}

void Fraction::setDenominator(int denominator){
    this->mechane = denominator;
}

float ariel::FractionToFloat(const Fraction& a){
    float numerator_a = (float)a.getNumerator();
    float denominator_a = (float)a.getDenominator();
    float fraction_float = numerator_a/denominator_a;
    return round(fraction_float*1000)/1000;
}