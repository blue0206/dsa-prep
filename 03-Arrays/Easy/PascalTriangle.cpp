/*
 * Problem: Pascal's Triangle (LeetCode #118)
 * Link: https://leetcode.com/problems/pascals-triangle/description/
 *
 * Approach: Iteratively construct the triangle row by row. For each row `i`,
 *           we know it has `i+1` elements. The first and last elements of any
 *           row are always 1. Every other element at position `j` in the
 *           current row is the sum of the two elements directly above it in the
 *           previous row, i.e., `ans[i-1][j-1] + ans[i-1][j]`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N^2) for storing the result triangle.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> generate(int numRows);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int numRows;
    cin >> numRows;

    vector<vector<int>> triangle = generate(numRows);

    cout << "Pascal's Triangle for " << numRows << " rows:" << endl;
    cout << "[ ";
    for (const auto& row : triangle) {
      cout << "[ ";
      for (int val : row) {
        cout << val << " ";
      }
      cout << "] " << endl;
    }
    cout << "]" << endl;
  }

  return 0;
}

vector<vector<int>> generate(int numRows) {
  vector<vector<int>> ans(numRows);

  for (int i = 0; i < numRows; i++) {
    for (int j = 0; j <= i; j++) {
      if (j == 0 || j == i) {
        ans[i].push_back(1);
      } else {
        ans[i].push_back(ans[i - 1][j - 1] + ans[i - 1][j]);
      }
    }
  }

  return ans;
}