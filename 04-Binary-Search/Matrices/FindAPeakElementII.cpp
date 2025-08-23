/*
 * Problem: Find a Peak Element II (LeetCode #1901)
 * Link: https://leetcode.com/problems/find-a-peak-element-ii/description/
 *
 * Approach: This problem can be solved efficiently by applying binary search on
 *           the columns of the matrix. The key idea is to reduce the 2D
 *           problem to a 1D-like problem in each step.
 *           1.  **Binary Search on Columns:** We initialize `low` and `high`
 *               pointers for the column indices `[0, n-1]`.
 *           2.  **Find Max in Middle Column:** In each iteration, we consider
 *               the middle column `mid`. We find the row index (`maxR`) of the
 *               maximum element in this column.
 *           3.  **Check Neighbors:** The element `mat[maxR][mid]` is a
 *               potential peak. It's already greater than its top and bottom
 *               neighbors (by virtue of being the max in its column). We only
 *               need to check its left and right neighbors.
 *           4.  **Eliminate Half:** If `mat[maxR][mid]` is a peak, we return
 *               it. Otherwise, if its left neighbor is larger, a peak must
 *               exist in the left half of the columns, so we move `high`. If
 *               the right is larger, we move `low`.
 *
 * Time Complexity: O(M * logN)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> findPeakGrid(vector<vector<int>>& mat);

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

    cout << "Matrix: [ ";
    for (int i = 0; i < m; i++) {
      cout << "[ ";
      for (int j = 0; j < n; j++) {
        cout << mat[i][j] << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    vector<int> result = findPeakGrid(mat);
    cout << "Peak Element: [" << result[0] << ", " << result[1] << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> findPeakGrid(vector<vector<int>>& mat) {
  int low = 0;
  int n = mat[0].size();
  int high = n - 1;

  while (low <= high) {
    int midCol = low + (high - low) / 2;

    // Find the row with the maximum element in the middle column.
    int maxR = 0;
    for (int i = 0; i < mat.size(); i++) {
      if (mat[i][midCol] > mat[maxR][midCol]) {
        maxR = i;
      }
    }

    // Check if this element is a peak by comparing with left and right.
    // It's already greater than top/bottom neighbors by definition.
    int left = (midCol > 0) ? mat[maxR][midCol - 1] : -1;
    int right = (midCol < n - 1) ? mat[maxR][midCol + 1] : -1;

    if (mat[maxR][midCol] > left && mat[maxR][midCol] > right) {
      return {maxR, midCol};
    } else if (left > mat[maxR][midCol]) {
      // If left is greater, a peak must exist on the left side.
      high = midCol - 1;
    } else {
      // Otherwise, a peak must exist on the right side.
      low = midCol + 1;
    }
  }

  return {-1, -1};
}
