#include <iostream>
#include <vector>
#include <queue>
#include <stack>
#include <chrono>

using namespace std;

struct Node {
    int val;
    Node* next;
    Node(int v) : val(v), next(NULL) {}
};

int main() {
    vector<int> data;
    vector<int> prefix;
    queue<int> q;
    stack<int> st;
    Node* head = NULL;
    string cmd;

    auto start = chrono::high_resolution_clock::now();

    while (cin >> cmd) {
        if (cmd == "ADD") {
            int x;
            cin >> x;
            
            // Part 1.3: Efficient storage (push_back)
            data.push_back(x);
            st.push(x);

            // Part 2.2: Prefix Sum update
            if (prefix.empty()) prefix.push_back(x);
            else prefix.push_back(prefix.back() + x);

        } else if (cmd == "PRINT") {
            for (int x : data) cout << x << " ";
            cout << endl;

        } else if (cmd == "QUERY") {
            int l, r;
            cin >> l >> r;
            int result;
            if (l == 0) result = prefix[r];
            else result = prefix[r] - prefix[l - 1];
            cout << "Sum: " << result << endl;

        } else if (cmd == "PROCESS") {
            // Part 3.2: Queue processing
            for (int x : data) q.push(x);
            
            Node* temp = head;
            while (!q.empty()) {
                int val = q.front();
                cout << val << " ";
                q.pop();

                // Part 4.3: Store in Linked List
                Node* newNode = new Node(val);
                if (!head) {
                    head = newNode;
                    temp = head;
                } else {
                    temp->next = newNode;
                    temp = newNode;
                }
            }
            cout << endl;

            // Part 4.4: Fast/Slow pointers for middle
            Node* slow = head;
            Node* fast = head;
            while (fast && fast->next) {
                slow = slow->next;
                fast = fast->next->next;
            }
            if (slow) cout << "Middle: " << slow->val << endl;

        } else if (cmd == "UNDO") {
            if (st.empty()) {
                cout << "Nothing to undo" << endl;
                continue;
            }
            st.pop();
            data.pop_back();
            prefix.pop_back();
        }
    }

    auto end = chrono::high_resolution_clock::now();
    cout << "Time: " << chrono::duration_cast<chrono::milliseconds>(end - start).count() << " ms" << endl;

    return 0;
}
