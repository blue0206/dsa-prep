/*
 * Problem: Set Matrix Zeroes (LeetCode #73)
 * Link: https://leetcode.com/problems/set-matrix-zeroes/description/
 */

#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

/**
 * Approach: Store all affected rows and columns in an unordered_set for rows
 *           and for columns.
 *           Then simply, iterate through each element and see if its row
 *           or column is in set, and set as 0 if true.
 *
 * Time Complexity: O(M*N)
 * Space Complexity: O(M+N)
 */
void bruteForceApproach(vector<vector<int>>& matrix);

/**
 * Approach: This O(1) space solution uses the matrix's first row and first
 *           column as in-place markers (or "parity" trackers) to avoid using
 *           extra memory.
 *
 *           The core idea is to use a dedicated variable, `colParity`, as the
 *           marker for the first column. This resolves the ambiguity of the
 *           `matrix[0][0]` cell, which is then used as the marker for the
 *           first row.
 *
 *           The algorithm proceeds in three stages:
 *           1.  **Marking:** Iterate through the matrix. If a zero is found at
 *               `matrix[row][col]`, mark the corresponding header of its row
 *               (`matrix[row][0] = 0`) and column (`matrix[0][col] = 0`). The
 *               `colParity` variable is used for marking the first column.
 *           2.  **Zeroing Inner Matrix:** Iterate through the matrix again,
 *               skipping the first row and column. For each cell, if its row
 *               marker (`matrix[row][0]`) or column marker (`matrix[0][col]`)
 *               is zero, set the cell to zero.
 *           3.  **Zeroing First Row/Column:** Finally, use the initial markers
 *               (`matrix[0][0]` for the first row and `colParity` for the
 *               first column) to zero out the first row and/or column if they
 *               were marked in the first stage.
 *
 * Time Complexity: O(M*N)
 * Space Complexity: O(1)
 */
void optimalApproach(vector<vector<int>>& matrix);
void mark(vector<vector<int>>& matrix, int row, int col, int& colParity);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;
    vector<vector<int>> matrix(m, vector<int>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cin >> matrix[i][j];
      }
    }

    cout << "Matrix: [ ";
    for (int i = 0; i < matrix.size(); i++) {
      cout << "[ ";
      for (int j = 0; j < matrix[i].size(); j++) {
        cout << matrix[i][j] << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    vector<vector<int>> bruteForceApproachArr = matrix;
    vector<vector<int>> optimalApproachArr = matrix;

    bruteForceApproach(bruteForceApproachArr);
    cout << "Brute-Force Approach: [ ";
    for (int i = 0; i < bruteForceApproachArr.size(); i++) {
      cout << "[ ";
      for (int j = 0; j < bruteForceApproachArr[i].size(); j++) {
        cout << bruteForceApproachArr[i][j] << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    optimalApproach(optimalApproachArr);
    cout << "Optimal Approach: [ ";
    for (int i = 0; i < optimalApproachArr.size(); i++) {
      cout << "[ ";
      for (int j = 0; j < optimalApproachArr[i].size(); j++) {
        cout << optimalApproachArr[i][j] << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

//---------------------------Brute Force Approach-------------------------------
void bruteForceApproach(vector<vector<int>>& matrix) {
  // Store the affected rows and cols in unordered_set.
  unordered_set<int> rows;
  unordered_set<int> cols;
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = 0; j < matrix[i].size(); j++) {
      if (matrix[i][j] == 0) {
        rows.insert(i);
        cols.insert(j);
      }
    }
  }

  // Iterate through all rows and if a row is present
  // in set, set all of its values to 0.
  for (int i = 0; i < matrix.size(); i++) {
    if (rows.find(i) != rows.end()) {
      for (int j = 0; j < matrix[i].size(); j++) {
        matrix[i][j] = 0;
      }
    }
  }

  // Iterate through all cols and if a col is present
  // in set, set all of its values to 0.
  for (int j = 0; j < matrix[0].size(); j++) {
    if (cols.find(j) != cols.end()) {
      for (int i = 0; i < matrix.size(); i++) {
        matrix[i][j] = 0;
      }
    }
  }
}

//-----------------------------Optimal Approach---------------------------------
void mark(vector<vector<int>>& matrix, int row, int col, int& colParity) {
  // We set parity to 0. This is because in the iteration for marking parity
  // we never check the party row and col before the current index again.
  // Therefore, it is ONLY safe to set it as 0 and not something like -1
  // because constraints showcase that an element can be ANY positive/negative
  // number. Since 0 is the only number we are manipulating, hence we can be
  // sure that it has been set by us and not came as input when performing
  // further processing.

  // Set row parity.
  matrix[row][0] = 0;
  // Set col parity.
  if (col == 0) {
    colParity = 0;
  } else {
    matrix[0][col] = 0;
  }
}
void optimalApproach(vector<vector<int>>& matrix) {
  // We need a parity index to mark if a row/col has 0.
  // This is easy to do with extra space. Since we need
  // to do this in O(1), we will use row-0 and col-0 as
  // parity index for rows and cols. Since matrix(0,0)
  // is a parity index for both, rows and cols, we set
  // matrix(0,0) as parity index for rows and create a
  // separate variable to serve as parity index for cols.
  int colParity = matrix[0][0];

  // Mark the parity indices with a 0 for each 0 encountered.
  for (int row = 0; row < matrix.size(); row++) {
    for (int col = 0; col < matrix[row].size(); col++) {
      if (matrix[row][col] == 0) {
        mark(matrix, row, col, colParity);
      }
    }
  }

  // Process all the area of matrix EXCLUDING the parity
  // index. This prevents unwanted collision.
  for (int row = 1; row < matrix.size(); row++) {
    for (int col = 1; col < matrix[row].size(); col++) {
      // Simply check if the parity row or parity col
      // is marked and set as 0 if true.
      if (matrix[0][col] == 0 || matrix[row][0] == 0) {
        matrix[row][col] = 0;
      }
    }
  }

  // Now, we handle the parity indices. In this, we only need
  // to check matrix(0,0) for parity columns (first row) and
  // colParity for parity rows (first column).
  // This is because, while marking, we are already setting
  // parity indices to 0 and hence, they don't require separate
  // processing.

  // We first handle the parity columns (the first row) instead of
  // parity rows (the first column) to prevent matrix(0,0) from
  // being updated first.
  if (matrix[0][0] == 0) {
    for (int col = 0; col < matrix[0].size(); col++) {
      matrix[0][col] = 0;
    }
  }
  // Finally, we handle the parity rows (the first column)
  // through a simple check of colParity.
  if (colParity == 0) {
    for (int row = 0; row < matrix.size(); row++) {
      matrix[row][0] = 0;
    }
  }
}
