# 🚀 Smart Systems Suite (Restaurant & Advanced Calculator)

Welcome to my multi-language programming portfolio. This repository showcases a collection of professional-grade tools ranging from business management systems to high-performance mathematical engines.

---

## 🧮 1. RA7IM Calculator (Advanced Math Engine)
A high-performance command-line calculator built in C. It uses a recursive descent parser to evaluate complex mathematical expressions with precision.

### Features:
* Recursive Parsing: Handles operator precedence (^, *, /, +, -) and nested parentheses.
* Scientific Functions: Supports sqrt, cbrt, sin, cos, tan, ln, exp, and more.
* Implicit Multiplication: Intelligent pre-processor that understands 2(5+5) as 2*(5+5).
* Constants & Special Roots: Built-in support for pi and custom root calculations using root(x, n).

---

## 🍽️ 2. Smart Restaurant Management System
An integrated system to handle restaurant operations using C, Python, and Web technologies.

### Components:
* **C Backend (restaurant.c):** Handles core order processing and permanent data storage in orders.txt.
* **Python Analytics (Restaurant 1.py):** An administrative dashboard for revenue calculation and sales trends analysis.
* **Web Dashboard (restaurant html.html):** A modern UI built with HTML/CSS/JS to visualize orders and daily statistics.

---

## 🛠️ How to Compile aFor RA7IM Calculator:alculator:**
`bash
gcc calculator_code.c -o calculator -lm
./calculator
