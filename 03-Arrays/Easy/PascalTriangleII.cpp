/*
 * Problem: Pascal's Triangle II (LeetCode #119)
 * Link: https://leetcode.com/problems/pascals-triangle-ii/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: This approach calculates each element of the target row
 *           independently using the combinatorial formula for nCr.
 *           A helper function `nCr` computes the value for each column
 *           `r` in the given `rowIndex` `n`.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(N)
 */
vector<int> bruteForceApproach(int rowIndex);
int nCr(int n, int r);

/**
 * Approach: This approach builds the row iteratively, which is more efficient.
 *           It starts with the first element (which is always 1) and
 *           calculates each subsequent element `nCr` based on the value of the
 *           previous element `nC(r-1)`. This avoids redundant calculations and
 *           computes the entire row in a single pass.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
vector<int> optimizedApproach(int rowIndex);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int rowIndex;
    cin >> rowIndex;

    vector<int> bruteForceApproachArr = bruteForceApproach(rowIndex);
    cout << "Brute-Force Approach: [ ";
    for (auto i : bruteForceApproachArr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> optimizedApproachArr = optimizedApproach(rowIndex);
    cout << "Optimized Approach: [ ";
    for (auto i : optimizedApproachArr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> bruteForceApproach(int rowIndex) {
  vector<int> ans;
  for (int i = 0; i <= rowIndex; i++) {
    ans.push_back(nCr(rowIndex, i));
  }
  return ans;
}
int nCr(int n, int r) {
  if (r > n) return 0;

  if (r > n - r) r = n - r;

  long long element = 1;
  for (int i = 0; i < r; i++) {
    element *= (n - i);
    element /= (i + 1);
  }

  return element;
}

vector<int> optimizedApproach(int rowIndex) {
  vector<int> ans;
  ans.push_back(1);

  long long element = 1;
  for (int i = 0; i < rowIndex; i++) {
    element *= (rowIndex - i);
    element /= (i + 1);
    ans.push_back(element);
  }
  return ans;
}
