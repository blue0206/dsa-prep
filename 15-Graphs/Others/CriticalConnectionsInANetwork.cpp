/*
 * Problem: Critical Connections in a Network (LeetCode #1192)
 * Link:
 * https://leetcode.com/problems/critical-connections-in-a-network/description/
 *
 * Approach: This problem is about finding all "bridges" in a graph. A bridge
 *           is an edge whose removal increases the number of connected
 *           components. This can be solved efficiently using Tarjan's
 *           bridge-finding algorithm, which is based on a single DFS traversal.
 *           1.  We maintain two arrays for each node: `times[]` (discovery time
 *               during DFS) and `low[]` (the lowest discovery time reachable
 *               from the node, including through back-edges).
 *           2.  Start a DFS from an arbitrary node. For each node `u`, set its
 *               `times[u]` and `low[u]` to the current discovery time.
 *           3.  For each neighbor `v` of `u`:
 *               - If `v` is the parent, ignore it.
 *               - If `v` is unvisited, recursively call DFS on `v`. After the
 *                 call returns, update `low[u] = min(low[u], low[v])`. If
 *                 `times[u] < low[v]`, it means `v` cannot reach `u` or any of
 *                 `u`'s ancestors, so the edge `u-v` is a bridge.
 *               - If `v` is visited, it's a back-edge. Update `low[u]` with
 *                 `low[u] = min(low[u], times[v])`.
 *
 * Time Complexity: O(V + E), as it's a single DFS traversal.
 * Space Complexity: O(V + E) for the adjacency list and recursion stack.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

vector<vector<int>> criticalConnections(int n,
                                        vector<vector<int>>& connections);
void dfs(vector<vector<int>>& ans, const vector<vector<int>>& adj,
         vector<int>& visited, vector<int>& times, vector<int>& low, int parent,
         int& timer, int node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, e;
    cin >> n >> e;

    vector<vector<int>> edges(e, vector<int>(2));
    for (int i = 0; i < e; i++) {
      cin >> edges[i][0] >> edges[i][1];
    }

    cout << "n: " << n << endl;
    cout << "Node-1\tNode-2:" << endl;
    for (auto edge : edges) {
      cout << edge[0] << "\t" << edge[1] << endl;
    }
    cout << endl;

    vector<vector<int>> bridge = criticalConnections(n, edges);

    cout << "Critical Connections:" << endl;
    cout << "Node-1\tNode-2:" << endl;
    for (auto edge : bridge) {
      cout << edge[0] << "\t" << edge[1] << endl;
    }

    cout << endl;
  }

  return 0;
}

vector<vector<int>> criticalConnections(int n,
                                        vector<vector<int>>& connections) {
  vector<vector<int>> adj(n);
  for (int i = 0; i < connections.size(); i++) {
    adj[connections[i][0]].emplace_back(connections[i][1]);
    adj[connections[i][1]].emplace_back(connections[i][0]);
  }

  vector<int> times(n), low(n), visited(n, 0);
  vector<vector<int>> ans;
  int timer = 0;

  // The graph is connected, so a single DFS from node 0 is sufficient.
  dfs(ans, adj, visited, times, low, -1, timer, 0);
  return ans;
}

void dfs(vector<vector<int>>& ans, const vector<vector<int>>& adj,
         vector<int>& visited, vector<int>& times, vector<int>& low, int parent,
         int& timer, int node) {
  visited[node] = 1;
  times[node] = timer;
  low[node] = timer;
  timer++;

  for (int next : adj[node]) {
    if (next == parent) continue;

    if (!visited[next]) {
      dfs(ans, adj, visited, times, low, node, timer, next);
      low[node] = min(low[node], low[next]);
      if (times[node] < low[next]) {
        ans.push_back({node, next});
      }
    }

    low[node] = min(low[node], low[next]);
  }
}
