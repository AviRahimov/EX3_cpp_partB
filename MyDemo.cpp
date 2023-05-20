#include "sources/Fraction.hpp"
#include <iostream>
using namespace ariel;
using namespace std;


int main() {
    try {
        // Create two fractions
        Fraction fraction1(3, 4);
        Fraction fraction2(2, 5);

        // Perform arithmetic operations on fractions
        Fraction sum = fraction1 + fraction2;
        Fraction difference = fraction1 - fraction2;
        Fraction product = fraction1 * fraction2;
        Fraction quotient = fraction1 / fraction2;

        // Output the results
        cout << "Fraction 1: " << fraction1 << endl;
        cout << "Fraction 2: " << fraction2 << endl;
        cout << "Sum: " << sum << endl; // 3/4 + 2/5 = 23/20
        cout << "Difference: " << difference << endl; // 3/4 - 2/5 = 7/20
        cout << "Product: " << product << endl; // 3/4 * 2/5 = reduced(6/20) = 3/10
        cout << "Quotient: " << quotient << endl; // (3/4) / (2/5) = 15/8

        // Compare fractions
        bool greaterThan = fraction1 > fraction2;
        bool lessThan = fraction1 < fraction2;
        bool greaterThanOrEqual = fraction1 >= fraction2;
        bool lessThanOrEqual = fraction1 <= fraction2;
        bool equalTo = fraction1 == fraction2;

        // Output the comparison results
        cout << "Fraction 1 > Fraction 2: " << (greaterThan ? "true" : "false") << endl; // 3/4 > 2/5
        cout << "Fraction 1 < Fraction 2: " << (lessThan ? "true" : "false") << endl; // 3/4 not less than 2/5
        cout << "Fraction 1 >= Fraction 2: " << (greaterThanOrEqual ? "true" : "false") << endl; //  3/4 >= 2/5
        cout << "Fraction 1 <= Fraction 2: " << (lessThanOrEqual ? "true" : "false") << endl; // 3/4 not less than or equal to 2/5
        cout << "Fraction 1 == Fraction 2: " << (equalTo ? "true" : "false") << endl; // 3/4 not equal to 2/5

        // Increment and decrement fractions
        Fraction fraction3(1, 3);
        cout << "Original Fraction: " << fraction3 << endl; // 1/3
        cout << "Prefix Increment: " << ++fraction3 << endl; // 4/3
        cout << "Postfix Increment: " << fraction3++ << endl; // 7/3 but printing 4/3 because that's how postfix works
        cout << "After Postfix Increment: " << fraction3 << endl; // 7/3
        cout << "Prefix Decrement: " << --fraction3 << endl; // 4/3
        cout << "Postfix Decrement: " << fraction3-- << endl; // 1/3 but printing 4/3 because that's how postfix works
        cout << "After Postfix Decrement: " << fraction3 << endl; // 1/3

    } catch (const exception& ex) {
        cout << "Exception: " << ex.what() << endl;
    }

    return 0;
}
