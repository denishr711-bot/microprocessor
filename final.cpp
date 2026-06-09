#include <iostream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <chrono> // For Requirement (e): Performance execution timing
#include <thread>
#include <gpiod.hpp> // Requirement (d): Raspberry Pi hardware interface

using namespace std;

// Requirement (a): Custom linear data structure built without using STL containers
class CustomDeck {
private:
    static const int MAX_CAPACITY = 52;
    int cards[MAX_CAPACITY]; // Raw array implementation replacing STL vector/stack
    int topIndex;

public:
    CustomDeck() {
        reset();
    }

    // Refills the internal storage structure back to its base state
    void reset() {
        topIndex = 0;
        for (int i = 0; i < 4; ++i) {
            for (int faceValue = 1; faceValue <= 13; ++faceValue) {
                cards[topIndex++] = faceValue;
            }
        }
    }

    // In-place shuffling routine
    void shuffleDecks() {
        if (topIndex <= 1) return; 
        for (int i = topIndex - 1; i > 0; --i) {
            int j = rand() % (i + 1);
            int temp = cards[i];
            cards[i] = cards[j];
            cards[j] = temp;
        }
    }

    bool isEmpty() const { return topIndex == 0; }
    int size() const { return topIndex; }

    // Requirement (b): Safe bounds-checking with exception handling
    int popCard() {
        if (isEmpty()) {
            throw runtime_error("Underflow Error: Attempted to draw from an empty deck.");
        }
        return cards[--topIndex]; 
    }
};

int getCardValue(int faceValue) {
    if (faceValue > 10) return 10; 
    if (faceValue == 1) return 11; 
    return faceValue;
}

void printCardName(int faceValue) {
    if (faceValue == 1) cout << "Ace";
    else if (faceValue == 11) cout << "Jack";
    else if (faceValue == 12) cout << "Queen";
    else if (faceValue == 13) cout << "King";
    else cout << faceValue;
}

bool isButtonPressed(gpiod::line& pin, bool& lastState) {
    bool currentState = (pin.get_value() == 0); 
    if (currentState && !lastState) {
        this_thread::sleep_for(chrono::milliseconds(50)); // Debounce window
        lastState = currentState;
        return true;
    }
    lastState = currentState;
    return false;
}

// Requirement (b) & (e): Structural automated verification suite with execution benchmarking
void runUnitTests() {
    cout << "=== Running Structural Verification & Performance Profiling ===\n";
    
    // Benchmark Initialization 
    auto startInit = chrono::high_resolution_clock::now();
    CustomDeck testDeck;
    auto endInit = chrono::high_resolution_clock::now();
    auto initDuration = chrono::duration_cast<chrono::nanoseconds>(endInit - startInit).count();
    
    if (testDeck.size() == 52) {
        cout << "[PASS] Deck initialized with 52 cards. Execution Time: " << initDuration << " ns\n";
    } else {
        cout << "[FAIL] Incorrect deck size matching initialization.\n";
    }

    // Benchmark Shuffling
    auto startShuffle = chrono::high_resolution_clock::now();
    testDeck.shuffleDecks();
    auto endShuffle = chrono::high_resolution_clock::now();
    auto shuffleDuration = chrono::duration_cast<chrono::nanoseconds>(endShuffle - startShuffle).count();
    cout << "[INFO] Shuffle operation execution time: " << shuffleDuration << " ns\n";

    // Exception Handling verification
    try {
        for (int i = 0; i < 53; ++i) {
            testDeck.popCard();
        }
        cout << "[FAIL] Failed to intercept structural underflow.\n";
    } catch (const runtime_error& e) {
        cout << "[PASS] Exception successfully handled: " << e.what() << "\n";
    }
    cout << "================================================================\n\n";
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    
    // Core structural verification execution
    runUnitTests();

    // Requirement (d): Setting up physical pin interfaces 
    gpiod::chip chip("0"); 
    gpiod::line hitPin = chip.get_line(17);   // Pin 11 on board (GPIO 17)
    gpiod::line standPin = chip.get_line(27); // Pin 13 on board (GPIO 27)
    gpiod::line resetPin = chip.get_line(22); // Pin 15 on board (GPIO 22)

    hitPin.request({"Blackjack", gpiod::line_request::DIRECTION_INPUT, gpiod::line_request::FLAG_BIAS_PULL_UP});
    standPin.request({"Blackjack", gpiod::line_request::DIRECTION_INPUT, gpiod::line_request::FLAG_BIAS_PULL_UP});
    resetPin.request({"Blackjack", gpiod::line_request::DIRECTION_INPUT, gpiod::line_request::FLAG_BIAS_PULL_UP});

    bool lastHitState = false;
    bool lastStandState = false;
    bool lastResetState = false;

    CustomDeck deck;

    while (true) {
        deck.reset();
        deck.shuffleDecks();

        cout << "=== Blackjack Ready ===\n";
        cout << "Cards remaining in deck: " << deck.size() << "\n\n";

        try {
            int pCard1 = deck.popCard();
            int pCard2 = deck.popCard();
            int playerTotal = getCardValue(pCard1) + getCardValue(pCard2);

            int dCard1 = deck.popCard();
            int dCard2 = deck.popCard();
            int dealerTotal = getCardValue(dCard1) + getCardValue(dCard2);

            cout << "Your Hand: "; printCardName(pCard1); cout << " & "; printCardName(pCard2);
            cout << " | Current Value: " << playerTotal << "\n";
            cout << "Dealer Visible Item: "; printCardName(dCard1); cout << "\n\n";

            bool playerTurn = true;
            while (playerTurn && playerTotal < 21) {
                if (isButtonPressed(hitPin, lastHitState)) {
                    int drawnCard = deck.popCard();
                    playerTotal += getCardValue(drawnCard);
                    cout << ">> Hit! Drew: "; printCardName(drawnCard); cout << " | New Value: " << playerTotal << "\n";
                }
                if (isButtonPressed(standPin, lastStandState)) {
                    cout << ">> Stood.\n";
                    playerTurn = false;
                }
                this_thread::sleep_for(chrono::milliseconds(10));
            }

            if (playerTotal > 21) {
                cout << "\nResult: Player Busted! Dealer Wins.\n";
            } else {
                cout << "\nDealer Playing... Base Hand Total: " << dealerTotal << "\n";
                while (dealerTotal < 17) {
                    this_thread::sleep_for(chrono::milliseconds(800));
                    int drawnCard = deck.popCard();
                    dealerTotal += getCardValue(drawnCard);
                    cout << ">> Dealer Drew: "; printCardName(drawnCard); cout << " | New Total: " << dealerTotal << "\n";
                }

                cout << "\n=== Final Calculations ===\n";
                cout << "User Hand: " << playerTotal << " | House Hand: " << dealerTotal << "\n";
                if (dealerTotal > 21 || playerTotal > dealerTotal) cout << "Outcome: You Win!\n";
                else if (playerTotal < dealerTotal) cout << "Outcome: House Wins.\n";
                else cout << "Outcome: Push (Tie).\n";
            }

        } catch (const runtime_error& e) {
            cout << "Structural Fail: " << e.what() << "\n";
        }

        cout << "\n[Press physical Reset Button (GPIO 22) to run a new round...]\n";
        while (true) {
            if (isButtonPressed(resetPin, lastResetState)) break;
            this_thread::sleep_for(chrono::milliseconds(10));
        }
    }
    return 0;
}

// g++ -g -O0 main.cpp -o blackjack_debug -lgpiodcxx
// gdb ./blackjack_debug
