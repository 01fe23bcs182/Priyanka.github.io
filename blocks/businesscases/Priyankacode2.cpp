#include <iostream>
#include <queue>
#include <vector>
using namespace std;

#define INF 1000000  // Representing no direct connection

// Warshall's Algorithm for finding the transitive closure
void warshallAlgorithm(int** graph, int n) {
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (graph[i][k] != INF && graph[k][j] != INF) {
                    graph[i][j] = min(graph[i][j], graph[i][k] + graph[k][j]);
                }
            }
        }
    }
}

// BFS for exploring economic connections (e.g., job availability)
void bfs(int** graph, int n, int start) {
    vector<bool> visited(n, false);
    queue<int> q;
    visited[start] = true;
    q.push(start);

    cout << "BFS Traversal (Job Availability from Region " << start << "): ";
    while (!q.empty()) {
        int region = q.front();
        q.pop();
        cout << region << " ";

        for (int i = 0; i < n; i++) {
            if (!visited[i] && graph[region][i] != INF) {
                visited[i] = true;
                q.push(i);
            }
        }
    }
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of regions: ";
    cin >> n;

    // Dynamically allocate the graph
    int** graph = new int*[n];
    for (int i = 0; i < n; i++) {
        graph[i] = new int[n];
    }

    cout << "Enter the adjacency matrix (use " << INF << " for no direct connection):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    // Apply Warshall's Algorithm
    warshallAlgorithm(graph, n);

    cout << "\nTransitive Closure (Economic Connections Matrix):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (graph[i][j] == INF) cout << "INF ";
            else cout << graph[i][j] << " ";
        }
        cout << endl;
    }

    // BFS Traversal from a specific region
    int startRegion;
    cout << "Enter the starting region for BFS: ";
    cin >> startRegion;
    bfs(graph, n, startRegion);

    // Free dynamically allocated memory
    for (int i = 0; i < n; i++) {
        delete[] graph[i];
    }
    delete[] graph;

    return 0;
}

