/*
 * Problem: Shortest Path in Binary Matrix (LeetCode #1091)
 * Link:
 * https://leetcode.com/problems/shortest-path-in-binary-matrix/description/
 *
 * Approach:
 * This problem asks for the shortest path in a grid, which is a perfect use
 * case for Breadth-First Search (BFS). The grid can be seen as an unweighted
 * graph where each valid cell (value 0) is a node.
 *
 * 1.  Start a BFS from the top-left cell (0, 0).
 * 2.  The BFS explores the grid layer by layer, where each layer corresponds
 *     to an increase in path length.
 * 3.  We explore in all 8 directions (including diagonals).
 * 4.  To avoid cycles and redundant work, we mark visited cells by modifying
 *     the grid in-place (changing 0 to 1).
 * 5.  The path length is returned as soon as the bottom-right cell is reached.
 *
 * Time Complexity: O(N*N), where N is the dimension of the grid.
 * Space Complexity: O(N*N) in the worst case for the queue.
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int shortestPathBinaryMatrix(vector<vector<int>>& grid);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> grid(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> grid[i][j];
      }
    }

    cout << "Grid: [ ";
    for (auto row : grid) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Shortest Path: " << shortestPathBinaryMatrix(grid) << endl;
  }

  return 0;
}

int shortestPathBinaryMatrix(vector<vector<int>>& grid) {
  if (grid[0][0] == 1) return -1;
  int n = grid.size();

  queue<pii> q;
  q.push({0, 0});
  grid[0][0] = 1;

  int distance = 1;
  int dx[8] = {0, 0, 1, -1, -1, 1, -1, 1};
  int dy[8] = {1, -1, 0, 0, 1, -1, -1, 1};
  while (!q.empty()) {
    int size = q.size();

    for (int i = 0; i < size; i++) {
      auto [r, c] = q.front();
      q.pop();

      if (r == n - 1 && c == n - 1) {
        return distance;
      }

      for (int j = 0; j < 8; j++) {
        int nextR = r + dy[j];
        int nextC = c + dx[j];

        if (nextR >= 0 && nextR < n && nextC >= 0 && nextC < n &&
            grid[nextR][nextC] == 0) {
          grid[nextR][nextC] = 1;
          q.push({nextR, nextC});
        }
      }
    }
    distance++;
  }

  return -1;
}
