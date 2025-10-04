/*
 * Problem: Rotting Oranges (LeetCode #994)
 * Link: https://leetcode.com/problems/rotting-oranges/description/
 *
 * Approach: This problem is a classic multi-source Breadth-First Search (BFS)
 *           problem. The goal is to find the minimum time for all fresh
 *           oranges to become rotten.
 *           1.  **Initialization:** Scan the grid to find all initially rotten
 *               oranges and add their coordinates to a queue. Also, count the
 *               total number of fresh oranges.
 *           2.  **BFS Traversal:** The BFS proceeds in layers, where each layer
 *               corresponds to one minute of time. In each iteration, we
 *               process all oranges currently in the queue.
 *           3.  **Spreading Rot:** For each rotten orange, explore its four
 *               adjacent cells. If a neighbor is a fresh orange, mark it as
 *               rotten, decrement the fresh orange count, and add it to the
 *               queue for the next minute's processing.
 *           4.  **Result:** After the BFS, if the fresh orange count is zero,
 *               the total time is the number of minutes (layers) passed. If
 *               any fresh oranges remain, they are unreachable, so we return
 * -1.
 *
 * Time Complexity: O(N * M), where N and M are the dimensions of the grid.
 * Space Complexity: O(N * M) in the worst case for the queue.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int orangesRotting(vector<vector<int>>& grid);
bool checkValid(const vector<vector<int>>& grid, int r, int c);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<int>> grid(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
      }
    }

    cout << "Input Grid: [ ";
    for (auto rows : grid) {
      cout << "[ ";
      for (int val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Time to rot all oranges: " << orangesRotting(grid) << endl;
  }

  return 0;
}

int orangesRotting(vector<vector<int>>& grid) {
  int n = grid.size();
  int m = grid[0].size();

  int freshCount = 0;
  queue<pii> q;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == 1) freshCount++;
      if (grid[i][j] == 2) {
        q.push({i, j});
      }
    }
  }

  int time = 0;
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};
  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      auto [r, c] = q.front();
      q.pop();

      for (int j = 0; j < 4; j++) {
        int nextCol = c + dx[j];
        int nextRow = r + dy[j];

        if (checkValid(grid, nextRow, nextCol)) {
          freshCount--;
          grid[nextRow][nextCol] = 2;
          q.push({nextRow, nextCol});
        }
      }
    }

    if (!q.empty()) time++;
  }

  if (freshCount > 0) return -1;
  return time;
}

bool checkValid(const vector<vector<int>>& grid, int r, int c) {
  if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() ||
      grid[r][c] != 1) {
    return false;
  }

  return true;
}
