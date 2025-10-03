/*
 * Problem: Number of Provinces (LeetCode #547)
 * Link: https://leetcode.com/problems/number-of-provinces/description/
 *
 * Approach: This problem is equivalent to finding the number of connected
 *           components in a graph. The solution uses a Depth-First Search
 *           (DFS) traversal to solve this.
 *           1.  Iterate through each city (node) from 0 to N-1.
 *           2.  Use a `visited` array to keep track of which cities have
 *               already been assigned to a province.
 *           3.  If a city `i` has not been visited, it means we've found a new
 *               province. Increment the province count and start a DFS from
 *               `i`.
 *           4.  The DFS recursively explores all connected cities, marking them
 *               as visited.
 *
 * Time Complexity: O(N^2), where N is the number of cities.
 * Space Complexity: O(N) for the visited array and recursion stack.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

int findCircleNum(vector<vector<int>>& isConnected);
void dfs(int node, vector<vector<int>>& isConnected, vector<int>& visited);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> isConnected(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> isConnected[i][j];
      }
    }

    cout << "Input Adjacency Matrix: [ ";
    for (auto rows : isConnected) {
      cout << "[ ";
      for (int val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Total Number of Provinces: " << findCircleNum(isConnected) << endl;
  }

  return 0;
}

int findCircleNum(vector<vector<int>>& isConnected) {
  int n = isConnected.size();

  vector<int> visited(n, 0);
  int count = 0;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      dfs(i, isConnected, visited);
      count++;
    }
  }

  return count;
}

void dfs(int node, vector<vector<int>>& isConnected, vector<int>& visited) {
  visited[node] = 1;
  for (int i = 0; i < isConnected.size(); i++) {
    if (isConnected[node][i] && !visited[i]) {
      dfs(i, isConnected, visited);
    }
  }
}
