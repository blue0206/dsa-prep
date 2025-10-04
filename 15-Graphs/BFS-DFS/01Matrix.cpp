/*
 * Problem: 01 Matrix (LeetCode #542)
 * Link: https://leetcode.com/problems/01-matrix/description/
 *
 * Approach: This solution uses a multi-source Breadth-First Search (BFS) to
 *           efficiently find the shortest distance from each cell to the
 *           nearest 0.
 *
 *           1.  **Initialization:**
 *               -   An `ans` matrix is created to store the final distances.
 *               -   A queue is initialized by adding the coordinates of all
 *                   cells that initially contain a `0`. These cells act as the
 *                   simultaneous starting points for the search.
 *
 *           2.  **Multi-Source BFS:**
 *               -   The BFS proceeds in layers, where each layer represents an
 *                   increasing distance from the source `0`s.
 *               -   For each cell processed from the queue, its four neighbors
 *                   are checked. If a neighbor is a `1` that hasn't been
 *                   visited, its distance is recorded, it's marked as visited
 *                   (by changing its value in the input matrix), and it's
 *                   added to the queue for the next layer.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(M * N)
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

vector<vector<int>> updateMatrix(vector<vector<int>>& mat);
bool isValid(vector<vector<int>>& mat, int r, int c);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> mat(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cin >> mat[i][j];
      }
    }

    cout << "Input Matrix: [ ";
    for (auto rows : mat) {
      cout << "[ ";
      for (int val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    vector<vector<int>> ans = updateMatrix(mat);

    cout << "Updated Matrix: [ ";
    for (auto rows : ans) {
      cout << "[ ";
      for (int val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<vector<int>> updateMatrix(vector<vector<int>>& mat) {
  int m = mat.size();
  int n = mat[0].size();
  vector<vector<int>> ans(m, vector<int>(n));
  queue<pii> q;

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      ans[i][j] = mat[i][j];
      if (mat[i][j] == 0) {
        q.push({i, j});
      }
    }
  }

  int dy[4] = {1, -1, 0, 0};
  int dx[4] = {0, 0, 1, -1};
  int distance = 1;
  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      auto [r, c] = q.front();
      q.pop();

      for (int j = 0; j < 4; j++) {
        int nextRow = r + dy[j];
        int nextCol = c + dx[j];

        if (isValid(mat, nextRow, nextCol)) {
          ans[nextRow][nextCol] = distance;
          mat[nextRow][nextCol] = 0;
          q.push({nextRow, nextCol});
        }
      }
    }

    distance++;
  }

  return ans;
}

bool isValid(vector<vector<int>>& mat, int r, int c) {
  if (r < 0 || r >= mat.size() || c < 0 || c >= mat[0].size() ||
      mat[r][c] != 1) {
    return false;
  }
  return true;
}
