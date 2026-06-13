#include <iostream>
#include <stack>

using namespace std;

int main() {
    string expr;
    getline(cin, expr);  // Read the entire expression as a string
    stack<char> operators;
    stack<double> values;
    
    for (size_t i = 0; i < expr.length(); i++) {
        char ch = expr[i];

        if (ch == ' ') {
            continue;  // Skip spaces
        } else if (ch == '(') {
            continue;  // Ignore opening parentheses
        } else if (ch == '+' || ch == '*') {
            operators.push(ch);  // Store operators
        } else if (ch == ')') {
            char op = operators.top();
            operators.pop();
            double v = values.top();
            values.pop();

            if (op == '+') {
                v = values.top() + v;
                values.pop();
            } else if (op == '*') {
                v = values.top() * v;
                values.pop();
            }
            values.push(v);
        } else {  // If it's a number
            double num = ch - '0';  // Convert character to number (assuming single-digit numbers)
            values.push(num);
        }
    }

    cout << values.top() << endl;  // Print the final result
    return 0;
}
