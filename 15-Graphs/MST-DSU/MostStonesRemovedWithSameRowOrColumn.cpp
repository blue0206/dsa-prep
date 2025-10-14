/*
 * Problem: Most Stones Removed with Same Row or Column (LeetCode #947)
 * Link:
 * https://leetcode.com/problems/most-stones-removed-with-same-row-or-column/description/
 *
 * Approach:
 * This problem can be modeled as finding connected components in a graph. Two
 * stones are in the same component if they share a row or a column. For any
 * component of size `k > 1`, we can remove `k-1` stones. Therefore, the
 * total number of stones that can be removed is `TotalStones -
 * NumberOfComponents`.
 *
 * This solution uses a Disjoint Set Union (DSU) to find the components. The
 * graph's nodes are the rows and columns themselves. A stone at `(r, c)` acts
 * as an edge connecting the node for row `r` and the node for column `c`.
 * To distinguish between row and column indices, we map columns to a shifted
 * range of indices (e.g., `col + maxRow + 1`).
 * After uniting all components based on the stone locations, we count the
 * number of resulting disjoint sets. This count equals the number of stone
 * components.
 *
 * Time Complexity: O(N + maxRow + maxCol), where N is the number of stones.
 * Space Complexity: O(maxRow + maxCol) for the DSU data structure.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
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

  int getComponentsCount() {
    int count = 0;
    for (int i = 0; i < parent.size(); i++) {
      if (find(i) == i && size[i] > 1) count++;
    }

    return count;
  }
};

int removeStones(vector<vector<int>>& stones);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> stones(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
      cin >> stones[i][0] >> stones[i][1];
    }

    cout << "Stones Location: [";
    for (auto stone : stones) {
      cout << " [ " << stone[0] << ", " << stone[1] << " ]";
    }
    cout << " ]" << endl;

    cout << "Stones Removed: " << removeStones(stones) << endl;

    cout << endl;
  }

  return 0;
}

int removeStones(vector<vector<int>>& stones) {
  int n = stones.size();

  int maxRow = 0;
  int maxCol = 0;
  for (int i = 0; i < n; i++) {
    maxRow = max(maxRow, stones[i][0]);
    maxCol = max(maxCol, stones[i][1]);
  }

  DisjointSet dsu(maxRow + maxCol + 2);
  for (int i = 0; i < n; i++) {
    int r = stones[i][0];
    int c = stones[i][1];

    dsu.unionBySize(r, c + maxRow + 1);
  }

  int components = dsu.getComponentsCount();
  return n - components;
}
