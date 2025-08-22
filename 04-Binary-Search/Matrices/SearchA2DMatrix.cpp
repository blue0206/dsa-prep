/*
 * Problem: Search a 2D Matrix (LeetCode #74)
 * Link: https://leetcode.com/problems/search-a-2d-matrix/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach first performs a binary search on the rows of the
 *           matrix to identify which row could possibly contain the target. A
 *           row is a candidate if the target is between its first and last
 *           element. Once the correct row is found, a second binary search is
 *           performed on that specific row to find the target.
 *
 * Time Complexity: O(log(M) + log(N))
 * Space Complexity: O(1)
 */
bool bsInBs(vector<vector<int>>& matrix, int target);
bool bs(vector<int>& nums, int target);

/**
 * Approach: This optimal approach treats the M x N matrix as a single,
 *           flattened, sorted array of size M * N. A standard binary search is
 *           performed on the index range [0, M*N - 1]. For any given 1D index
 *           `mid`, it's mapped back to its 2D coordinates using
 *           `row = mid / N` and `col = mid % N`, where N is the number of
 *           columns. This allows finding the target in a single binary search
 *           pass.
 *
 * Time Complexity: O(log(M * N))
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
         << (bsInBs(matrix, target) ? "True" : "False") << endl;

    cout << "Search Result (Optimal Approach): "
         << (optimalApproach(matrix, target) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

//-------------------------ROW-WISE SEARCH APPROACH-----------------------------
bool bsInBs(vector<vector<int>>& matrix, int target) {
  int colSize = matrix[0].size();
  int low = 0;
  int high = matrix.size() - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (target >= matrix[mid][0] && target <= matrix[mid][colSize - 1]) {
      return bs(matrix[mid], target);
    } else if (matrix[mid][colSize - 1] < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
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
  int m = matrix.size();
  int n = matrix[0].size();

  int low = 0;
  int high = (m * n) - 1;

  while (low <= high) {
    int mid = low + (high - low) / 2;
    int element = matrix[mid / n][mid % n];
    if (element == target) {
      return true;
    } else if (element < target) {
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return false;
}
