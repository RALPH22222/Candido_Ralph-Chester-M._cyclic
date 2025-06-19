#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <iomanip>

using namespace std;

void printMatrix(const vector<vector<int>>& matrix) {
    cout << "\nAdjacency Matrix:\n";
    cout << "   ";
    for (int i = 0; i < matrix.size(); ++i) {
        cout << setw(3) << i;
    }
    cout << "\n   ";
    for (int i = 0; i < matrix.size(); ++i) {
        cout << "---";
    }
    cout << endl;
    
    for (int i = 0; i < matrix.size(); ++i) {
        cout << i << " |";
        for (int j = 0; j < matrix.size(); ++j) {
            cout << setw(3) << matrix[i][j];
        }
        cout << endl;
    }
}

bool isCyclicBFS(const vector<vector<int>>& adjMatrix, vector<bool>& visited, int start, vector<int>& cycleVertices) {
    queue<int> q;
    q.push(start);
    visited[start] = true;
    vector<int> parent(adjMatrix.size(), -1);
    
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        
        for (int v = 0; v < adjMatrix.size(); ++v) {
            if (adjMatrix[u][v]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    q.push(v);
                } else if (parent[u] != v) {
                    unordered_map<int, bool> inCycle;
                    vector<int> path1, path2;
                    int current = u;
                    while (current != -1) {
                        path1.push_back(current);
                        inCycle[current] = true;
                        current = parent[current];
                    }
                    current = v;
                    while (!inCycle[current]) {
                        path2.push_back(current);
                        current = parent[current];
                    }
                    int common = current;
                
                    for (int i = 0; i < path1.size() && path1[i] != common; ++i) {
                        cycleVertices.push_back(path1[i]);
                    }
                    cycleVertices.push_back(common);
                    for (int i = path2.size() - 1; i >= 0; --i) {
                        cycleVertices.push_back(path2[i]);
                    }
                    cycleVertices.push_back(u);
                    
                    return true;
                }
            }
        }
    }
    return false;
}

void detectCycleBFS(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> cycleVertices;
    
    printMatrix(adjMatrix);
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (isCyclicBFS(adjMatrix, visited, i, cycleVertices)) {
                cout << "\n\033[1;32mCycle detected!\033[0m Path: ";
                for (int j = 0; j < cycleVertices.size(); ++j) {
                    cout << cycleVertices[j];
                    if (j != cycleVertices.size() - 1) cout << " -> ";
                }
                cout << endl << endl;
                return;
            }
        }
    }
    cout << "\n\033[1;31mNo cycles found\033[0m in the graph.\n\n";
}

void inputMatrix(vector<vector<int>>& adjMatrix, int n) {
    cout << "\nEnter connections for each vertex (0 or 1):\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (i == j) {
                adjMatrix[i][j] = 0; 
                continue;
            }
            cout << "Is there an edge between " << i << " and " << j << "? (0/1): ";
            cin >> adjMatrix[i][j];
        }
    }
}

int main() {
    cout << "\n\033[1;36mGraph Cycle Detection using BFS\033[0m\n";
    cout << "=================================\n";
    
    int numGraphs;
    cout << "\nEnter the number of graphs to test: ";
    cin >> numGraphs;
    
    for (int g = 0; g < numGraphs; ++g) {
        cout << "\n\033[1;33mGraph " << g + 1 << "\033[0m\n";
        cout << "------------\n";
        
        int n;
        cout << "Enter the number of vertices: ";
        cin >> n;
        
        vector<vector<int>> adjMatrix(n, vector<int>(n, 0));
        inputMatrix(adjMatrix, n);
        detectCycleBFS(adjMatrix);
    }
    
    cout << "\nProgram completed. Goodbye!\n";
    return 0;
}