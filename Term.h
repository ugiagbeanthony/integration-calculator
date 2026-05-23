// dal153159
// Osagbewonrue Ugiagbe
#ifndef TERM_H
#define TERM_H

#include <iostream>

class Term
{
    int numerator;
    int denominator;
    int expon;

public:
    Term();
    Term(int numerator, int denominator, int expon);
    void setNumerator(int numerator);
    void setDenominator(int denominator);
    void setExpon(int expon);
    int getNumerator() const;
    int getDenominator() const;
    int getExpon() const;
    void simplify();
    int gcd(int a, int b);
    void integrateself();
    double evaluateAt(int x) const;
    Term &operator+=(const Term &other);
    bool operator<(const Term &other) const;
    bool operator>(const Term &other) const;
    bool operator==(const Term &other) const;
    friend std::ostream &operator<<(std::ostream &os, const Term &other);
};
#endif