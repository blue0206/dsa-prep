/*
 * Problem: The Celebrity Problem
 * Link: https://www.geeksforgeeks.org/problems/the-celebrity-problem/1
 *
 * Approach: This problem can be solved in two passes with O(1) extra space.
 *
 *           1.  **Candidate Elimination Pass:**
 *               -   The core idea is that if person `A` knows person `B`, then
 *                   `A` cannot be a celebrity. If `A` does not know `B`, then
 *                   `B` cannot be a celebrity (since a celebrity must be known
 *                   by everyone).
 *               -   We can iterate through all people and eliminate one person
 *                   at each step. We start by assuming person `0` is a
 *                   potential celebrity (`candidate`).
 *               -   We then iterate from `i = 1` to `n-1`. In each step, we
 *                   compare `candidate` with `i`.
 *               -   If `knows(candidate, i)` is true, `candidate` is not a
 *                   celebrity. Our new potential candidate becomes `i`.
 *               -   If `knows(candidate, i)` is false, `i` is not a celebrity.
 *                   We keep our current `candidate`.
 *               -   After this single pass, we are left with only one person
 *                   who could possibly be a celebrity.
 *
 *           2.  **Candidate Verification Pass:**
 *               -   The person identified in the first pass is just a
 *                   candidate. We must verify if they meet the two conditions
 *                   of a celebrity: they know no one, and everyone knows them.
 *               -   A single loop checks these conditions for all other people
 *                   `i`. If the candidate fails for any `i`, we return -1.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int celebrity(const vector<vector<int>>& mat);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> mat(n, vector<int>(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> mat[i][j];
      }
    }

    cout << "Input Matrix: [ ";
    for (auto row : mat) {
      cout << "[ ";
      for (auto i : row) {
        cout << i << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << "Celebrity Index: " << celebrity(mat) << endl;

    cout << endl;
  }

  return 0;
}

int celebrity(const vector<vector<int>>& mat) {
  int n = mat.size();
  if (n < 1) return -1;

  // Pass 1: Find a potential celebrity candidate.
  int candidate = 0;
  for (int i = 1; i < n; i++) {
    // If the current candidate knows person i, then the current candidate
    // cannot be a celebrity. Person i becomes the new candidate.
    if (mat[candidate][i]) {
      candidate = i;
    }
  }

  // Pass 2: Verify if the candidate is actually a celebrity.
  for (int i = 0; i < n; i++) {
    // A celebrity doesn't know anyone (mat[candidate][i] == 0)
    // and everyone knows the celebrity (mat[i][candidate] == 1).
    // We skip checking the person against themselves.
    if (i != candidate && (mat[candidate][i] || !mat[i][candidate])) {
      return -1;
    }
  }

  return candidate;
}
