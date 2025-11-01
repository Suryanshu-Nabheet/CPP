/*
 * ZCO PREPARATION - GRAPHS: Graph Basics and Representation
 * 
 * Graph representation methods and basic operations
 * Foundation for all graph algorithms
 */

#include <iostream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
using namespace std;

// ===== GRAPH REPRESENTATION =====

// 1. Adjacency List (Most common in CP)
class Graph {
    int V;  // Number of vertices
    vector<list<int>> adj;  // Adjacency list
    
public:
    Graph(int V) : V(V), adj(V) {}
    
    // Add edge (directed)
    void addEdge(int u, int v) {
        adj[u].push_back(v);
    }
    
    // Add edge (undirected)
    void addUndirectedEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    
    // Print adjacency list
    void printGraph() {
        for(int i = 0; i < V; i++) {
            cout << i << ": ";
            for(int neighbor : adj[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
    
    // Get neighbors
    list<int> getNeighbors(int u) {
        return adj[u];
    }
};

// 2. Adjacency Matrix
class GraphMatrix {
    int V;
    vector<vector<int>> adjMatrix;
    
public:
    GraphMatrix(int V) : V(V), adjMatrix(V, vector<int>(V, 0)) {}
    
    void addEdge(int u, int v, int weight = 1) {
        adjMatrix[u][v] = weight;
        // For undirected: adjMatrix[v][u] = weight;
    }
    
    bool hasEdge(int u, int v) {
        return adjMatrix[u][v] != 0;
    }
    
    int getWeight(int u, int v) {
        return adjMatrix[u][v];
    }
};

// 3. Edge List (For certain algorithms)
struct Edge {
    int u, v, weight;
    Edge(int u, int v, int w = 1) : u(u), v(v), weight(w) {}
};

// ===== BREADTH-FIRST SEARCH (BFS) =====
// Level-order traversal, finds shortest path in unweighted graph

vector<int> BFS(Graph &g, int start) {
    int V = g.V;
    vector<bool> visited(V, false);
    vector<int> result;
    queue<int> q;
    
    visited[start] = true;
    q.push(start);
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        
        for(int v : g.getNeighbors(u)) {
            if(!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    
    return result;
}

// BFS with distance calculation (shortest path in unweighted graph)
vector<int> shortestPathBFS(Graph &g, int start) {
    int V = g.V;
    vector<int> dist(V, -1);  // -1 means unreachable
    queue<int> q;
    
    dist[start] = 0;
    q.push(start);
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        for(int v : g.getNeighbors(u)) {
            if(dist[v] == -1) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return dist;
}

// ===== DEPTH-FIRST SEARCH (DFS) =====
// Explores as far as possible before backtracking

void DFSRecursive(Graph &g, int u, vector<bool> &visited, vector<int> &result) {
    visited[u] = true;
    result.push_back(u);
    
    for(int v : g.getNeighbors(u)) {
        if(!visited[v]) {
            DFSRecursive(g, v, visited, result);
        }
    }
}

vector<int> DFS(Graph &g, int start) {
    int V = g.V;
    vector<bool> visited(V, false);
    vector<int> result;
    DFSRecursive(g, start, visited, result);
    return result;
}

// DFS Iterative (using stack)
vector<int> DFSIterative(Graph &g, int start) {
    int V = g.V;
    vector<bool> visited(V, false);
    vector<int> result;
    stack<int> st;
    
    st.push(start);
    
    while(!st.empty()) {
        int u = st.top();
        st.pop();
        
        if(!visited[u]) {
            visited[u] = true;
            result.push_back(u);
            
            // Push neighbors in reverse order for same order as recursive
            vector<int> neighbors;
            for(int v : g.getNeighbors(u)) {
                neighbors.push_back(v);
            }
            reverse(neighbors.begin(), neighbors.end());
            
            for(int v : neighbors) {
                if(!visited[v]) {
                    st.push(v);
                }
            }
        }
    }
    
    return result;
}

// ===== CONNECTED COMPONENTS =====
// Find all connected components in undirected graph

void DFSUtil(Graph &g, int u, vector<bool> &visited, vector<int> &component) {
    visited[u] = true;
    component.push_back(u);
    
    for(int v : g.getNeighbors(u)) {
        if(!visited[v]) {
            DFSUtil(g, v, visited, component);
        }
    }
}

vector<vector<int>> connectedComponents(Graph &g) {
    int V = g.V;
    vector<bool> visited(V, false);
    vector<vector<int>> components;
    
    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            vector<int> component;
            DFSUtil(g, i, visited, component);
            components.push_back(component);
        }
    }
    
    return components;
}

// ===== CYCLE DETECTION =====

// Undirected graph - using DFS
bool hasCycleUndirected(Graph &g, int u, int parent, vector<bool> &visited) {
    visited[u] = true;
    
    for(int v : g.getNeighbors(u)) {
        if(!visited[v]) {
            if(hasCycleUndirected(g, v, u, visited)) {
                return true;
            }
        } else if(v != parent) {
            return true;  // Back edge found
        }
    }
    
    return false;
}

bool hasCycle(Graph &g) {
    int V = g.V;
    vector<bool> visited(V, false);
    
    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            if(hasCycleUndirected(g, i, -1, visited)) {
                return true;
            }
        }
    }
    
    return false;
}

// Directed graph - using colors (0=white, 1=gray, 2=black)
bool hasCycleDirected(Graph &g, int u, vector<int> &color) {
    color[u] = 1;  // Gray (being processed)
    
    for(int v : g.getNeighbors(u)) {
        if(color[v] == 1) {
            return true;  // Back edge (cycle)
        }
        if(color[v] == 0 && hasCycleDirected(g, v, color)) {
            return true;
        }
    }
    
    color[u] = 2;  // Black (processed)
    return false;
}

bool hasCycleDirected(Graph &g) {
    int V = g.V;
    vector<int> color(V, 0);  // All white
    
    for(int i = 0; i < V; i++) {
        if(color[i] == 0) {
            if(hasCycleDirected(g, i, color)) {
                return true;
            }
        }
    }
    
    return false;
}

// ===== TOPOLOGICAL SORT =====
// For Directed Acyclic Graph (DAG)
// Linear ordering such that for every edge u->v, u comes before v

void topologicalSortUtil(Graph &g, int u, vector<bool> &visited, stack<int> &st) {
    visited[u] = true;
    
    for(int v : g.getNeighbors(u)) {
        if(!visited[v]) {
            topologicalSortUtil(g, v, visited, st);
        }
    }
    
    st.push(u);  // Push after processing all neighbors
}

vector<int> topologicalSort(Graph &g) {
    int V = g.V;
    vector<bool> visited(V, false);
    stack<int> st;
    
    for(int i = 0; i < V; i++) {
        if(!visited[i]) {
            topologicalSortUtil(g, i, visited, st);
        }
    }
    
    vector<int> result;
    while(!st.empty()) {
        result.push_back(st.top());
        st.pop();
    }
    
    return result;
}

// Kahn's Algorithm (BFS-based) for Topological Sort
vector<int> topologicalSortKahn(Graph &g) {
    int V = g.V;
    vector<int> inDegree(V, 0);
    
    // Calculate in-degrees
    for(int u = 0; u < V; u++) {
        for(int v : g.getNeighbors(u)) {
            inDegree[v]++;
        }
    }
    
    queue<int> q;
    for(int i = 0; i < V; i++) {
        if(inDegree[i] == 0) {
            q.push(i);
        }
    }
    
    vector<int> result;
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        result.push_back(u);
        
        for(int v : g.getNeighbors(u)) {
            inDegree[v]--;
            if(inDegree[v] == 0) {
                q.push(v);
            }
        }
    }
    
    // If result size != V, there's a cycle
    return result;
}

// ===== BIPARTITE CHECK =====
// Check if graph can be colored with 2 colors (no odd-length cycles)

bool isBipartite(Graph &g, int start, vector<int> &color) {
    queue<int> q;
    color[start] = 0;
    q.push(start);
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        for(int v : g.getNeighbors(u)) {
            if(color[v] == -1) {
                color[v] = 1 - color[u];
                q.push(v);
            } else if(color[v] == color[u]) {
                return false;  // Same color neighbors
            }
        }
    }
    
    return true;
}

bool isBipartite(Graph &g) {
    int V = g.V;
    vector<int> color(V, -1);  // -1 = uncolored
    
    for(int i = 0; i < V; i++) {
        if(color[i] == -1) {
            if(!isBipartite(g, i, color)) {
                return false;
            }
        }
    }
    
    return true;
}

// ===== MAIN FUNCTION =====
int main() {
    Graph g(5);
    
    // Add edges
    g.addUndirectedEdge(0, 1);
    g.addUndirectedEdge(0, 2);
    g.addUndirectedEdge(1, 3);
    g.addUndirectedEdge(2, 4);
    
    cout << "Graph:" << endl;
    g.printGraph();
    
    cout << "\nBFS from 0: ";
    vector<int> bfsResult = BFS(g, 0);
    for(int x : bfsResult) cout << x << " ";
    cout << endl;
    
    cout << "DFS from 0: ";
    vector<int> dfsResult = DFS(g, 0);
    for(int x : dfsResult) cout << x << " ";
    cout << endl;
    
    cout << "\nShortest distances from 0: ";
    vector<int> distances = shortestPathBFS(g, 0);
    for(int d : distances) cout << d << " ";
    cout << endl;
    
    return 0;
}

