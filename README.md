# Integration Calculator 

This project implements a binary search tree of polynomial terms and uses it to compute indefinite and definite integrals. Polynomial expressions are read from an input file, parsed into Term objects, inserted into a templated binary search tree, and then integrated using the power rule. Results are written to a console.

## Project Structure
main.cpp  
BinTree.h  
Node.h  
Term.h  
term.cpp  


## Overview
Each polynomial expression is broken into individual terms. These terms are stored in a templated binary search tree, ordered by exponent. The tree supports insertion, traversal, and evaluation. Integration is performed by applying the power rule to each term, and definite integrals are computed by evaluating the antiderivative at the upper and lower bounds.

## Features
- Parses polynomial expressions from a text file
- Stores terms in a templated binary search tree
- Supports positive and negative coefficients
- Handles constant terms and higher‑degree terms
- Computes indefinite integrals
- Computes definite integrals when both bounds are provided
- Outputs results in standard mathematical form

## Example Input
| 3x^2 + 2x + 1 dx
2 | 1 1x^-2 + 3x + 4 dx
1| 2 1x^3 - 4x dx
1|2 10x^-2 - 3x^10 + 4x^3 dx
1 |2 0x^5 + 0x^3 + 0x^0 + 0x dx
1| 2 5x^5 + 0 dx 
|5x^5 + 0x^0 dx 


## Example Output
x^3 + x^2 + x + C
(3/2)x^2 + 4x - x^-1, 2|1 = -9.000
(1/4)x^4 - 2x^2, 1|2 = -2.250
(-3/11)x^11 + x^4 - 10x^-1, 1|2 = -538.273
0, 1|2 = 0.000
(5/6)x^6, 1|2 = 52.500
(5/6)x^6 + C

## How to Compile
Compile the project using g++:

g++ main.cpp Term.cpp -o integrate

BinTree.h and Node.h are header‑only templates and do not require separate compilation.

## How to Run
On Windows:

integrate.exe

On Mac/Linux:

./integrate

Ensure that the input file is in the same directory as the executable.

## Possible Extensions
- Improved error handling for malformed expressions
- Support for more complex integrals
- Additional mathematical functions

## Author
Osagbewonrue Anthony Ugiagbe  
University of Texas at Dallas
