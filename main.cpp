#include <iostream>
#include <vector>
#include <climits>
using namespace std;

int V;
vector<vector<int>> graph;
vector<vector<int>> allColors; 
int minColors = INT_MAX;


bool isSafe(int v, vector<int> &color, int c) {
    for (int i = 0; i < V; i++) {
        if (graph[v][i] && color[i] == c)
            return false;
    }
    return true;
}


void graphColoring(int v, vector<int> &color, int m) {
    if (v == V) { 
        allColors.push_back(color);

        int usedColors = 0;
        vector<bool> used(m + 1, false);
        for (int c : color)
            used[c] = true;
        for (bool u : used)
            if (u) usedColors++;

        minColors = min(minColors, usedColors);
        return;
    }

    for (int c = 1; c <= m; c++) {
        if (isSafe(v, color, c)) {
            color[v] = c;
            graphColoring(v + 1, color, m);
            color[v] = 0;
        }
    }
}

void graphColoring(int m) {
    vector<int> color(V, 0);
    graphColoring(0, color, m);
}

int main() {
    int E;
    cout << "Enter number of vertices: ";
    cin >> V;
    cout << "Enter number of edges: ";
    cin >> E;

    graph.assign(V, vector<int>(V, 0));

    cout << "Enter edges (u v) between 0 to " << V - 1 << ":\n";
    for (int i = 0; i < E; i++) {
        int u, v;
        cin >> u >> v;
        graph[u][v] = graph[v][u] = 1;
    }

    int maxColors;
    cout << "Enter the maximum number of colors to try: ";
    cin >> maxColors;

    graphColoring(maxColors);

    if (allColors.empty()) {
        cout << "\nNo valid colorings possible with " << maxColors << " colors.\n";
    } else {
        cout << "\nAll possible valid colorings:\n";
        for (auto &c : allColors) {
            for (int col : c)
                cout << col << " ";
            cout << endl;
        }
        cout << "\nMinimum number of colors required: " << minColors << endl;
    }

    return 0;
}
