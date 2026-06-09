#include <iostream>
using namespace std;

void stackExample() {
    int localVar = 50;
    cout << "[Stack] localVar = " << localVar 
         << ", Address = " << &localVar << endl;
}

int main() {

    cout << "===== BASIC DATA TYPES =====" << endl;
    int a = 10;
    float b = 3.14;
    char c = 'A';

    cout << "a = " << a << " (Address: " << &a << ")" << endl;
    cout << "b = " << b << " (Address: " << &b << ")" << endl;
    cout << "c = " << c << " (Address: " << (void*)&c << ")" << endl;

    cout << "\n===== STACK MEMORY =====" << endl;
    stackExample();

    cout << "\n===== HEAP MEMORY =====" << endl;
    int* p = new int(100);
    cout << "Heap value = " << *p 
         << ", Address = " << p << endl;
    delete p;

    cout << "\n===== POINTERS =====" << endl;
    int x = 25;
    int* ptr = &x;
    cout << "Value of x = " << x << endl;
    cout << "Address of x = " << ptr << endl;
    cout << "Value via pointer = " << *ptr << endl;

    cout << "\n===== ARRAY (STACK) =====" << endl;
    int arr[3] = {1,2,3};
    for(int i = 0; i < 3; i++) {
        cout << "arr[" << i << "] = " << arr[i] 
             << " (Address: " << &arr[i] << ")" << endl;
    }

    cout << "\n===== DYNAMIC ARRAY (HEAP) =====" << endl;
    int* darr = new int[3]{10,20,30};
    for(int i = 0; i < 3; i++) {
        cout << "darr[" << i << "] = " << darr[i] 
             << " (Address: " << &darr[i] << ")" << endl;
    }
    delete[] darr;

    cout << "\n===== REFERENCE =====" << endl;
    int val = 5;
    int& ref = val;
    ref = 20;
    cout << "val = " << val << endl;

    cout << "\n===== MEMORY LEAK DEMO =====" << endl;
    int* leak = new int(999);
    cout << "Leaked value = " << *leak << endl;
    // delete leak; // Uncomment to fix

    return 0;
}