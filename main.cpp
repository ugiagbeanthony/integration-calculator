/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby,
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
#include <iostream>  //for cout
#include "BinTree.h" // to use binary tree
#include "Term.h"    // to create some term
#include <iomanip>   //required for setprecision and fixed
#include <string>    //string
#include <sstream>   //i use a string stream one time
#include <fstream>   // i use ifstream
#include <cctype>    // i use isdigit
#include <vector>    // i use a vector

using namespace std;

void printPolynomial(const vector<Term> &terms)
{
    bool first = true; // tracks if nothing has been printed yet
    for (const Term &t : terms)
    {
        std::ostringstream temp;
        temp << t; // convert term to string using operator<<

        if (temp.str().empty())
            continue; // skip zero terms

        int num = t.getNumerator(); // coefficient sign check

        if (first)
        {
            // first real term prints with no leading +/-
            cout << temp.str();
            first = false; // after printing its no longer false
        }
        else
        {
            // for all other terms, print sign manually
            if (num > 0)
            {
                cout << " + " << temp.str();
            }
            else
            {
                // print negative term as "- positive version"
                Term temp2 = t;
                temp2.setNumerator(abs(num));
                cout << " - " << temp2;
            }
        }
    }
    if (first)
    {
        // nothing printed - polynomial was zero
        cout << "0";
    }
}
void parseString(string line, Bst<Term> &tree)
{
    int i = 0;
    int n = line.length();

    while (i < n)
    {
        int start = i;

        // contine after + or -
        if (line[i] == '+' || line[i] == '-')
            i++;

        // scan until next + or - that is NOT part of exponent
        while (i < n)
        {
            if ((line[i] == '+' || line[i] == '-') && !(i > 0 && line[i - 1] == '^'))
            {
                break;
            }
            i++;
        }

        // isolate the term substring
        string termStr = line.substr(start, i - start);
        if (termStr.empty())
            continue;

        // default coefficient = 1/1, exponent = 0
        int num = 1, den = 1, expon = 0;

        size_t xPos = termStr.find('x');
        size_t slashPos = termStr.find('/');
        size_t hatPos = termStr.find('^');

        // exponent logic
        if (xPos == string::npos)
        {
            expon = 0; // constant term
        }
        else if (hatPos != string::npos)
        {
            string expStr = termStr.substr(hatPos + 1);
            expon = expStr.empty() ? 1 : stoi(expStr);
        }
        else
        {
            expon = 1; // plain "x"
        }

        // coefficient logic
        string coeffPart = (xPos == string::npos) ? termStr : termStr.substr(0, xPos);

        if (coeffPart == "" || coeffPart == "+")
        {
            num = 1;
        }
        else if (coeffPart == "-")
        {
            num = -1;
        }
        else if (slashPos != string::npos)
        {
            // fraction
            string nStr = coeffPart.substr(0, slashPos);
            string dStr = coeffPart.substr(slashPos + 1);

            num = (nStr == "" || nStr == "+") ? 1 : (nStr == "-") ? -1
                                                                  : stoi(nStr);

            den = stoi(dStr);
        }
        else
        {
            // integer coefficient
            num = stoi(coeffPart);
            den = 1;
        }

        // create term
        Term t(num, den, expon);

        // check if exponent already exists in tree
        Term *exists = tree.find(t);

        if (!exists)
        {
            tree.insert(t); // new exponent - new node
        }
        else
        {
            *exists += t; // same exponent - combine coefficients
        }
    }
}

// try to open the file
bool openFile(ifstream &fin, const string &filename)
{
    fin.open(filename);
    if (!fin)
    {
        cout << "Error opening file" << endl;
        return false;
    }
    return true;
}

// remove spaces
string stripSpaces(const string &s)
{
    string out;
    for (char c : s)
    {
        if (c != ' ')
            out += c;
    }
    return out;
}

// call the integrate and evlauate
void handleDefiniteIntegral(const string &poly, int lower, int upper)
{
    Bst<Term> binTree;

    parseString(poly, binTree);

    vector<Term> terms = binTree.toVector();
    for (Term &t : terms)
    {
        t.integrateself();
    }

    double upperval = 0, lowerval = 0;
    for (const Term &t : terms)
    {
        upperval += t.evaluateAt(upper);
        lowerval += t.evaluateAt(lower);
    }

    double result = upperval - lowerval;

    printPolynomial(terms);
    cout << ", " << lower << "|" << upper << " = " << fixed << setprecision(3) << result << endl;
}

