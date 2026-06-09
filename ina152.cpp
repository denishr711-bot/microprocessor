/**********************************************************

Seattle University - ECEGR-2030

Project: Hashing Exercise
Description: C++ program to implement hashing
using chaining and open addressing.


***********************************************************/

#include <iostream>
#include <vector>
#include <string>

using namespace std;

// Hash table class using chaining
class HashTableChaining {

private:

    static const int SIZE = 10;

    vector<string> table[SIZE];

public:

    // Hash function
    int hashFunction(string game) {

        /* TODO:
            Create an integer variable called sum initialized to 0
            Loop through every character in game to:
                * add ASCII value of character to sum
            Return sum modulo SIZE
        */
		int sum = 0;
		for (char c : game) {
            sum += int(c);
        }
		return sum % SIZE;
    }

    // Insert using chaining
    void insert(string game) {

        /* TODO:
            Compute hash index using hashFunction()
            Insert game into table at index using push_back()
        */
		int index = hashFunction(game);
        table[index].push_back(game);
    }

    // Display hash table
    void display() {

        /* TODO:
            Loop through all rows in hash table
            Output row number
            Loop through vector at each row to:
                * output each game followed by " -> "
            Output newline
        */
		for (int i = 0; i < SIZE; i++) {
            cout << i << ": ";
            for (string game : table[i]) {
                cout << game << " -> ";
            }
            cout << "\n";
        }
    }
};


// Hash table class using open addressing
class HashTableOpenAddressing {

private:

    static const int SIZE = 10;

    string table[SIZE];

public:

    // Constructor
    HashTableOpenAddressing() {

        /* TODO:
            Loop through the table
            Initialize every row to empty string ""
        */
		for (int i = 0; i < SIZE; i++) {
            table[i] = "";
        }
    }

    // Hash function
    int hashFunction(string game) {

        /* TODO:
            Create an integer variable called sum initialized to 0
            Loop through every character in game to:
                * add ASCII value of character to sum
            Return sum modulo SIZE
        */
		int sum = 0;
		for (char c : game) {
            sum += int(c);
        }
		return sum % SIZE;
    }

    // Insert using linear probing
    void insert(string game) {

        /* TODO:
            Compute hash index using hashFunction()

            Loop while table at index is NOT empty string:
                * move to next index using:
                    (index + 1) % SIZE

            Insert game into empty position
        */
		int index = hashFunction(game);
		while (table[index] != "") {
            index = (index + 1) % SIZE;
        }
        table[index] = game;
    }

    // Display hash table
    void display() {

        /* TODO:
            Loop through all rows in table
            Output row number and stored game
        */
		for (int i = 0; i < SIZE; i++) {
            cout << i << ": " << table[i] << "\n";
        }
    }
};


int main() {

    cout << "----- HASHING WITH CHAINING -----\n";

    HashTableChaining chainingTable;

    /* TODO:
        Insert:
            Zelda
            Halo
            Mario
            Metroid

        Display the chaining table
    */
	chainingTable.insert("Zelda");
	chainingTable.insert("Halo");
	chainingTable.insert("Mario");
	chainingTable.insert("Metroid");

	chainingTable.display();

    cout << "\n----- HASHING WITH OPEN ADDRESSING -----\n";

    HashTableOpenAddressing openTable;

    /* TODO:
        Insert:
            Zelda
            Halo
            Mario
            Metroid

        Display the open addressing table
    */
	openTable.insert("Zelda");
	openTable.insert("Halo");
	openTable.insert("Mario");
	openTable.insert("Metroid");

	openTable.display();
	
    return 0;
}