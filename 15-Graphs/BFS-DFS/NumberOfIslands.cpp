/*
 * Problem: Number of Islands (LeetCode #200)
 * Link: https://leetcode.com/problems/number-of-islands/description/
 *
 * Approach: This problem is solved by treating the grid as a graph and finding
 *           the number of connected components of '1's (land).
 *           1.  Iterate through each cell of the grid.
 *           2.  If a cell contains '1' (land), it signifies the start of a new,
 *               unvisited island. Increment the island count.
 *           3.  Initiate a Depth-First Search (DFS) from this cell. The DFS
 *               recursively explores all adjacent land cells (up, down, left,
 *               right) and "sinks" them by changing their value from '1' to
 *               '0'. This ensures that each island is counted only once.
 *
 * Time Complexity: O(N * M), where N and M are the grid dimensions.
 * Space Complexity: O(N * M) in the worst case for the recursion stack (e.g.,
 *                   a snake-like island).
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numIslands(vector<vector<char>>& grid);
void dfs(vector<vector<char>>& grid, int row, int col);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> grid(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> grid[i][j];
      }
    }

    cout << "Input Grid: [ ";
    for (auto rows : grid) {
      cout << "[ ";
      for (char val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Number of Islands: " << numIslands(grid) << endl;
  }

  return 0;
}

int numIslands(vector<vector<char>>& grid) {
  int n = grid.size();
  int m = grid[0].size();

  int count = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (grid[i][j] == '1') {
        dfs(grid, i, j);
        count++;
      }
    }
  }

  return count;
}

void dfs(vector<vector<char>>& grid, int row, int col) {
  if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() ||
      grid[row][col] == '0') {
    return;
  }

  grid[row][col] = '0';

  dfs(grid, row + 1, col);
  dfs(grid, row - 1, col);
  dfs(grid, row, col + 1);
  dfs(grid, row, col - 1);
}
