/*
 * Problem: Topological Sort
 * Link: https://www.geeksforgeeks.org/problems/topological-sort/1
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

/**
 * Approach: This solution uses Depth-First Search (DFS). The core idea is
 *           that for a directed edge u -> v, vertex u must come before vertex
 *           v in the topological ordering. A post-order traversal ensures this.
 *           1.  Perform a DFS from an unvisited node.
 *           2.  After visiting all descendants of a node (i.e., after the
 *               recursive calls for its neighbors have returned), push the
 *               node onto a stack.
 *           3.  After the DFS is complete for all components, the contents of
 *               the stack, when popped, will give a valid topological sort.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the visited array, stack, and recursion depth.
 */
vector<int> dfsApproach(int V, const vector<vector<int>>& adj);
void dfs(const vector<vector<int>>& adj, vector<int>& visited, stack<int>& st,
         int node);

/**
 * Approach: This solution uses Breadth-First Search (BFS) and is also known
 *           as Kahn's algorithm.
 *           1.  Calculate the in-degree (number of incoming edges) for every
 *               vertex.
 *           2.  Initialize a queue with all vertices that have an in-degree of
 *               0.
 *           3.  While the queue is not empty, dequeue a vertex, add it to the
 *               result, and for each of its neighbors, decrement their
 *               in-degree.
 *           4.  If a neighbor's in-degree becomes 0, enqueue it.
 *
 * Time Complexity: O(V + E)
 * Space Complexity: O(V) for the in-degree array and queue.
 */
vector<int> bfsApproach(int V, const vector<vector<int>>& adj);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int v;
    cin >> v;  // Number of vertices

    int e;
    cin >> e;  // Number of edges

    vector<vector<int>> adj(v);
    for (int i = 0; i < e; i++) {
      int u, v_node;
      cin >> u >> v_node;
      adj[u].emplace_back(v_node);
    }

    cout << "Edges: [";
    for (int i = 0; i < adj.size(); ++i) {
      cout << i << " -> ";
      cout << "[ ";
      for (int neighbor : adj[i]) {
        cout << neighbor << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    // Uncomment the approach to use.
    vector<int> ans = bfsApproach(v, adj);
    // vector<int> ans = dfsApproach(v, adj);

    cout << "Topological Sort: [ ";
    for (int val : ans) {
      cout << val << " ";
    }
    cout << "]" << endl;
  }

  return 0;
}

//------------------------------DFS APPROACH------------------------------------
vector<int> dfsApproach(int V, const vector<vector<int>>& adj) {
  stack<int> st;
  vector<int> visited(V, 0);
  for (int i = 0; i < V; i++) {
    if (!visited[i]) {
      dfs(adj, visited, st, i);
    }
  }

  vector<int> ans;
  while (!st.empty()) {
    ans.emplace_back(st.top());
    st.pop();
  }

  return ans;
}

void dfs(const vector<vector<int>>& adj, vector<int>& visited, stack<int>& st,
         int node) {
  visited[node] = 1;

  for (int next : adj[node]) {
    if (!visited[next]) {
      dfs(adj, visited, st, next);
    }
  }

  st.push(node);
}

//------------------------------BFS APPROACH------------------------------------
vector<int> bfsApproach(int V, const vector<vector<int>>& adj) {
  vector<int> inCount(V, 0);
  for (int i = 0; i < V; i++) {
    for (int node : adj[i]) {
      inCount[node]++;
    }
  }

  queue<int> q;
  for (int i = 0; i < V; i++) {
    if (inCount[i] == 0) q.push(i);
  }

  vector<int> ans;
  while (!q.empty()) {
    int node = q.front();
    q.pop();

    ans.emplace_back(node);
    for (int next : adj[node]) {
      inCount[next]--;
      if (inCount[next] == 0) {
        q.push(next);
      }
    }
  }

  return ans;
}
