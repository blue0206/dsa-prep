/*
 * Problem: Flood Fill (LeetCode #733)
 * Link: https://leetcode.com/problems/flood-fill/description/
 *
 * Approach: This problem is a classic graph traversal problem that can be
 *           solved with Depth-First Search (DFS).
 *           1.  Store the initial color of the starting pixel `(sr, sc)`. This
 *               is the `base` color that needs to be replaced.
 *           2.  Start a recursive DFS from the starting pixel.
 *           3.  The DFS function changes the color of the current pixel and
 *               then recursively calls itself for all four adjacent pixels
 *               (up, down, left, right).
 *           4.  The recursion has a base case to stop if the pixel is out of
 *               bounds, or if its color is not the `base` color.
 *
 * Time Complexity: O(N * M), where N and M are the grid dimensions.
 * Space Complexity: O(N * M) in the worst case for the recursion stack.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                              int color);
void dfs(vector<vector<int>>& image, int sr, int sc, int color, int base);

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

    int color, sr, sc;
    cin >> color >> sr >> sc;

    cout << "Input Grid: [ ";
    for (auto rows : grid) {
      cout << "[ ";
      for (int val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    grid = floodFill(grid, sr, sc, color);

    cout << "Modified Grid: [ ";
    for (auto rows : grid) {
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

vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc,
                              int color) {
  int baseColor = image[sr][sc];
  if (baseColor != color) {
    dfs(image, sr, sc, color, baseColor);
  }
  return image;
}

void dfs(vector<vector<int>>& image, int sr, int sc, int color, int base) {
  if (sr < 0 || sr >= image.size() || sc < 0 || sc >= image[0].size() ||
      image[sr][sc] == color || image[sr][sc] != base) {
    return;
  }

  image[sr][sc] = color;
  dfs(image, sr + 1, sc, color, base);
  dfs(image, sr - 1, sc, color, base);
  dfs(image, sr, sc + 1, color, base);
  dfs(image, sr, sc - 1, color, base);
}
