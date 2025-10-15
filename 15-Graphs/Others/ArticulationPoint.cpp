/*
 * Problem: Articulation Point
 * Link: https://www.geeksforgeeks.org/problems/articulation-point-1/1
 *
 * Approach: This problem is about finding all "articulation points" (or cut
 *           vertices) in a graph. An articulation point is a vertex whose
 *           removal increases the number of connected components. This can be
 *           solved efficiently using a single DFS traversal, similar to
 *           Tarjan's bridge-finding algorithm.
 *           1.  We maintain two arrays for each node: `times[]` (discovery time
 *               during DFS) and `low[]` (the lowest discovery time reachable
 *               from the node, including through back-edges).
 *           2.  During the DFS, for a node `u` and its child `v` in the DFS
 *               tree:
 *               - `u` is an articulation point if `low[v] >= times[u]`. This
 *                 means `v` cannot reach any ancestor of `u`, so `u` is the
 *                 only connection for the subtree rooted at `v` to the rest of
 *                 the graph.
 *           3.  A special case is the root of the DFS tree. It is an
 *               articulation point if and only if it has more than one child
 *               in the DFS tree.
 *
 * Time Complexity: O(V + E), as it's a single DFS traversal.
 * Space Complexity: O(V + E) for the adjacency list and recursion stack.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

vector<int> articulationPoints(int V, vector<vector<int>>& adj);
void dfs(unordered_map<int, int>& mp, vector<vector<int>>& adj,
         vector<int>& times, vector<int>& low, vector<int>& visited, int parent,
         int& timer, int node);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> adj(n);
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;

      for (int j = 0; j < m; j++) {
        int val;
        cin >> val;

        adj[i].emplace_back(val);
      }
    }

    vector<int> ans = articulationPoints(n, adj);

    cout << "Articulation Points:" << endl;
    for (int i = 0; i < ans.size(); i++) {
      cout << ans[i] << " ";
    }
    cout << endl;

    cout << endl;
  }

  return 0;
}

vector<int> articulationPoints(int V, vector<vector<int>>& adj) {
  vector<int> times(V), low(V), visited(V, 0);
  unordered_map<int, int> mp;
  int timer = 0;

  dfs(mp, adj, times, low, visited, -1, timer, 0);
  vector<int> ans;
  for (int i = 0; i < V; i++) {
    if (mp.count(i)) {
      ans.emplace_back(i);
    }
  }

  if (ans.empty()) return {-1};
  return ans;
}

void dfs(unordered_map<int, int>& mp, vector<vector<int>>& adj,
         vector<int>& times, vector<int>& low, vector<int>& visited, int parent,
         int& timer, int node) {
  visited[node] = 1;
  times[node] = timer;
  low[node] = timer;
  timer++;

  int child = 0;
  for (int next : adj[node]) {
    if (next == parent) continue;

    if (!visited[next]) {
      dfs(mp, adj, times, low, visited, node, timer, next);

      if (times[node] <= low[next] && parent != -1) {
        mp[node] = 1;
      }
      low[node] = min(low[node], low[next]);

      child++;
    } else {
      low[node] = min(low[node], times[next]);
    }
  }

  if (parent == -1 && child > 1) {
    mp[node] = 1;
  }
}
