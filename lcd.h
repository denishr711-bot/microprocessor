#ifndef LCD_H
#define LCD_H

#include <iostream>
using namespace std;

class LCD {
public:

    void display(string line1, string line2) {

        cout << "LCD DISPLAY" << endl;
        cout << line1 << endl;
        cout << line2 << endl;
    }
};

#endif
