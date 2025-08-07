/*
 * Problem: Rotate Image (LeetCode #48)
 * Link: https://leetcode.com/problems/rotate-image/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: Create a new N x N matrix to store the result. Iterate through the
 *           original matrix and place each element into its new rotated
 *           position in the new matrix. Finally, copy the new matrix back to
 *           the original one.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2)
 */
void bruteForceApproach(vector<vector<int>>& matrix);

/**
 * Approach: Perform the rotation in-place in two steps. First, transpose the
 *           matrix (swap `matrix[i][j]` with `matrix[j][i]`). After
 *           transposing, reverse each row of the matrix. The combination of
 *           these two operations results in a 90-degree clockwise rotation.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
void optimalApproach(vector<vector<int>>& matrix);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<vector<int>> matrix(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
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

void bruteForceApproach(vector<vector<int>>& matrix) {
  vector<vector<int>> rotatedMatrix(matrix.size(), vector<int>(matrix.size()));

  int row = 0;
  for (int i = 0; i < matrix.size(); i++) {
    int col = 0;
    for (int j = matrix.size() - 1; j >= 0; j--) {
      rotatedMatrix[row][col++] = matrix[j][i];
    }
    row++;
  }

  matrix = rotatedMatrix;
}

void optimalApproach(vector<vector<int>>& matrix) {
  // Transpose matrix.
  for (int i = 0; i < matrix.size(); i++) {
    for (int j = i; j < matrix.size(); j++) {
      swap(matrix[j][i], matrix[i][j]);
    }
  }

  // Reverse rows.
  for (int i = 0; i < matrix.size(); i++) {
    reverse(matrix[i].begin(), matrix[i].end());
  }
}
