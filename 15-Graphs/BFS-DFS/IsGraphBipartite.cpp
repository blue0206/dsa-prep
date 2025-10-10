/*
 * Problem: Is Graph Bipartite? (LeetCode #785)
 * Link: https://leetcode.com/problems/is-graph-bipartite/description/
 *
 * Approach: A graph is bipartite if its vertices can be divided into two
 *           disjoint and independent sets, U and V, such that every edge
 *           connects a vertex in U to one in V. This can be checked by trying
 *           to "color" the graph with two colors.
 *
 *           1.  Use a `colors` array to store the color of each node.
 *               -1: uncolored, 0: color A, 1: color B.
 *           2.  Iterate through each node to handle disconnected components.
 *           3.  If a node is uncolored, start a traversal (DFS or BFS) from it,
 *               assigning it color 0.
 *           4.  During traversal, for each node, assign the opposite color to
 *               all its uncolored neighbors.
 *           5.  If we ever find a neighbor that is already colored with the
 *               *same* color as the current node, the graph is not bipartite.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the colors array and recursion/queue.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

bool isBipartite(vector<vector<int>>& graph);
bool dfs(const vector<vector<int>>& graph, vector<int>& colors, int node);
bool bfs(const vector<vector<int>>& graph, vector<int>& colors, int node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;

      for (int j = 0; j < m; j++) {
        int x;
        cin >> x;

        graph[i].emplace_back(x);
      }
    }

    cout << "Adjacency List: [";
    for (auto u : graph) {
      cout << "[ ";
      for (int v : u) {
        cout << v << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Is Bipartite: " << (isBipartite(graph) ? "True" : "False") << endl;
  }

  return 0;
}

bool isBipartite(vector<vector<int>>& graph) {
  vector<int> colors(graph.size(), -1);
  for (int i = 0; i < graph.size(); i++) {
    if (colors[i] == -1) {
      colors[i] = 0;

      // Uncomment the traversal to use.
      // if (!dfs(graph, colors, i)) {
      //   return false;
      // }
      if (!bfs(graph, colors, i)) {
        return false;
      }
    }
  }

  return true;
}

bool dfs(vector<vector<int>>& graph, vector<int>& colors, int node) {
  int currentColor = colors[node];

  for (int i : graph[node]) {
    if (colors[i] == currentColor) return false;
    if (colors[i] == -1) {
      colors[i] = (currentColor == 0) ? 1 : 0;

      if (!dfs(graph, colors, i)) {
        return false;
      }
    }
  }

  return true;
}

bool bfs(vector<vector<int>>& graph, vector<int>& colors, int node) {
  queue<int> q;
  q.push(node);

  while (!q.empty()) {
    int currentNode = q.front();
    q.pop();

    for (int i : graph[currentNode]) {
      if (colors[i] == colors[currentNode]) {
        return false;
      }
      if (colors[i] == -1) {
        colors[i] = (colors[currentNode] == 0) ? 1 : 0;
        q.push(i);
      }
    }
  }

  return true;
}
