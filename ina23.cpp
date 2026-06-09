#include <iostream>
#include <vector>
#include <list>
#include <stack>
#include <queue>
#include <set>
#include <map>
#include <unordered_map>

using namespace std;

int main() {

    int data[] = {10, 20, 30, 20, 40};
	int n =5;

    // ===== VECTOR =====
    cout << "\n===== VECTOR =====" << endl;
    vector<int> v;

    // TODO 1: Insert all elements from data into vector
    for(int i = 0; i < n; i++) {
        v.push_back(data[i]);
    }

    // TODO 2: Print elements
    for(int x : v) {
        cout << x << " "; 
    }
    cout << endl;

    // ===== LIST =====
    cout << "\n===== LIST =====" << endl;
    list<int> l;

    // TODO 3: Insert all elements
    for(int i = 0; i < n; i++) {
        l.push_back(data[i]);
    }

    // TODO 4: Print elements
    for(int x : l) {
        cout << x << " ";
    }
    cout << endl;

    // ===== STACK =====
    cout << "\n===== STACK =====" << endl;
    stack<int> s;

    // TODO 5: Insert all elements
    for(int i = 0; i < n; i++) {
        s.push(data[i]);
    }

    // TODO 6: Print top element
    cout << "Top element: " << s.top() << endl;

    // ===== QUEUE =====
    cout << "\n===== QUEUE =====" << endl;
    queue<int> q;

    // TODO 7: Insert all elements
    for(int i = 0; i < n; i++) {
        q.push(data[i]);
    }

    // TODO 8: Print front element
    cout << "Front element: " << q.front() << endl;

    // ===== PRIORITY QUEUE =====
    cout << "\n===== PRIORITY QUEUE =====" << endl;
    priority_queue<int> pq;

    // TODO 9: Insert all elements
    for(int i = 0; i < n; i++) {
        pq.push(data[i]);
    }

    // TODO 10: Print top element
    cout << "Top element: " << pq.top() << endl;

    // ===== SET =====
    cout << "\n===== SET =====" << endl;
    set<int> st;

    // TODO 11: Insert all elements
    for(int i = 0; i < n; i++) {
        st.insert(data[i]);
    }

    // TODO 12: Print elements
    for(int x : st) {
        cout << x << " ";
    }
    cout << endl;

    // ===== MAP =====
    cout << "\n===== MAP (Frequency Count) =====" << endl;
    map<int, int> m;

    // TODO 13: Count frequency of each number
    for(int i = 0; i < n; i++) {
        m[data[i]]++;
    }

    // TODO 14: Print (key, frequency)
    for(auto p : m) {
        cout << p.first << " -> " << p.second << endl;
    }

    // ===== UNORDERED MAP =====
    cout << "\n===== UNORDERED MAP =====" << endl;
    unordered_map<int, int> um;

    // TODO 15: Count frequency again
     for(int i = 0; i < n; i++) {
        um[data[i]]++;
    }

    // TODO 16: Print values
    for(auto p : um) {
        cout << p.first << " -> " << p.second << endl;
    }

    return 0;
}