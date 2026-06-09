#include <iostream>
using namespace std;

int main() {
    int val = 0;       
    int *ptr = &val;   
    *ptr = 25;         
    
    cout << "Value: " << *ptr << endl; 
    return 0;
}
