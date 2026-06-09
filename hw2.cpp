#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <pigpio.h> // Library for GPIO control
#include <unistd.h> // For usleep

using namespace std;

#define BUTTON_PIN 2 // Connect button to GPIO 2 and GND

int main() {
    // Initialize GPIO
    if (gpioInitialise() < 0) return 1;
    gpioSetMode(BUTTON_PIN, PI_INPUT);
    gpioSetPullUpDown(BUTTON_PIN, PI_PUD_UP);

    queue<int> requestQueue;
    stack<int> historyStack;
    vector<int> originalInputs;

    cout << "System Ready. Press button to simulate 5 requests." << endl;

    // 1. Collect inputs via sensor
    while (requestQueue.size() < 5) {
        if (gpioRead(BUTTON_PIN) == 0) { // Assuming active low button
            int requestId = (requestQueue.size() + 1) * 10; // e.g., 10, 20...
            cout << "Request " << requestId << " captured!" << endl;
            
            requestQueue.push(requestId);
            originalInputs.push_back(requestId);
            
            usleep(500000); // 0.5s debounce delay
        }
    }

    // 2. Process Queue and move to Stack
    cout << "\n--- Processing Queue (FIFO) ---" << endl;
    while (!requestQueue.empty()) {
        int current = requestQueue.front();
        cout << "Processing: " << current << endl;
        historyStack.push(current);
        requestQueue.pop();
    }

    // 3. Display Results
    cout << "\n--- Final Results ---" << endl;
    cout << "Original Order: ";
    for (int val : originalInputs) cout << val << " ";
    
    cout << "\nReviewing Stack (LIFO): ";
    while (!historyStack.empty()) {
        cout << historyStack.top() << " ";
        historyStack.pop();
    }
    cout << endl;

    gpioTerminate();
    return 0;
}
