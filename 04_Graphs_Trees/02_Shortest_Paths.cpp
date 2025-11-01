/*
 * ZCO PREPARATION - GRAPHS: Shortest Path Algorithms
 * 
 * Algorithms to find shortest paths in graphs
 * Essential for pathfinding problems
 */

#include <iostream>
#include <vector>
#include <queue>
#include <climits>
#include <algorithm>
using namespace std;

#define INF INT_MAX

// Edge structure for weighted graphs
struct Edge {
    int to, weight;
    Edge(int t, int w) : to(t), weight(w) {}
};

// Graph representation using adjacency list
class WeightedGraph {
    int V;
    vector<vector<Edge>> adj;
    
public:
    WeightedGraph(int V) : V(V), adj(V) {}
    
    void addEdge(int u, int v, int w) {
        adj[u].push_back(Edge(v, w));
        // For undirected: adj[v].push_back(Edge(u, w));
    }
    
    vector<vector<Edge>> getAdj() { return adj; }
    int getV() { return V; }
};

// ===== 1. DIJKSTRA'S ALGORITHM =====
// Single source shortest path for non-negative weights
// Time: O((V + E) log V) with priority queue

vector<int> dijkstra(WeightedGraph &g, int src) {
    int V = g.getV();
    vector<int> dist(V, INF);
    vector<bool> visited(V, false);
    
    // Min heap: {distance, vertex}
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[src] = 0;
    pq.push({0, src});
    
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if(visited[u]) continue;
        visited[u] = true;
        
        for(Edge &e : g.getAdj()[u]) {
            int v = e.to;
            int weight = e.weight;
            
            if(!visited[v] && dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    
    return dist;
}

// ===== 2. BELLMAN-FORD ALGORITHM =====
// Single source shortest path, works with negative weights
// Can detect negative cycles
// Time: O(V * E)

vector<int> bellmanFord(WeightedGraph &g, int src) {
    int V = g.getV();
    vector<int> dist(V, INF);
    dist[src] = 0;
    
    // Relax all edges V-1 times
    for(int i = 0; i < V - 1; i++) {
        for(int u = 0; u < V; u++) {
            if(dist[u] != INF) {
                for(Edge &e : g.getAdj()[u]) {
                    int v = e.to;
                    int weight = e.weight;
                    if(dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }
    }
    
    // Check for negative cycles
    for(int u = 0; u < V; u++) {
        if(dist[u] != INF) {
            for(Edge &e : g.getAdj()[u]) {
                int v = e.to;
                int weight = e.weight;
                if(dist[u] + weight < dist[v]) {
                    // Negative cycle detected
                    cout << "Negative cycle detected!" << endl;
                    return vector<int>();  // Return empty
                }
            }
        }
    }
    
    return dist;
}

// ===== 3. FLOYD-WARSHALL ALGORITHM =====
// All pairs shortest paths
// Time: O(V^3), Space: O(V^2)

vector<vector<int>> floydWarshall(vector<vector<int>> &graph) {
    int V = graph.size();
    vector<vector<int>> dist = graph;
    
    // Initialize: dist[i][j] = graph[i][j] if edge exists, else INF
    for(int i = 0; i < V; i++) {
        for(int j = 0; j < V; j++) {
            if(i == j) dist[i][j] = 0;
            else if(graph[i][j] == 0) dist[i][j] = INF;
        }
    }
    
    // Update distances using all vertices as intermediate
    for(int k = 0; k < V; k++) {
        for(int i = 0; i < V; i++) {
            for(int j = 0; j < V; j++) {
                if(dist[i][k] != INF && dist[k][j] != INF) {
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
                }
            }
        }
    }
    
    // Check for negative cycles
    for(int i = 0; i < V; i++) {
        if(dist[i][i] < 0) {
            cout << "Negative cycle detected!" << endl;
        }
    }
    
    return dist;
}

// ===== 4. SHORTEST PATH IN UNWEIGHTED GRAPH =====
// Use BFS - already covered in Graph_Basics.cpp
// This is just a reminder that BFS finds shortest path in unweighted graphs

// ===== 5. MULTI-SOURCE SHORTEST PATHS =====
// Multiple sources using BFS

vector<int> multiSourceBFS(vector<vector<int>> &graph, vector<int> &sources) {
    int V = graph.size();
    vector<int> dist(V, INF);
    queue<int> q;
    
    // Add all sources to queue with distance 0
    for(int src : sources) {
        dist[src] = 0;
        q.push(src);
    }
    
    while(!q.empty()) {
        int u = q.front();
        q.pop();
        
        for(int v : graph[u]) {
            if(dist[v] == INF) {
                dist[v] = dist[u] + 1;
                q.push(v);
            }
        }
    }
    
    return dist;
}

// ===== 6. SHORTEST PATH WITH AT MOST K EDGES =====
// Using Dynamic Programming

vector<int> shortestPathKEdges(WeightedGraph &g, int src, int k) {
    int V = g.getV();
    // dp[i][v] = shortest distance from src to v using at most i edges
    vector<vector<int>> dp(k + 1, vector<int>(V, INF));
    
    dp[0][src] = 0;
    
    for(int i = 1; i <= k; i++) {
        for(int u = 0; u < V; u++) {
            if(dp[i - 1][u] != INF) {
                for(Edge &e : g.getAdj()[u]) {
                    int v = e.to;
                    dp[i][v] = min(dp[i][v], dp[i - 1][u] + e.weight);
                }
            }
        }
    }
    
    return dp[k];
}

// ===== 7. RESTORING PATH =====
// Reconstruct the actual shortest path

vector<int> dijkstraWithPath(WeightedGraph &g, int src, int dest) {
    int V = g.getV();
    vector<int> dist(V, INF);
    vector<int> parent(V, -1);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    
    dist[src] = 0;
    pq.push({0, src});
    
    while(!pq.empty()) {
        int u = pq.top().second;
        pq.pop();
        
        if(u == dest) break;
        
        for(Edge &e : g.getAdj()[u]) {
            int v = e.to;
            if(dist[u] + e.weight < dist[v]) {
                dist[v] = dist[u] + e.weight;
                parent[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    
    // Reconstruct path
    vector<int> path;
    if(dist[dest] == INF) return path;  // No path
    
    int curr = dest;
    while(curr != -1) {
        path.push_back(curr);
        curr = parent[curr];
    }
    reverse(path.begin(), path.end());
    
    return path;
}

// ===== 8. 0-1 BFS =====
// For graphs with edge weights 0 or 1
// More efficient than Dijkstra

vector<int> zeroOneBFS(vector<vector<pair<int, int>>> &graph, int src) {
    int V = graph.size();
    vector<int> dist(V, INF);
    deque<int> dq;
    
    dist[src] = 0;
    dq.push_back(src);
    
    while(!dq.empty()) {
        int u = dq.front();
        dq.pop_front();
        
        for(auto &edge : graph[u]) {
            int v = edge.first;
            int weight = edge.second;
            
            if(dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                
                if(weight == 0) {
                    dq.push_front(v);  // Weight 0: add to front
                } else {
                    dq.push_back(v);   // Weight 1: add to back
                }
            }
        }
    }
    
    return dist;
}

// ===== MAIN FUNCTION =====
int main() {
    WeightedGraph g(5);
    
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 1);
    g.addEdge(2, 1, 2);
    g.addEdge(2, 3, 5);
    g.addEdge(1, 3, 1);
    g.addEdge(3, 4, 3);
    
    cout << "Dijkstra from vertex 0:" << endl;
    vector<int> dist = dijkstra(g, 0);
    for(int i = 0; i < dist.size(); i++) {
        if(dist[i] == INF) {
            cout << "Vertex " << i << ": INF" << endl;
        } else {
            cout << "Vertex " << i << ": " << dist[i] << endl;
        }
    }
    
    cout << "\nPath from 0 to 4:" << endl;
    vector<int> path = dijkstraWithPath(g, 0, 4);
    for(int v : path) {
        cout << v << " ";
    }
    cout << endl;
    
    return 0;
}

