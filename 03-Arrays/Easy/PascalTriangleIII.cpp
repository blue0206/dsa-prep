/*
 * Problem: Pascal's Triangle III
 *
 * Statement: Given a Row and Column, output the element present at that place
 *            in a Pascal's Triangle.
 *
 * Approach: The element at row `n` and column `r` in Pascal's Triangle can be
 *           calculated directly using the combinatorial formula for "n choose
 *           r", which is `nCr = n! / (r! * (n-r)!)`. This can be computed
 *           efficiently in a single loop to avoid large intermediate numbers.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void nCr(int n, int r);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int r, c;
    cin >> r >> c;

    // Pass r-1 and c-1 in case of 1-based index.
    // Current setup considers 0-based index.
    nCr(r, c);

    cout << endl;
  }

  return 0;
}

void nCr(int n, int r) {
  if (r > n) {
    cout << "Invalid input" << endl;
    return;
  }

  if (r > n - r) r = n - r;

  long long element = 1;
  for (int i = 0; i < r; i++) {
    element *= (n - i);
    element /= (i + 1);
  }

  cout << "The element present at row " << n << " and column " << r
       << " is: " << element << endl;
}
