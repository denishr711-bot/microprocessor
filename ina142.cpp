#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>

using namespace std;

class Graph {
private:
    // Adjacency list with edge weights
    unordered_map<string, vector<pair<string, int>>> adj;

    // Vertex values
    unordered_map<string, int> vertexValue;

public:

    // NEW: Count total vertices
    int count_vertices() {
        return adj.size();
    }

    // NEW: Count total edges
    int count_edges() {
        int total = 0;
        for (const auto& v : adj) {
            total += v.second.size();
        }
        return total;
    }

    // NEW: Compute the degree of a vertex (Out-degree + In-degree for directed graph)
    int degree(const string& x) {
        if (adj.find(x) == adj.end()) {
            return 0; // Vertex doesn't exist
        }

        // Out-degree: Number of edges leaving x
        int out_degree = adj[x].size();

        // In-degree: Number of edges entering x from other vertices
        int in_degree = 0;
        for (const auto& v : adj) {
            if (v.first == x) continue; // Avoid double-counting self-loops if handled above
            for (const auto& edge : v.second) {
                if (edge.first == x) {
                    in_degree++;
                }
            }
        }

        return out_degree + in_degree;
    }

    // add_vertex(G, x)
    void add_vertex(string x) {
        if (adj.find(x) == adj.end()) {
            adj[x] = {};
            cout << "Vertex " << x << " added.\n";
        }
        else {
            cout << "Vertex already exists.\n";
        }
    }

    // remove_vertex(G, x)
    void remove_vertex(string x) {
        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        // Remove edges pointing to x
        for (auto &v : adj) {
            auto &neighbors = v.second;

            for (auto it = neighbors.begin(); it != neighbors.end(); ) {
                if (it->first == x)
                    it = neighbors.erase(it);
                else
                    ++it;
            }
        }

        // Remove the vertex
        adj.erase(x);
        vertexValue.erase(x);

        cout << "Vertex " << x << " removed.\n";
    }

    // add_edge(G, x, y, z)
    void add_edge(string x, string y, int z) {

        if (adj.find(x) == adj.end())
            add_vertex(x);

        if (adj.find(y) == adj.end())
            add_vertex(y);

        // Check if edge already exists
        for (auto edge : adj[x]) {
            if (edge.first == y) {
                cout << "Edge already exists.\n";
                return;
            }
        }

        adj[x].push_back({y, z});

        cout << "Edge added from "
             << x << " to " << y
             << " with value " << z << ".\n";
    }

    // remove_edge(G, x, y)
    void remove_edge(string x, string y) {

        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        auto &neighbors = adj[x];

        for (auto it = neighbors.begin(); it != neighbors.end(); ++it) {
            if (it->first == y) {
                neighbors.erase(it);

                cout << "Edge removed.\n";
                return;
            }
        }

        cout << "Edge not found.\n";
    }

    // adjacent(G, x, y)
    bool adjacent(string x, string y) {

        if (adj.find(x) == adj.end())
            return false;

        for (auto edge : adj[x]) {
            if (edge.first == y)
                return true;
        }

        return false;
    }

    // neighbors(G, x)
    void neighbors(string x) {

        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        cout << "Neighbors of " << x << ": ";

        for (auto edge : adj[x]) {
            cout << edge.first << " ";
        }

        cout << endl;
    }

    // set_vertex_value(G, x, v)
    void set_vertex_value(string x, int v) {

        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        vertexValue[x] = v;
    }

    // get_vertex_value(G, x)
    int get_vertex_value(string x) {

        if (vertexValue.find(x) == vertexValue.end()) {
            cout << "No value assigned.\n";
            return -1;
        }

        return vertexValue[x];
    }

    // set_edge_value(G, x, y, v)
    void set_edge_value(string x, string y, int v) {

        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        for (auto &edge : adj[x]) {
            if (edge.first == y) {
                edge.second = v;

                cout << "Edge value updated.\n";
                return;
            }
        }

        cout << "Edge not found.\n";
    }

    // get_edge_value(G, x, y)
    int get_edge_value(string x, string y) {

        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return -1;
        }

        for (auto edge : adj[x]) {
            if (edge.first == y)
                return edge.second;
        }

        cout << "Edge not found.\n";

        return -1;
    }

    // Display graph
    void display() {

        cout << "\nGraph:\n";

        for (auto v : adj) {

            cout << v.first << " -> ";

            for (auto edge : v.second) {
                cout << "("
                     << edge.first
                     << ", "
                     << edge.second
                     << ") ";
            }

            cout << endl;
        }
    }
};

int main() {

    Graph G;

    // Add vertices
    G.add_vertex("A");
    G.add_vertex("B");
    G.add_vertex("C");

    // Add edges
    G.add_edge("A", "B", 5);
    G.add_edge("A", "C", 10);
    G.add_edge("B", "C", 3);

    // Display graph
    G.display();

    // --- PRINTING NEW FUNCTIONS (INITIAL GRAPH STATS) ---
    cout << "\n--- New Function Outputs (Initial) ---" << endl;
    cout << "Total Vertices: " << G.count_vertices() << endl;
    cout << "Total Edges: " << G.count_edges() << endl;
    cout << "Degree of Vertex A: " << G.degree("A") << endl;
    cout << "Degree of Vertex B: " << G.degree("B") << endl;
    cout << "--------------------------------------" << endl;

    // Adjacent
    cout << "\nIs A adjacent to B? ";

    if (G.adjacent("A", "B"))
        cout << "Yes\n";
    else
        cout << "No\n";

    // Neighbors
    G.neighbors("A");

    // Vertex values
    G.set_vertex_value("A", 100);

    cout << "\nVertex value of A = "
         << G.get_vertex_value("A")
         << endl;

    // Edge values
    cout << "Edge value A->B = "
         << G.get_edge_value("A", "B")
         << endl;

    G.set_edge_value("A", "B", 20);

    cout << "Updated edge value A->B = "
         << G.get_edge_value("A", "B")
         << endl;

    // Remove edge
    G.remove_edge("A", "C");

    // Remove vertex
    G.remove_vertex("B");

    // Final graph
    G.display();

    // --- PRINTING NEW FUNCTIONS (FINAL GRAPH STATS) ---
    cout << "\n--- New Function Outputs (Final) ---" << endl;
    cout << "Total Vertices: " << G.count_vertices() << endl;
    cout << "Total Edges: " << G.count_edges() << endl;
    cout << "Degree of Vertex A: " << G.degree("A") << endl;
    cout << "------------------------------------" << endl;

    return 0;
}

