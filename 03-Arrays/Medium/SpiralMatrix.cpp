/*
 * Problem: Spiral Matrix (LeetCode #54)
 * Link: https://leetcode.com/problems/spiral-matrix/description/
 *
 * Approach: Use four pointers (top, bottom, left, right) to define the
 *           boundaries of the current layer of the matrix. Iteratively traverse
 *           the top row, right column, bottom row, and left column, adding
 *           elements to the result. After each traversal, shrink the
 *           corresponding boundary inward. Repeat until the boundaries cross.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(1) auxiliary space. O(M * N) for storing the answer.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> spiralOrder(const vector<vector<int>>& matrix);

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

    vector<int> ans = spiralOrder(matrix);
    cout << "Spiral Order: [ ";
    for (auto i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> spiralOrder(const vector<vector<int>>& matrix) {
  vector<int> ans;
  int top = 0;
  int left = 0;
  int right = matrix[0].size() - 1;
  int bottom = matrix.size() - 1;

  while (top <= bottom && left <= right) {
    // Traverse the top row from left to right.
    for (int i = left; i <= right; i++) {
      ans.push_back(matrix[top][i]);
    }
    top++;

    // Traverse the right-most column from top to bottom.
    for (int i = top; i <= bottom; i++) {
      ans.push_back(matrix[i][right]);
    }
    right--;

    // Break if boundaries crossed.
    if (top > bottom) {
      break;
    }
    // Traverse the bottom row from right to left.
    for (int i = right; i >= left; i--) {
      ans.push_back(matrix[bottom][i]);
    }
    bottom--;

    // Break if boundaries crossed.
    if (left > right) {
      break;
    }
    // Traverse the left-most column from bottom to top.
    for (int i = bottom; i >= top; i--) {
      ans.push_back(matrix[i][left]);
    }
    left++;
  }

  return ans;
}