// If it's NOT a number, do the integral (with + C)
void handleIndefiniteIntegral(const string &poly)
{
    Bst<Term> binTree;

    parseString(poly, binTree);

    vector<Term> terms = binTree.toVector();
    for (Term &t : terms)
    {
        t.integrateself();
    }

    printPolynomial(terms);
    cout << " + C" << endl;
}

// whiole im able to get more from the file keep getting
void processLine(const string &line)
{
    if (line.empty())
        return; // if the line is empty skip it

    Bst<Term> binTree;
    string newLine = "";
    string leftside = "";
    string newRight = "";
    string rightside = "";
    bool isNumber = true;

    size_t pos = line.find("|");

    if (pos != string::npos)
    { // if we find |
        // remove space for the leftside
        for (size_t i = 0; i < pos; i++)
        {
            if (line[i] != ' ')
            {
                leftside += line[i];
            }
        }

        if ((pos == 0) || (pos == line.size()))
        { // there is either no right or no left
            string expr;
            if (pos == 0)
            {
                // everything after '|'
                expr = line.substr(pos + 1);
            }
            else
            {
                // everything before '|'
                expr = line.substr(0, pos);
            }

            newLine.clear();
            for (char c : expr)
            {
                if (c != ' ')
                    newLine += c;
            }
            isNumber = false;
        }
        else
        {
            newRight = line.substr(pos + 1);

            // get just the upperbound
            // first trim rightside leading spaces
            while (!newRight.empty() && isspace(newRight.front()))
            {
                newRight.erase(0, 1);
            }

            if (newRight.empty())
            {
                isNumber = false;
            }
            else
            {
                size_t seprtr = newRight.find(" ");
                rightside = newRight.substr(0, seprtr);
                string rest = newRight.substr(seprtr + 1);

                // now remove the spaces in new line since theyre not consistent
                for (char c : rest)
                {
                    if (c != ' ')
                        newLine += c;
                }

                // check left side if its a number
                if (leftside.size() == 0)
                {
                    isNumber = false;
                }
                else if (leftside[0] != '-')
                {
                    for (char c : leftside)
                    {
                        if (!isdigit(c))
                        {
                            isNumber = false;
                            break;
                        }
                    }
                }
                else
                {
                    size_t i = 0;
                    while (i < (leftside.size() - 1))
                    {
                        if (!isdigit(leftside[i + 1]) || leftside.size() == 1)
                        {
                            isNumber = false;
                            break;
                        }
                        i++;
                    }
                }

                // cjeck right side if its a number
                if (rightside.size() == 0)
                {
                    isNumber = false;
                }
                else if (rightside[0] != '-')
                {
                    for (char c : rightside)
                    {
                        if (!isdigit(c))
                        {
                            isNumber = false;
                            break;
                        }
                    }
                }
                else
                {
                    size_t i = 0;
                    while (i < (rightside.size() - 1))
                    {
                        if (!isdigit(rightside[i + 1]) || rightside.size() == 1)
                        {
                            isNumber = false;
                            break;
                        }
                        i++;
                    }
                }
            }
        }

        if (isNumber)
        { // if it is a number
            int lower = stoi(leftside);
            int upper = stoi(rightside);

            size_t dxPos = newLine.find("dx");
            string poly = newLine.substr(0, dxPos);

            handleDefiniteIntegral(poly, lower, upper);
        }
        else
        {
            size_t dxPos = newLine.find("dx");
            string poly = newLine.substr(0, dxPos);

            handleIndefiniteIntegral(poly);
        }
    }
}
int main()
{
    string filename;
    string line;
    cout << "Enter the name of the file to open" << endl;
    cin >> filename;
    ifstream fin; // try to open the file
    if (!openFile(fin, filename))
    { // case - if it doesnt open
        return 0;
    }
    else
    {
        while (getline(fin, line))
        { // whiole im able to get more from the file keep getting
            processLine(line);
        }
    }
    fin.close();
    return 0;
}
