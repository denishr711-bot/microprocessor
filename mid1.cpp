#include <iostream>
#include <cmath>

using namespace std;

double calculate_sqrt(double num) {
    if (num < 0) {
        return -1; 
    }
    return sqrt(num);
}

int main() {
    // Test Case 1
    cout << "Test 1 (Perfect Square): Input 16.0 -> Expected: 4 -> Got: " 
         << calculate_sqrt(16.0) << endl;

    // Test Case 2
    cout << "Test 2 (Zero Boundary):  Input 0.0  -> Expected: 0 -> Got: " 
         << calculate_sqrt(0.0) << endl;

    // Test Case 3
    cout << "Test 3 (Negative Input): Input -9.0 -> Expected: -1 -> Got: " 
         << calculate_sqrt(-9.0) << endl;

    // Test Case 4
    cout << "Test 4 (Irrationals):    Input 2.0  -> Expected: 1.41421 -> Got: " 
         << calculate_sqrt(2.0) << endl;

    // Test Case 5
    cout << "Test 5 (Fractional):     Input 0.04 -> Expected: 0.2 -> Got: " 
         << calculate_sqrt(0.04) << endl;

    return 0;
}
