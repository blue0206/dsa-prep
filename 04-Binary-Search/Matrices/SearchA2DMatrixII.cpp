/*
 * Problem: Search a 2D Matrix II (LeetCode #240)
 * Link: https://leetcode.com/problems/search-a-2d-matrix-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach iterates through each row of the matrix. For each
 *           row, it checks if the target could possibly exist in that row by
 *           comparing it with the first and last elements. If it's possible,
 *           a standard binary search is performed on that row.
 *
 * Time Complexity: O(M * log(N)), where M is the number of rows and N is the
 *                  number of columns.
 * Space Complexity: O(1)
 */
bool bsOnRow(vector<vector<int>>& matrix, int target);
bool bs(vector<int>& nums, int target);

/**
 * Approach: This optimal approach starts the search from the top-right corner
 *           of the matrix. The properties of the matrix (rows and columns are
 *           sorted) allow us to eliminate either a row or a column in each
 *           step.
 *           - If the current element is equal to the target, we've found it.
 *           - If the current element is less than the target, the target
 *             cannot be in the current row (since all elements to the left
 *             are smaller), so we move down to the next row.
 *           - If the current element is greater than the target, the target
 *             cannot be in the current column (since all elements below are
 *             larger), so we move left to the previous column.
 *
 * Time Complexity: O(M + N)
 * Space Complexity: O(1)
 */
bool optimalApproach(vector<vector<int>>& matrix, int target);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m, target;
    cin >> n >> m >> target;
    vector<vector<int>> matrix(n, vector<int>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> matrix[i][j];
      }
    }

    cout << "Search Result (Row-wise Search Approach): "
         << (bsOnRow(matrix, target) ? "True" : "False") << endl;

    cout << "Search Result (Optimal Approach): "
         << (optimalApproach(matrix, target) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

//-------------------------ROW-WISE SEARCH APPROACH-----------------------------
bool bsOnRow(vector<vector<int>>& matrix, int target) {
  int m = matrix.size();
  int n = matrix[0].size();

  for (int i = 0; i < m; i++) {
    if (target >= matrix[i][0] && target <= matrix[i][n - 1]) {
      if (bs(matrix[i], target)) {
        return true;
      }
    }
  }

  return false;
}

bool bs(vector<int>& nums, int target) {
  int low = 0;
  int high = nums.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (nums[mid] == target) {
      return true;
    } else if (nums[mid] > target) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return false;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
bool optimalApproach(vector<vector<int>>& matrix, int target) {
  int row = 0;
  int col = matrix[0].size() - 1;

  while (row < matrix.size() && col >= 0) {
    if (matrix[row][col] == target) {
      return true;
    } else if (matrix[row][col] < target) {
      row++;
    } else {
      col--;
    }
  }

  return false;
}
