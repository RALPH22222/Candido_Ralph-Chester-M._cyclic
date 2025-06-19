#include <iostream>
#include <vector>
#include <stack>
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

bool isCyclicDFS(const vector<vector<int>>& adjMatrix, vector<bool>& visited, vector<int>& parent, int start, vector<int>& cycleVertices) {
    stack<int> s;
    s.push(start);
    visited[start] = true;
    
    while (!s.empty()) {
        int u = s.top();
        s.pop();
        
        for (int v = 0; v < adjMatrix.size(); ++v) {
            if (adjMatrix[u][v]) {
                if (!visited[v]) {
                    visited[v] = true;
                    parent[v] = u;
                    s.push(v);
                } else if (parent[u] != v) {
                    int current = u;
                    cycleVertices.push_back(v);
                    cycleVertices.push_back(current);
                    while (parent[current] != -1 && parent[current] != v) {
                        current = parent[current];
                        cycleVertices.push_back(current);
                    }
                    return true;
                }
            }
        }
    }
    return false;
}

void detectCycleDFS(const vector<vector<int>>& adjMatrix) {
    int n = adjMatrix.size();
    vector<bool> visited(n, false);
    vector<int> parent(n, -1);
    vector<int> cycleVertices;
    
    printMatrix(adjMatrix);
    
    for (int i = 0; i < n; ++i) {
        if (!visited[i]) {
            if (isCyclicDFS(adjMatrix, visited, parent, i, cycleVertices)) {
                cout << "\n\033[1;32mCycle detected!\033[0m Path: ";
                for (int j = cycleVertices.size() - 1; j >= 0; --j) {
                    cout << cycleVertices[j];
                    if (j != 0) cout << " -> ";
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
    cout << "\n\033[1;36mGraph Cycle Detection using DFS\033[0m\n";
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
        detectCycleDFS(adjMatrix);
    }
    
    cout << "\nProgram completed. Goodbye!\n";
    return 0;
}