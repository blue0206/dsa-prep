/*
 * Problem: Path With Minimum Effort (LeetCode #1631)
 * Link: https://leetcode.com/problems/path-with-minimum-effort/description/
 *
 * Approach: This problem can be modeled as finding a shortest path in a graph,
 *           but with a unique definition of "path cost". The cost, or
 *           "effort", of a path is the maximum absolute difference in height
 *           between any two adjacent cells in that path. We want to find the
 *           path with the minimum such effort.
 *
 *           This is a perfect application for a variation of Dijkstra's
 *           algorithm. The grid cells are the nodes. Instead of summing edge
 *           weights, the "distance" to a cell is the minimum effort required
 *           to reach it. When moving from cell A to B, the new path effort is
 *           `max(current_effort_to_A, abs(height[B] - height[A]))`. A
 *           min-priority queue is used to always explore the path with the
 *           lowest current maximum effort.
 *
 * Time Complexity: O(M * N * log(M * N)), where M and N are the dimensions of
 *                  the grid. This is the complexity of Dijkstra's on a grid.
 * Space Complexity: O(M * N) for the distance array and the priority queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct Info {
  int d;
  int r;
  int c;
};

struct CompareInfo {
  bool operator()(const Info& a, const Info& b) { return a.d > b.d; }
};

int minimumEffortPath(const vector<vector<int>>& heights);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> heights(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> heights[i][j];
      }
    }

    cout << "Heights: [ ";
    for (auto row : heights) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Minimum Effort Path: " << minimumEffortPath(heights) << endl;
  }

  return 0;
}

int minimumEffortPath(const vector<vector<int>>& heights) {
  int n = heights.size();
  int m = heights[0].size();

  if (n == 1 && m == 1) return 0;

  const int INF = 1e9;
  vector<vector<int>> diffArr(n, vector<int>(m, INF));
  priority_queue<Info, vector<Info>, CompareInfo> minheap;
  minheap.push({0, 0, 0});

  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};
  while (!minheap.empty()) {
    auto [diff, r, c] = minheap.top();
    minheap.pop();

    if (diffArr[r][c] < diff) {
      continue;
    }

    if (r == n - 1 && c == m - 1) {
      return diff;
    }

    for (int i = 0; i < 4; i++) {
      int nr = dy[i] + r;
      int nc = dx[i] + c;

      if (nr >= 0 && nr < n && nc >= 0 && nc < m) {
        int nextDiff = abs(heights[nr][nc] - heights[r][c]);
        int maxDiff = max(diff, nextDiff);
        if (maxDiff < diffArr[nr][nc]) {
          minheap.push({maxDiff, nr, nc});
          diffArr[nr][nc] = maxDiff;
        }
      }
    }
  }

  return -1;
}
