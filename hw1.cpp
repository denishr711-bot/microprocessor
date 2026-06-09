#include <iostream>
#include <stack>
#include <string>
using namespace std;

bool hasValidBrackets(string expr) {
    stack<char> st;

    for (char ch : expr) {
        if (ch == '(' || ch == '{' || ch == '[') {
            st.push(ch);
        }
        else if (ch == ')' || ch == '}' || ch == ']') {
            if (st.empty()) return false;

            char top = st.top();
            st.pop();

            if ((ch == ')' && top != '(') ||
                (ch == '}' && top != '{') ||
                (ch == ']' && top != '[')) {
                return false;
            }
        }
    }

    return st.empty();
}

bool runTests() {
    string validTests[] = {
        "[()]{}{[()()]()}",
        "()",
        "{[()]}",
        "((()))[]{}"
    };

    string invalidTests[] = {
        "[()(}",
        "[(])",
        "((()",
        "}{"
    };
    bool allPassed = true;

    cout << "=== Testing Balanced Expressions ===" << endl;
    for (string test : validTests) {
        bool result = hasValidBrackets(test);
        cout << "Expression: " << test 
             << " -> Result: " << (result ? "Valid" : "Invalid") << endl;

        if (!result) allPassed = false;
    }

    cout << "\n=== Testing Unbalanced Expressions ===" << endl;
    for (string test : invalidTests) {
        bool result = hasValidBrackets(test);
        cout << "Expression: " << test 
             << " -> Result: " << (result ? "Valid" : "Invalid") << endl;

        if (result) allPassed = false;
    }

    return allPassed;
}
int main() {
    bool success = runTests();

    cout << "\n=== Unit Test Result ===" << endl;
    if (success) {
        cout << "All unit tests passed successfully." << endl;
    } else {
        cout << "Some unit tests failed." << endl;
    }

    return 0;
}