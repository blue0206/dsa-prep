/*
 * Problem: Shortest path in Directed Acyclic Graph
 * Link:
 * https://www.geeksforgeeks.org/problems/shortest-path-in-undirected-graph/1
 *
 * Approach: The single-source shortest path in a weighted Directed Acyclic
 *           Graph (DAG) can be efficiently solved in linear time. This is
 *           faster than Dijkstra's algorithm, which is needed for general
 *           graphs. The algorithm works in two phases:
 *           1.  **Topological Sort:** First, find a linear ordering of the
 *               vertices such that for every directed edge u -> v, vertex u
 *               comes before vertex v. This is done using DFS.
 *           2.  **Path Relaxation:** Initialize distances to all vertices as
 *               infinity and the source as 0. Process the vertices in the
 *               topologically sorted order. For each vertex `u`, relax its
 *               outgoing edges to `v` by updating `dist[v]` if a shorter path
 *               is found through `u`.
 *
 * Time Complexity: O(V + E) for topological sort and path relaxation.
 * Space Complexity: O(V + E) for the adjacency list and stack.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

vector<int> shortestPath(int V, int E, const vector<vector<int>>& edges);
void topologicalSort(const vector<vector<pii>>& adj, vector<int>& visited,
                     stack<int>& st, int node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int v, e;
    cin >> v >> e;

    vector<vector<int>> edges(e, vector<int>(3));

    for (int i = 0; i < e; i++) {
      cin >> edges[i][0] >> edges[i][1] >> edges[i][2];
    }

    vector<int> ans = shortestPath(v, e, edges);

    cout << "Shortest Path in Directed Acyclic Graph: " << endl;
    for (int i = 0; i < v; i++) {
      cout << "0 -> " << i << ": " << ans[i] << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<int> shortestPath(int V, int E, const vector<vector<int>>& edges) {
  vector<vector<pii>> adj(V);
  for (const auto& edge : edges) {
    adj[edge[0]].push_back({edge[1], edge[2]});
  }

  stack<int> st;
  vector<int> visited(V, 0);
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      topologicalSort(adj, visited, st, i);
    }
  }

  const int INF = 1e9;
  vector<int> distance(V, INF);
  // 0 is src.
  distance[0] = 0;

  while (!st.empty()) {
    int u = st.top();
    st.pop();

    if (distance[u] != INF) {
      for (auto [v, wt] : adj[u]) {
        distance[v] = min(distance[v], distance[u] + wt);
      }
    }
  }

  for (int i = 0; i < V; i++) {
    if (distance[i] == INF) {
      distance[i] = -1;
    }
  }

  return distance;
}

void topologicalSort(const vector<vector<pii>>& adj, vector<int>& visited,
                     stack<int>& st, int node) {
  visited[node] = 1;

  for (auto [nextNode, wt] : adj[node]) {
    if (!visited[nextNode]) {
      topologicalSort(adj, visited, st, nextNode);
    }
  }

  st.push(node);
}
