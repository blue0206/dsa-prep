/*
 * Problem: Swim in Rising Water (LeetCode #778)
 * Link: https://leetcode.com/problems/swim-in-rising-water/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <queue>
#include <vector>

using namespace std;

struct Info {
  int level;
  int r;
  int c;
};

struct CompareInfo {
  bool operator()(const Info& a, const Info& b) { return a.level > b.level; }
};

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
};

/**
 * Approach: This solution is analogous to Kruskal's algorithm for finding a
 *           Minimum Spanning Tree. We want to find a path from (0,0) to
 *           (n-1, n-1) such that the maximum elevation on the path is
 * minimized.
 *           1.  Treat each cell as a node and store them all in a list with
 * their elevations.
 *           2.  Sort this list by elevation in ascending order. This is like
 *               sorting edges by weight.
 *           3.  Iterate through the sorted cells. For each cell, consider the
 *               water level to have risen to its elevation.
 *           4.  Union the current cell with any adjacent cells that have a
 * lower or equal elevation (i.e., they are already "underwater").
 *           5.  After each union, check if the start cell (0) and end cell
 *               (n*n - 1) are connected. The first time they are, the current
 *               cell's elevation is the minimum required time to swim across.
 *
 * Time Complexity: O(N^2 log N), dominated by sorting the N*N cells.
 * Space Complexity: O(N^2) for the DSU structure and the sorted list of cells.
 */
int dsuApproach(vector<vector<int>>& grid);

/**
 * Approach: This problem can be modeled as finding a shortest path where the
 *           "cost" of a path is the maximum elevation encountered. This is a
 *           variation of Dijkstra's algorithm, similar to finding a path with
 *           minimum effort.
 *           1.  Use a min-priority queue to store `{effort, row, col}`.
 * `effort` is the max elevation seen on the path to `(row, col)`.
 *           2.  Start at `(0,0)`. The initial effort is `grid[0][0]`.
 *           3.  When moving from cell A to B, the new path effort is
 *               `max(effort_to_A, elevation_of_B)`.
 *           4.  The algorithm always explores the path with the minimum current
 *               maximum effort. The first time the destination is reached, we
 *               have found the optimal path.
 *
 * Time Complexity: O(N^2 log N), the complexity of Dijkstra's on an N*N grid.
 * Space Complexity: O(N^2) for the distance/levels array and priority queue.
 */
int dijkstraApproach(vector<vector<int>>& grid);

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

    cout << "Minimum Time (DSU): " << dsuApproach(grid) << endl;
    cout << "Minimum Time (Dijkstra): " << dijkstraApproach(grid) << endl;

    cout << endl;
  }

  return 0;
}

bool checkValid(int n, int r, int c) {
  return (r >= 0 && r < n && c >= 0 && c < n);
}

int dsuApproach(vector<vector<int>>& grid) {
  int n = grid.size();

  vector<Info> levels;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < n; j++) {
      levels.push_back({grid[i][j], i, j});
    }
  }
  sort(levels.begin(), levels.end(),
       [](Info& a, Info& b) { return a.level < b.level; });

  DisjointSet dsu(n * n);
  int dx[4] = {1, -1, 0, 0};
  int dy[4] = {0, 0, 1, -1};
  for (int i = 0; i < levels.size(); i++) {
    auto [level, r, c] = levels[i];

    for (int j = 0; j < 4; j++) {
      int nr = r + dy[j];
      int nc = c + dx[j];

      if (checkValid(n, nr, nc) && grid[nr][nc] <= level) {
        int cell = r * n + c;
        int nextCell = nr * n + nc;

        dsu.unionBySize(cell, nextCell);
      }
    }

    if (dsu.find(0) == dsu.find(n * n - 1)) return level;
  }

  return -1;
}

int dijkstraApproach(vector<vector<int>>& grid) {
  const int n = grid.size();
  const int INF = 1e9;

  vector<vector<int>> levels(n, vector<int>(n, INF));

  priority_queue<Info, vector<Info>, CompareInfo> minheap;
  minheap.push({grid[0][0], 0, 0});
  levels[0][0] = grid[0][0];

  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  while (!minheap.empty()) {
    auto [level, r, c] = minheap.top();
    minheap.pop();

    if (levels[r][c] < level) continue;
    if (r == n - 1 && c == n - 1) {
      return level;
    }

    for (int i = 0; i < 4; i++) {
      int nr = r + dy[i];
      int nc = c + dx[i];

      if (checkValid(n, nr, nc)) {
        int currentLevel = levels[nr][nc];
        int newLevel = max(level, grid[nr][nc]);

        if (newLevel < currentLevel) {
          levels[nr][nc] = newLevel;
          minheap.push({newLevel, nr, nc});
        }
      }
    }
  }

  return -1;
}
