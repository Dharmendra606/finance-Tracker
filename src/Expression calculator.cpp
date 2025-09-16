#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cctype>
#include <cmath>
#include <map>

using namespace std;

// Helper function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Operator precedence
int precedence(char op) {
    if (op == '+' || op == '-') return 1;
    if (op == '*' || op == '/') return 2;
    return 0;
}

// Apply operator to two operands
double applyOp(double a, double b, char op) {
    switch(op) {
        case '+': return a + b;
        case '-': return a - b;
        case '*': return a * b;
        case '/':
            if (b == 0) {
                throw runtime_error("Division by zero!");
            }
            return a / b;
    }
    return 0;
}

// Evaluate expression given as a string
double evaluateExpression(const string& expr) {
    stack<double> values;
    stack<char> ops;

    for (size_t i = 0; i < expr.length(); i++) {
        // Skip spaces
        if (expr[i] == ' ') continue;

        // If digit or decimal, parse the number
        if (isdigit(expr[i]) || expr[i] == '.') {
            string valStr;
            // Read full number including decimals
            while (i < expr.length() && (isdigit(expr[i]) || expr[i] == '.')) {
                valStr += expr[i++];
            }
            i--; // step back for next iteration
            double val = stod(valStr);
            values.push(val);
        }
        // Opening parenthesis
        else if (expr[i] == '(') {
            ops.push(expr[i]);
        }
        // Closing parenthesis: solve entire bracket
        else if (expr[i] == ')') {
            while (!ops.empty() && ops.top() != '(') {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            if (!ops.empty()) ops.pop(); // remove '('
            else throw runtime_error("Mismatched parentheses");
        }
        // Operator
        else if (isOperator(expr[i])) {
            while (!ops.empty() && precedence(ops.top()) >= precedence(expr[i])) {
                double val2 = values.top(); values.pop();
                double val1 = values.top(); values.pop();
                char op = ops.top(); ops.pop();
                values.push(applyOp(val1, val2, op));
            }
            ops.push(expr[i]);
        }
        else {
            throw runtime_error("Invalid character in expression");
        }
    }

    // Final evaluation
    while (!ops.empty()) {
        double val2 = values.top(); values.pop();
        double val1 = values.top(); values.pop();
        char op = ops.top(); ops.pop();
        values.push(applyOp(val1, val2, op));
    }

    if (values.size() != 1)
        throw runtime_error("Invalid expression");

    return values.top();
}

int main() {
    cout << "Enter arithmetic expression to evaluate:\n";
    string expression;
    getline(cin, expression);

    try {
        double result = evaluateExpression(expression);
        cout << "Result: " << result << "\n";
    } catch (const exception& e) {
        cout << "Error: " << e.what() << "\n";
    }

    return 0;
}
