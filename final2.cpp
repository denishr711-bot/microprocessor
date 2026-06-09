#include <iostream>
#include <stdexcept>
#include <random>
#include <chrono>

using namespace std;

// Requirement (a): Custom linear data structure replacing STL
class CustomDeck {
private:
    static const int MAX_CARDS = 52;
    int cards[MAX_CARDS];
    int topIndex; 

public:
    CustomDeck() {
        resetDeck();
    }

    void resetDeck() {
        topIndex = 0;
        for (int i = 0; i < 4; ++i) {
            for (int faceValue = 1; faceValue <= 13; ++faceValue) {
                cards[topIndex++] = faceValue;
            }
        }
    }

    void shuffleDecks() {
        resetDeck(); 
        unsigned seed = chrono::system_clock::now().time_since_epoch().count();
        mt19937 gen(seed);

        for (int i = topIndex - 1; i > 0; --i) {
            uniform_int_distribution<int> dist(0, i);
            int j = dist(gen);
            swap(cards[i], cards[j]);
        }
    }

    bool isEmpty() const { return topIndex == 0; }
    int size() const { return topIndex; }

    int popCard() {
        if (isEmpty()) {
            throw runtime_error("Underflow Error: Empty deck.");
        }
        return cards[--topIndex];
    }
};

// Requirement (a/b): Core evaluation logic
// If Ace (11) + other cards > 21, the Ace value drops to 1. Otherwise, it stays 11.
int calculateHandTotal(const int hand[], int cardCount) {
    int total = 0;
    int aceCount = 0;

    for (int i = 0; i < cardCount; ++i) {
        int face = hand[i];
        if (face == 1) {
            aceCount++;
            total += 11; // Assume Ace is 11 initially
        } else if (face > 10) {
            total += 10;
        } else {
            total += face;
        }
    }

    // "if ace + total value of cards is over 21 then ace value is 1"
    while (total > 21 && aceCount > 0) {
        total -= 10; // Reduces an Ace from 11 down to 1
        aceCount--;
    }

    return total;
}

void printCardName(int faceValue) {
    if (faceValue == 1) cout << "Ace";
    else if (faceValue == 11) cout << "Jack";
    else if (faceValue == 12) cout << "Queen";
    else if (faceValue == 13) cout << "King";
    else cout << faceValue;
}

int main() {
    CustomDeck deck;
    char playAgain;

    cout << "=== Simple Blackjack ===\n";

    do {
        deck.shuffleDecks();
        cout << "\n--- New Round Started ---\n";

        try {
            // Fixed array syntax to ensure multi-card storage works safely
            int playerHand[15] = {0}; 
            int dealerHand[15] = {0};
            int pCount = 0;
            int dCount = 0;

            // Deal initial cards
            playerHand[pCount++] = deck.popCard();
            playerHand[pCount++] = deck.popCard();
            int playerTotal = calculateHandTotal(playerHand, pCount);

            dealerHand[dCount++] = deck.popCard();
            dealerHand[dCount++] = deck.popCard();
            int dealerTotal = calculateHandTotal(dealerHand, dCount);

            cout << "Your starting total: " << playerTotal << " (Drew ";
            printCardName(playerHand[0]);
            cout << " and ";
            printCardName(playerHand[1]);
            cout << ")\n";
            
            cout << "Dealer's visible card: ";
            printCardName(dealerHand[0]);
            cout << "\n\n";

            // Player hit/stand loop
            char choice;
            while (playerTotal < 21) {
                cout << "Do you want to (h)it or (s)tand? ";
                cin >> choice;
                if (choice == 'h' || choice == 'H') {
                    playerHand[pCount++] = deck.popCard();
                    playerTotal = calculateHandTotal(playerHand, pCount);
                    
                    cout << "You drew a ";
                    printCardName(playerHand[pCount - 1]);
                    cout << ". New total: " << playerTotal << "\n\n";
                } else {
                    break;
                }
            }

            if (playerTotal > 21) {
                cout << "You busted! Dealer wins.\n";
            } else {
                // Dealer turn logic
                cout << "\nDealer's turn. Starting total: " << dealerTotal << "\n";
                while (dealerTotal < 17) {
                    dealerHand[dCount++] = deck.popCard();
                    dealerTotal = calculateHandTotal(dealerHand, dCount);
                    
                    cout << "Dealer draws a ";
                    printCardName(dealerHand[dCount - 1]);
                    cout << ". New total: " << dealerTotal << "\n";
                }

                // Score checking
                cout << "\n=== Final Results ===\n";
                cout << "Your Total: " << playerTotal << "\n";
                cout << "Dealer Total: " << dealerTotal << "\n";

                if (dealerTotal > 21) cout << "Dealer busted! You win!\n";
                else if (playerTotal > dealerTotal) cout << "You win!\n";
                else if (playerTotal < dealerTotal) cout << "Dealer wins.\n";
                else cout << "It's a tie (Push)!\n";
            }

        } catch (const runtime_error& e) {
            cout << "Game Error: " << e.what() << "\n";
        }

        cout << "\nDo you want to play another round? (y/n): ";
        cin >> playAgain;

    } while (playAgain == 'y' || playAgain == 'Y');

    cout << "\nThanks for playing!\n";
    return 0;
}
//g++ -o final2 final2.cpp