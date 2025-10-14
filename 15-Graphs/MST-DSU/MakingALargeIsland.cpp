/*
 * Problem: Making A Large Island (LeetCode #827)
 * Link: https://leetcode.com/problems/making-a-large-island/description/
 *
 * Approach: This problem can be solved efficiently using a Disjoint Set Union
 *           (DSU) data structure. The solution involves two main steps:
 *           1.  **Build Initial Islands:** First, iterate through the grid. For
 *               each cell containing a '1', treat it as a node in the DSU.
 *               Connect adjacent '1' cells by performing a `union` operation.
 *               This process groups all existing land cells into disjoint sets,
 *               where each set represents an island and its size is tracked by
 *               the DSU.
 *           2.  **Check Potential Merges:** Iterate through the grid again.
 *               This time, for each cell containing a '0', simulate changing it
 *               to a '1'. The potential new island size is 1 (for the '0'
 *               itself) plus the sizes of all unique neighboring islands.
 *               Use a `set` to keep track of the parent IDs of neighboring
 *               islands to avoid double-counting. The maximum size found during
 *               this process is the answer.
 *
 * Time Complexity: O(N*N), as we iterate through the grid twice.
 * Space Complexity: O(N*N) for the DSU data structure.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class DisjointSet {
 private:
  vector<int> size, parent;

 public:
  DisjointSet(int n) {
    size.assign(n, 1);
    parent.assign(n, 0);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i) return i;

    parent[i] = find(parent[i]);
    return parent[i];
  }

  void unionBySize(int i, int j) {
    int pi = find(i);
    int pj = find(j);

    if (pi == pj) return;

    if (size[pi] >= size[pj]) {
      size[pi] += size[pj];
      parent[pj] = pi;
    } else {
      size[pj] += size[pi];
      parent[pi] = pj;
    }
  }

  int getSize(int i) { return size[i]; }
};

int largestIsland(vector<vector<int>>& grid);

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

    cout << "Grid: [";
    for (auto row : grid) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Largest Island: " << largestIsland(grid) << endl;

    cout << endl;
  }

  return 0;
}

int largestIsland(vector<vector<int>>& grid) {
  int n = grid.size();

  DisjointSet dsu(n * n);

  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  bool noZeroes = true;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j]) {
        for (int k = 0; k < 4; k++) {
          int ni = i + dy[k];
          int nj = j + dx[k];

          if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj]) {
            int cell = i * n + j;
            int nextCell = ni * n + nj;

            dsu.unionBySize(cell, nextCell);
          }
        }
      } else {
        noZeroes = false;
      }
    }
  }

  if (noZeroes) return n * n;

  int maxSize = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      if (grid[i][j] == 0) {
        int size = 1;
        unordered_set<int> visitedParent;
        for (int k = 0; k < 4; k++) {
          int ni = i + dy[k];
          int nj = j + dx[k];

          if (ni >= 0 && ni < n && nj >= 0 && nj < n && grid[ni][nj]) {
            int cell = i * n + j;
            int nextCell = ni * n + nj;
            int parent = dsu.find(nextCell);

            if (!visitedParent.count(parent)) {
              size += dsu.getSize(parent);
              visitedParent.insert(parent);
            }
          }
        }

        if (size > maxSize) {
          maxSize = size;
        }
      }
    }
  }

  return maxSize;
}
