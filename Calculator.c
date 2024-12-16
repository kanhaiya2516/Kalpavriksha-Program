#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isOperator(char c) {
    return (c == '+' || c == '-' || c == '*' || c == '/');
}

int precedence(char operator) {
    if (operator == '+' || operator == '-') {
        return 1;
    } else if (operator == '*' || operator == '/') {
        return 2;
    }
    return 0;
}

double fun(double a, double b, char operator) {
    if(operator == '+') return a + b;
    else if(operator == '-') return a - b;
    else if(operator == '/') {
         if (b == 0) {
            printf("Error: Division by zero.\n");
            exit(1);
        }
        return a / b;
    }
    else return 0;
}

double fun1(char* expression) {
    double values[110];
    char operators[110];
    int valueTop = -1, operatorTop = -1;

    int i = 0;

    int len = strlen(expression);

    while (i < len) {
        char ch = expression[i];

        if (ch == ' ') {
            i++;
            continue;
        }

        if (isdigit(ch) || ch == '.') {
            char numStr[20];
            int j = 0;

            while ((isdigit(expression[i]) || expression[i] == '.') && i < len) {
                numStr[j++] = expression[i++];
            }
            numStr[j] = '\0';

            values[++valueTop] = atof(numStr);
        }

        else if (isOperator(ch)) {
            while (operatorTop >= 0 && precedence(operators[operatorTop]) >= precedence(ch)) {
                double b = values[valueTop--];
                double a = values[valueTop--];
                char op = operators[operatorTop--];

                values[++valueTop] = fun(a, b, op);
            }
            operators[++operatorTop] = ch;
            i++;
        } else {
            printf("Error: Invalid operator.\n");
            exit(1);
        }
    }

    while (operatorTop >= 0) {
        double b = values[valueTop--];
        double a = values[valueTop--];
        char op = operators[operatorTop--];

        values[++valueTop] = fun(a, b, op);
    }
    return values[valueTop];
}

int main() {
    char expression[100];
    printf("Enter a mathematical expression: ");
    fgets(expression, sizeof(expression), stdin);

    expression[strcspn(expression, "\n")] = '\0';

    double result = fun1(expression);
    printf("Result: %.2lf\n", result);

    return 0;
}