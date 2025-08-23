/*
 * Problem: Find Median in a Row-wise Sorted Matrix
 * Link:
 * https://www.naukri.com/code360/problems/median-of-a-row-wise-sorted-matrix_1115473?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is a prime example of "Binary Search on Answer".
 *           Instead of searching on indices, we search for the value of the
 *           median within the possible range of numbers in the matrix.
 *           1.  **Search Space:** The median must be a value between the
 *               minimum and maximum elements in the matrix. We can find this
 *               range by checking the first and last elements of each row.
 *               This defines our `low` and `high` for the binary search.
 *           2.  **Binary Search:** For each `mid` value in our search space, we
 *               need to determine if it could be the median. The median is the
 *               element `x` where the count of numbers `<= x` is greater than
 *               `(M*N)/2`.
 *           3.  **Feasibility Check:** We create a helper function that counts
 *               how many elements in the matrix are less than or equal to
 *               `mid`. This is done efficiently by using `upper_bound` on each
 *               row, which takes O(log N) time per row.
 *           4.  **Narrowing Down:** If the count is too small, we search in the
 *               right half (`low = mid + 1`). If the count is sufficient, `mid`
 *               is a potential answer, so we search for a smaller one in the
 *               left half (`high = mid - 1`).
 *
 * Time Complexity: O(M * log(N) * log(Range)), where Range is (max - min)
 * value. Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int median(vector<vector<int>>& matrix, int m, int n);
int countSmallEquals(vector<vector<int>>& matrix, int element);

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
    for (int i = 0; i < m; i++) {
      cout << "[ ";
      for (int j = 0; j < n; j++) {
        cout << matrix[i][j] << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Matrix Median: " << median(matrix, m, n) << endl;

    cout << endl;
  }

  return 0;
}

int median(vector<vector<int>>& matrix, int m, int n) {
  int low = INT_MAX;
  int high = INT_MIN;
  for (int i = 0; i < m; i++) {
    low = min(low, matrix[i][0]);
    high = max(high, matrix[i][n - 1]);
  }

  int pivot = (m * n) / 2;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int smallEquals = countSmallEquals(matrix, mid);

    if (smallEquals <= pivot) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return low;
}

int countSmallEquals(vector<vector<int>>& matrix, int element) {
  int count = 0;
  for (int i = 0; i < matrix.size(); i++) {
    // upper_bound finds the first element > element.
    // The distance from the beginning is the count of elements <= element.
    count += (upper_bound(matrix[i].begin(), matrix[i].end(), element) -
              matrix[i].begin());
  }

  return count;
}
