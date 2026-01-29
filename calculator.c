#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

/* * INTERNAL SETTINGS & GLOBALS
 * ---------------------------
 */
const char *input;
int pos = 0;

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

/* FUNCTION PROTOTYPES */
double parseExpression();
double parseTerm();
double parsePower();
double parseFactor();
void skipSpaces();
void reportError(const char *msg);
void runPreProcessor(char *expr);

/* --- CORE PARSER LOGIC --- */

double parseExpression() {
    double value = parseTerm();
    while (1) {
        skipSpaces();
        if (input[pos] == '+') { pos++; value += parseTerm(); }
        else if (input[pos] == '-') { pos++; value -= parseTerm(); }
        else break;
    }
    return value;
}

double parseTerm() {
    double value = parsePower();
    while (1) {
        skipSpaces();
        if (input[pos] == '*') { pos++; value *= parsePower(); }
        else if (input[pos] == '/') {
            pos++;
            double d = parsePower();
            if (d == 0) reportError("Division by zero");
            value /= d;
        } else break;
    }
    return value;
}

double parsePower() {
    double base = parseFactor();
    skipSpaces();
    if (input[pos] == '^') {
        pos++;
        double exponent = parsePower();
        return pow(base, exponent);
    }
    return base;
}

double parseFactor() {
    skipSpaces();
    
    if (isdigit(input[pos]) || input[pos] == '.') {
        char *end;
        double value = strtod(&input[pos], &end);
        pos = (int)(end - input);
        return value;
    }

    if (isalpha(input[pos])) {
        char name[10];
        int i = 0;
        while (isalpha(input[pos]) && i < 9) name[i++] = input[pos++];
        name[i] = '\0';
        
        if (strcmp(name, "pi") == 0) return M_PI;

        skipSpaces();
        
        if (strcmp(name, "root") == 0) {
            if (input[pos] != '(') reportError("root requires (x, n)");
            pos++;
            double x = parseExpression();
            skipSpaces();
            if (input[pos] != ',') reportError("Comma expected");
            pos++;
            double n = parseExpression();
            skipSpaces();
            if (input[pos] != ')') reportError("Missing ')'");
            pos++;
            return pow(x, 1.0/n);
        }

        double val;
        if (input[pos] == '(') {
            pos++;
            val = parseExpression();
            skipSpaces();
            if (input[pos] != ')') reportError("Missing ')'");
            pos++;
        } else {
            val = parseFactor(); 
        }

        if (strcmp(name, "sqrt") == 0) return sqrt(val);
        if (strcmp(name, "cbrt") == 0) return cbrt(val);
        if (strcmp(name, "ln")   == 0) return log(val);
        if (strcmp(name, "exp")  == 0) return exp(val);
        if (strcmp(name, "sin")  == 0) return sin(val);
        if (strcmp(name, "cos")  == 0) return cos(val);
        if (strcmp(name, "tan")  == 0) return tan(val);
        if (strcmp(name, "asin") == 0) return asin(val);
        if (strcmp(name, "acos") == 0) return acos(val);
        if (strcmp(name, "atan") == 0) return atan(val);
        
        reportError("Unknown identifier");
    }

    if (input[pos] == '(') {
        pos++;
        double value = parseExpression();
        skipSpaces();
        if (input[pos] != ')') reportError("Missing ')'");
        pos++;
        return value;
    }

    if (input[pos] == '-') { 
        pos++; 
        return -parseFactor(); 
    }

    reportError("Unexpected character");
    return 0;
}

/* --- ENHANCED PRE-PROCESSOR --- */

void runPreProcessor(char *expr) {
    char out[2048];
    int j = 0;
    for (int i = 0; expr[i]; i++) {
        unsigned char curr = expr[i];
        unsigned char next = (unsigned char)expr[i+1];
        
        out[j++] = curr;

        // Logic to inject '*' for implicit multiplication
        if ((isdigit(curr) || curr == ')') && (next == '(' || isalpha(next) || (next == 0xE2))) {
             out[j++] = '*';
        }
        
        // Handle UTF-8 Roots
        if (next == 0xE2 && (unsigned char)expr[i+2] == 0x88 && (unsigned char)expr[i+3] == 0x9A) {
            if ((unsigned char)expr[i+4] == 0xC2 && (unsigned char)expr[i+5] == 0xB3) {
                strcat(out + j, "cbrt"); j += 4; i += 5;
            } else {
                strcat(out + j, "sqrt"); j += 4; i += 3;
            }
        }
        else if (next == 0xE2 && (unsigned char)expr[i+2] == 0x88 && (unsigned char)expr[i+3] == 0x9B) {
            strcat(out + j, "cbrt"); j += 4; i += 3;
        }
    }
    out[j] = '\0';
    strcpy(expr, out);
}

void skipSpaces() {
    while (input[pos] != '\0' && isspace((unsigned char)input[pos])) pos++;
}

void reportError(const char *msg) {
    fprintf(stderr, "\n[Error] %s\n", msg);
    exit(EXIT_FAILURE);
}

int main() {
    char buffer[1024];
    printf("----------------------------------------\n");
    printf("            RA7IM CALCULATOR            \n");
    printf("----------------------------------------\n\n");

    while (1) {
        printf("RA7IM > ");
        if (!fgets(buffer, sizeof(buffer), stdin)) break;
        if (strncmp(buffer, "exit", 4) == 0) break;
        
        runPreProcessor(buffer);
        input = buffer;
        pos = 0;
        
        skipSpaces();
        if (input[pos] == '\n' || input[pos] == '\0') continue;
        
        printf("result = %.10g\n\n", parseExpression());
    }
    return 0;
}
    