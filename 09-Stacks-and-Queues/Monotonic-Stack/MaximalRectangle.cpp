/*
 * Problem: Maximal Rectangle (LeetCode #85)
 * Link: https://leetcode.com/problems/maximal-rectangle/description/
 *
 * Approach: This problem can be solved by reducing it to a series of "Largest
 *           Rectangle in Histogram" problems (LeetCode #84).
 *
 *           The core idea is to iterate through each row of the matrix and
 *           treat it as the "ground" for a histogram. For each row `i`, we
 *           construct a histogram where the height of the `j`-th bar is the
 *           number of consecutive '1's directly above `matrix[i][j]`.
 *
 *           1.  Initialize a `histogram` array of size `m` (number of columns)
 *               with zeros.
 *           2.  Iterate through each row of the matrix. For each cell, if it's
 *               a '1', increment the corresponding height in the `histogram`
 *               array. If it's a '0', reset the height to 0.
 *           3.  After updating the histogram for a row, calculate the largest
 *               rectangle in that histogram using the single-pass monotonic
 *               stack approach.
 *           4.  Keep track of the maximum area found across all rows.
 *
 * Time Complexity: O(M * N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int maximalRectangle(vector<vector<char>>& matrix);
int largestRectangle(const vector<int>& histogram, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<vector<char>> matrix(n, vector<char>(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> matrix[i][j];
      }
    }

    cout << "Input Matrix: [ ";
    for (auto row : matrix) {
      cout << "[ ";
      for (auto i : row) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Maximal Rectangle: " << maximalRectangle(matrix) << endl;

    cout << endl;
  }

  return 0;
}

int maximalRectangle(vector<vector<char>>& matrix) {
  if (matrix.empty() || matrix[0].empty()) return 0;

  int n = matrix.size();
  int m = matrix[0].size();

  // There are m cols and we pad one 0 at end for solving in single pass.
  vector<int> histogram(m + 1, 0);

  int maxArea = 0;
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < m; j++) {
      if (matrix[i][j] == '0') {
        histogram[j] = 0;
      } else {
        histogram[j]++;
      }
    }

    maxArea = max(maxArea, largestRectangle(histogram, m + 1));
  }

  return maxArea;
}

int largestRectangle(const vector<int>& histogram, int n) {
  stack<int> st;
  int maxArea = 0;
  for (int i = 0; i < n; i++) {
    while (!st.empty() && histogram[st.top()] > histogram[i]) {
      int height = histogram[st.top()];
      st.pop();

      int pse = (st.empty()) ? -1 : st.top();
      int width = i - pse - 1;

      int area = width * height;
      maxArea = max(maxArea, area);
    }

    st.push(i);
  }

  return maxArea;
}
