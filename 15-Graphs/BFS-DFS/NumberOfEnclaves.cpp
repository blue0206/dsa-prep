/*
 * Problem: Number of Enclaves (LeetCode #1020)
 * Link: https://leetcode.com/problems/number-of-enclaves/description/
 *
 * Approach: This problem is very similar to "Surrounded Regions". The core idea
 *           is to find all land cells ('1's) that can reach the boundary of
 *           the grid. Any land cell that cannot reach the boundary is an
 *           enclave.
 *           1.  Iterate through the cells on the four borders of the grid.
 *           2.  If a land cell ('1') is found on a border, start a Depth-First
 *               Search (DFS) from that cell.
 *           3.  The DFS recursively explores all connected land cells and
 *               "sinks" them by changing their value from '1' to '0'. This
 *               effectively removes all land that is not an enclave.
 *           4.  After the boundaries have been processed, iterate through the
 *               entire grid and count the remaining '1's. This sum is the
 *               number of enclaved land cells.
 *
 * Time Complexity: O(M * N), where M and N are the grid dimensions.
 * Space Complexity: O(M * N) in the worst case for the recursion stack.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int numEnclaves(vector<vector<int>>& grid);
void dfs(vector<vector<int>>& grid, int r, int c);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
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

    cout << "Number of Enclaves: " << numEnclaves(grid) << endl;
  }

  return 0;
}

int numEnclaves(vector<vector<int>>& grid) {
  int m = grid.size();
  int n = grid[0].size();

  for (int i = 0; i < m; i++) {
    if (grid[i][0] == 1) {
      dfs(grid, i, 0);
    }
    if (grid[i][n - 1] == 1) {
      dfs(grid, i, n - 1);
    }
  }

  for (int i = 0; i < n; i++) {
    if (grid[0][i] == 1) {
      dfs(grid, 0, i);
    }
    if (grid[m - 1][i] == 1) {
      dfs(grid, m - 1, i);
    }
  }

  int count = 0;
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      count += grid[i][j];
    }
  }

  return count;
}

void dfs(vector<vector<int>>& grid, int r, int c) {
  if (r < 0 || r >= grid.size() || c < 0 || c >= grid[0].size() ||
      grid[r][c] == 0) {
    return;
  }

  grid[r][c] = 0;

  dfs(grid, r + 1, c);
  dfs(grid, r - 1, c);
  dfs(grid, r, c + 1);
  dfs(grid, r, c - 1);
}
