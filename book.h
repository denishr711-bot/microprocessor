#ifndef BOOK_H
#define BOOK_H

#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string shelf;

    Book(int i, string t, string s) {
        id = i;
        title = t;
        shelf = s;
    }
};

#endif
