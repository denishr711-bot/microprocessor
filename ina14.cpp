#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <algorithm> // Needed for std::remove_if

using namespace std;

class Graph {
private:
    // Adjacency list with edge weights
    unordered_map<string, vector<pair<string, int>>> adj;

    // Vertex values
    unordered_map<string, int> vertexValue;

public:

    // add_vertex(G, x)
    void add_vertex(const string& x) {
        if (adj.find(x) == adj.end()) {
            adj[x] = {};
            cout << "Vertex " << x << " added.\n";
        }
        else {
            cout << "Vertex already exists.\n";
        }
    }

    // remove_vertex(G, x)
    void remove_vertex(const string& x) {
        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        // Remove incoming edges pointing to x from all other vertices
        for (auto &v : adj) {
            auto &neighbors = v.second;
            neighbors.erase(
                remove_if(neighbors.begin(), neighbors.end(), 
                          [&x](const pair<string, int>& edge) { return edge.first == x; }),
                neighbors.end()
            );
        }

        // Remove the vertex itself and its assigned data
        adj.erase(x);
        vertexValue.erase(x);

        cout << "Vertex " << x << " removed.\n";
    }

    // add_edge(G, x, y, z)
    void add_edge(const string& x, const string& y, int z) {
        if (adj.find(x) == adj.end())
            add_vertex(x);

        if (adj.find(y) == adj.end())
            add_vertex(y);

        // Check if edge already exists using const reference to prevent deep copying
        const auto& neighbors = adj[x];
        for (const auto& edge : neighbors) {
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
    void remove_edge(const string& x, const string& y) {
        auto it = adj.find(x);
        if (it == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        auto &neighbors = it->second;
        for (auto vec_it = neighbors.begin(); vec_it != neighbors.end(); ++vec_it) {
            if (vec_it->first == y) {
                neighbors.erase(vec_it);
                cout << "Edge removed.\n";
                return;
            }
        }

        cout << "Edge not found.\n";
    }

    // adjacent(G, x, y)
    bool adjacent(const string& x, const string& y) const {
        auto it = adj.find(x);
        if (it == adj.end())
            return false;

        for (const auto& edge : it->second) {
            if (edge.first == y)
                return true;
        }

        return false;
    }

    // neighbors(G, x)
    void neighbors(const string& x) const {
        auto it = adj.find(x);
        if (it == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        cout << "Neighbors of " << x << ": ";
        for (const auto& edge : it->second) {
            cout << edge.first << " ";
        }
        cout << endl;
    }

    // set_vertex_value(G, x, v)
    void set_vertex_value(const string& x, int v) {
        if (adj.find(x) == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }
        vertexValue[x] = v;
    }

    // get_vertex_value(G, x)
    int get_vertex_value(const string& x) const {
        auto it = vertexValue.find(x);
        if (it == vertexValue.end()) {
            cout << "No value assigned.\n";
            return -1;
        }
        return it->second;
    }

    // set_edge_value(G, x, y, v)
    void set_edge_value(const string& x, const string& y, int v) {
        auto it = adj.find(x);
        if (it == adj.end()) {
            cout << "Vertex not found.\n";
            return;
        }

        for (auto &edge : it->second) {
            if (edge.first == y) {
                edge.second = v;
                cout << "Edge value updated.\n";
                return;
            }
        }

        cout << "Edge not found.\n";
    }

    // get_edge_value(G, x, y)
    int get_edge_value(const string& x, const string& y) const {
        auto it = adj.find(x);
        if (it == adj.end()) {
            cout << "Vertex not found.\n";
            return -1;
        }

        for (const auto& edge : it->second) {
            if (edge.first == y)
                return edge.second;
        }

        cout << "Edge not found.\n";
        return -1;
    }

    // Display graph
    void display() const {
        cout << "\nGraph:\n";
        for (const auto& v : adj) {
            cout << v.first << " -> ";
            for (const auto& edge : v.second) {
                cout << "(" << edge.first << ", " << edge.second << ") ";
            }
            cout << endl;
        }
    }

    //function to count total vertices
    int count_vertices() const {
        return adj.size();
    }

    //function to count total edges
    int count_edges() const {
        int total_edges = 0;
        for (const auto& v : adj) {
            total_edges += v.second.size();
        }
        return total_edges;
    }

    //function to compute the degree of a vertex (in-degree + out-degree)
    int degree(const string& x) const {
        auto it = adj.find(x);
        if (it == adj.end()) {
            cout << "Vertex not found.\n";
            return -1;
        }

        // Out-degree is the size of the vertex's adjacency vector
        int out_degree = it->second.size();

        // In-degree requires checking how many other vertices reference x
        int in_degree = 0;
        for (const auto& v : adj) {
            for (const auto& edge : v.second) {
                if (edge.first == x) {
                    in_degree++;
                }
            }
        }

        return out_degree + in_degree;
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

    // Display initial graph metrics
    G.display();
	
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
    
    cout << "\nTotal vertices in graph: " << G.count_vertices() << "\n";
    cout << "Total edges in graph: " << G.count_edges() << "\n";
    cout << "\nTotal Degree of vertex A: " << G.degree("A") << " (2 out, 0 in)\n";
    cout << "Total Degree of vertex B: " << G.degree("B") << " (1 out, 1 in)\n";
    cout << "Total Degree of vertex C: " << G.degree("C") << " (0 out, 2 in)\n";

    // Remove edge
    G.remove_edge("A", "C");

    // Remove vertex
    G.remove_vertex("B");

    // Final state checking
    G.display();
    cout << "\nUpdated total vertices: " << G.count_vertices() << "\n";
    cout << "Updated total edges: " << G.count_edges() << "\n";

    return 0;
}
