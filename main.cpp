// #include "src/SystemManager.h"
//
// int main() {
//     SystemManager system;
//     system.run();
//     return 0;
// }
//

#include <iostream>
#include <stack>
#include <cctype>
using namespace std;

// bool isOperand(char ch) {
//     if (ch >= '0' && ch <= '9') return true;
//     if (ch >= 'a' && ch <= 'z') return true;
//     if (ch >= 'A' && ch <= 'Z') return true;
//
//     return false;
// }
//
// int precedence(char ch) {
//     if (ch == '+' || ch == '-') return 1;
//     if (ch == '*' || ch == '/') return 2;
// }
//
// string infixToPostfix(string infix) {
//     string postfix = "";
//     stack<char> st;
//
//     for (char ch : infix) {
//         if (isOperand(ch)) {
//             postfix += ch;
//         }
//
//         else if (ch == '(') {
//             st.push(ch);
//         }
//
//         else if (ch == ')') {
//             while (!st.empty() && st.top() != '(') {
//                 postfix += st.top();
//                 st.pop();
//             }
//             st.pop();
//         }
//
//         else {
//             while (!st.empty() && st.top() != '(' && precedence(st.top()) >= precedence(ch)) {
//                 postfix += st.top();
//                 st.pop();
//             }
//             st.push(ch);
//         }
//     }
//
//     while (!st.empty()) {
//         postfix += st.top();
//         st.pop();
//     }
//
//     return postfix;
// }
//
// int evaluatePostfix(string postfix) {
//     stack<char> st;
//
//     for (char ch : postfix) {
//         if (isdigit(ch)) {
//             st.push(ch - '0');
//         }
//
//         else {
//             int val2 = st.top(); st.pop();
//             int val1 = st.top(); st.pop();
//             int result;
//
//             switch (ch) {
//                 case '+': result = val1 + val2; break;
//                 case '-': result = val1 - val2; break;
//                 case '*': result = val1 * val2; break;
//                 case '/': result = val1 / val2; break;
//             }
//
//             st.push(result);
//         }
//     }
//
//     return st.top();
// }

#define MAX 10

struct Queue {

};

int main() {










    // string infix = "9+(6*4)/3";
    //
    // string postfix = infixToPostfix(infix);
    // int result = evaluatePostfix(postfix);
    //
    // cout << result << endl;
}