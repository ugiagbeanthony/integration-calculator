#include "Term.h"
#include <cmath>
// #include <iostream>
// ill need a function to put my fraction coeff in lowest terms
// ill need a function to add my fraction coeff of same exp

/*Term::Term() { //when there isnt an exponent
    this->numerator = 1;
    this->denominator = 1;
    this->expon = 1;
}*/

Term::Term()
{
    this->numerator = 0;
    // default term starts as 0 so it prints nothing unless needed

    this->denominator = 1;
    // keep denominator valid so no divide by zero

    this->expon = 0;
    // default exponent for constant term
}

Term::Term(int numerator, int denominator, int expon)
{
    this->numerator = numerator;
    // store numerator directly

    this->denominator = denominator;
    // store denominator directly

    this->expon = expon;
    // store exponent directly
}

void Term::setNumerator(int numerator)
{
    this->numerator = numerator;
    // update numerator only
}

void Term::setDenominator(int denominator)
{
    this->denominator = denominator;
    // update denominator only
}

void Term::setExpon(int expon)
{
    this->expon = expon;
    // update exponent only
}

int Term::getNumerator() const
{ // get the numerator
    return numerator;
}

int Term::getDenominator() const
{ // get my denominator
    return denominator;
}

int Term::getExpon() const
{ // get my exponent
    return expon;
}

int Term::gcd(int a, int b)
{ // get the greatest common divisor
    // standard euclid algorithm
    // keeps reducing until remainder is zero
    while (b)
    {
        int remains = a % b;
        a = b;
        b = remains;
    }
    return a;
}

void Term::simplify()
{ // get the simplest term
    if (numerator == 0)
    { // ifnum is empy early return
        this->denominator = 1;
        // zero fraction always becomes 0/1
        return;
    }
    else
    {
        int common = gcd(std::abs(numerator), std::abs(denominator));
        // get gcd of absolute values

        this->numerator = (this->numerator / common);
        // divide numerator by gcd

        this->denominator = (this->denominator / common);
        // divide denominator by gcd

        if (denominator < 0)
        {
            // keep denominator positive always
            this->denominator *= -1;
            this->numerator *= -1;
        }
    }
}

Term &Term::operator+=(const Term &other)
{ // for when i need to add fractions that have same exponent
    // cross multiply to add fractions
    int newNum;
    int newdenum;

    newNum = (this->numerator * other.denominator) + (this->denominator * other.numerator);
    newdenum = this->denominator * other.denominator;

    this->numerator = newNum;
    this->denominator = newdenum;

    simplify();
    // reduce result to simplest form

    return *this;
}

bool Term::operator<(const Term &other) const
{
    return this->expon < other.expon;
    // compare by exponent only since exponent is the key
}

bool Term::operator>(const Term &other) const
{
    return this->expon > other.expon;
    // same logic but reversed
}

bool Term::operator==(const Term &other) const
{
    return this->expon == other.expon;
    // equal if exponents match
}

std::ostream &operator<<(std::ostream &os, const Term &other)
{
    /*if(other.numerator == 0) {
        return os;
    }*/
    if (other.numerator == 0 && other.expon == 0)
    {
        return os;
        // print nothing for 0 constant unless caller handles it
    }

    if (other.numerator == 0 && other.expon != 0)
    {
        return os;
        // skip zero coefficient non constant terms
    }

    else if (other.expon == 0)
    { // if coeff is not 1 and
        if (other.denominator == 1)
        {
            return os << other.numerator;
            // plain integer constant
        }
        else
        {
            return os << "(" << other.numerator << "/" << other.denominator << ")";
            // fractional constant
        }
    }

    else if (other.numerator == 1 && other.denominator == 1 && other.expon == 1)
    {
        return os << "x";
        // simple x
    }

    else if (other.numerator == -1 && other.denominator == 1 && other.expon == 1)
    {
        return os << "-x";
        // simple -x
    }

    else
    {
        if (other.numerator == 1 && other.denominator == 1 && other.expon != 1)
        {
            return os << "x^" << other.expon;
            // 1x^n prints as x^n
        }
        else if (other.numerator == -1 && other.denominator == 1 && other.expon != 1)
        {
            return os << "-x^" << other.expon;
            // -1x^n prints as -x^n
        }
        else if ((other.numerator != 1 || other.denominator != 1) && other.expon == 1)
        {
            if (other.denominator == 1)
            {
                return os << other.numerator << "x";
                // ax when exponent is 1
            }
            else
            {
                return os << "(" << other.numerator << "/" << other.denominator << ")x";
                // fractional coeff with x
            }
        }
        else
        {
            if (other.denominator == 1)
            {
                return os << other.numerator << "x^" << other.expon;
                // ax^n
            }
            else
            {
                return os << "(" << other.numerator << "/" << other.denominator << ")x^" << other.expon;
                // fractional coeff with exponent
            }
        }
    }
}

void Term::integrateself()
{
    // increase exponent by 1
    int newExp = expon + 1;

    // multiply denominator by new exponent for integration rule
    denominator *= newExp;

    // update exponent
    expon = newExp;

    simplify();
    // reduce fraction after integration
}

double Term::evaluateAt(int x) const
{
    // convert fraction to double
    double coeff = (double)numerator / denominator;

    // compute coeff * x^exponent
    return coeff * pow(x, expon);
}
