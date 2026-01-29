# 🧮 RA7IM CALCULATOR (Advanced C Math Engine)

A powerful, high-performance command-line calculator built in C. This project uses a Recursive Descent Parser to evaluate complex mathematical expressions with high precision, handling operator precedence and scientific functions natively.



## 🌟 Key Features

* Advanced Expression Parsing: Handles nested parentheses and standard operator precedence (^ power, * multiplication, / division, + addition, - subtraction).
* Scientific Function Support: Built-in support for trigonometric and logarithmic functions:
    * sin, cos, tan, asin, acos, atan
    * sqrt (square root), cbrt (cube root), ln (natural log), exp.
* Implicit Multiplication: Automatically detects and handles implicit operations like 2(5+5) or 5pi.
* Smart Pre-processor: Supports Unicode symbols like square roots (√) and cube roots (∛) directly from the input.
* Custom Root Function: Ability to calculate any nth root using the syntax root(x, n).
* Mathematical Constants: Built-in high-precision pi.

## 🛠️ Technical Implementation

The calculator works in three main stages:
1.  Pre-processing: Sanitizes input and injects missing operators (like *).
2.  Lexical Analysis: Breaks down the string into recognizable mathematical "tokens".
3.  Recursive Parsing: Evaluates the tokens based on mathematical grammar rules (Expressions -> Terms -> Powers -> Factors).

## 🚀 How to Compile and Run

To compile the calculator on a Linux/Unix or macOS system, you need to link the math library using the -lm flag:

`bash
gcc calculator.c -o ra7im_calc -lm
./ra7im_calc
