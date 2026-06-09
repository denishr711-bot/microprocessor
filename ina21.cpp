#include <iostream>
using namespace std;

// TODO 3: Modify this function to use a static variable
void counter() {
    static int count = 0;
    count++;
    cout << "Counter value: " << count << endl;
}

// TODO 2: Modify value using pointer
void modify(int* p) {
    *p = 99;// modify value here
}

// TODO 4: Reference example
void refModify(int& r) {
    r = 500;// modify value here
}

int main() {

    cout << "===== STACK VARIABLE =====" << endl;
    
    // TODO 1: Add another stack variable and print its address
    int x = 10;
    cout << "Value x: " << x << ", Address: " << &x << endl;

    int y = 30; // <-- students observe proximity in memory
    cout << "Value y: " << y << ", Address: " << &y << endl;

    int z = 50;  
    cout << "Value z: " << z << ", Address: " << &z << endl;

    cout << "\n===== HEAP VARIABLE =====" << endl;

    int* p = new int(20);
    cout << "Value: " << *p << ", Address: " << p << endl;

    cout << "\n===== POINTER FUNCTION =====" << endl;
    modify(&x);
    cout << "Modified x: " << x << endl;

    cout << "\n===== REFERENCE FUNCTION =====" << endl;
    refModify(x);
    cout << "Modified x again: " << x << endl;

    cout << "\n===== STATIC DEMO =====" << endl;
    counter();
    counter();
    counter();

    cout << "\n===== DYNAMIC ARRAY =====" << endl;

    int* arr = new int[3];

    // TODO 5: initialize and print values + addresses
    for(int i = 0; i < 3; i++) {
        arr[i] = (i + 1) * 10;
        cout << "Arr[" << i << "]: " << arr[i] << " at " << &arr[i] << endl;
    }

    // TODO 6: free memory properly

    delete p;   // keep this or move into TODO 6
    delete[] arr;

    return 0;
}