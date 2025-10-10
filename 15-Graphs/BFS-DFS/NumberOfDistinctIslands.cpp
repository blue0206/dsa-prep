/*
 * Problem: Number of Distinct Islands
 * Link: https://www.geeksforgeeks.org/problems/number-of-distinct-islands/1
 *
 * Approach: To count distinct islands, we need a way to represent the shape of
 *           each island in a canonical form, regardless of its position on
 *           the grid.
 *           1.  Iterate through the grid. When an unvisited land cell ('1') is
 *               found, it marks the start of a new island.
 *           2.  Begin a Depth-First Search (DFS) from this starting cell,
 *               which we'll call the "base" cell `(baseRow, baseCol)`.
 *           3.  During the DFS, for each land cell `(row, col)` that is part
 *               of the island, calculate its coordinates relative to the base
 *               cell: `(row - baseRow, col - baseCol)`.
 *           4.  Store these relative coordinate pairs in a vector. This vector
 *               represents the unique shape of the island.
 *           5.  Insert this shape vector into a `set` to automatically handle
 *               uniqueness. The final size of the set is the number of
 *               distinct islands.
 *
 * Time Complexity: O(N * M * log(N * M)). The log factor comes from inserting
 *                  a vector (representing an island) into the set.
 * Space Complexity: O(N * M) for the set and recursion stack.
 */
#include <algorithm>
#include <iostream>
#include <queue>
#include <set>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int countDistinctIslands(vector<vector<int>>& grid);
void dfs(vector<vector<int>>& grid, vector<pii>& island, int baseRow,
         int baseCol, int row, int col);
pii calculate(int x1, int y1, int x2, int y2);

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

    cout << "Grid: [ ";
    for (auto rows : grid) {
      cout << "[ ";
      for (int val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Number of Distinct Islands: " << countDistinctIslands(grid)
         << endl;
  }

  return 0;
}

int countDistinctIslands(vector<vector<int>>& grid) {
  set<vector<pii>> islandSet;

  for (int i = 0; i < grid.size(); i++) {
    for (int j = 0; j < grid[i].size(); j++) {
      if (grid[i][j]) {
        vector<pii> island;
        dfs(grid, island, i, j, i, j);
        islandSet.insert(island);
      }
    }
  }

  return islandSet.size();
}

void dfs(vector<vector<int>>& grid, vector<pii>& island, int baseRow,
         int baseCol, int row, int col) {
  if (row < 0 || row >= grid.size() || col < 0 || col >= grid[0].size() ||
      grid[row][col] == 0) {
    return;
  }

  island.emplace_back(calculate(baseRow, baseCol, row, col));
  grid[row][col] = 0;

  dfs(grid, island, baseRow, baseCol, row + 1, col);
  dfs(grid, island, baseRow, baseCol, row - 1, col);
  dfs(grid, island, baseRow, baseCol, row, col + 1);
  dfs(grid, island, baseRow, baseCol, row, col - 1);
}

pii calculate(int x1, int y1, int x2, int y2) { return {x2 - x1, y2 - y1}; }
