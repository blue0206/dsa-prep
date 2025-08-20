/*
 * Problem: Painter's Partition
 * Link:
 * https://www.codechef.com/practice/course/binary-search/INTBINS01/problems/BSEX03?tab=statement
 *
 * Approach: This is a classic "Binary Search on Answer" problem, structurally
 *           identical to "Book Allocation" and "Split Array Largest Sum". We
 *           need to find the minimum of the maximum work assigned to a painter.
 *           1.  **Search Space:** The answer (max work for a painter) must be
 *               in a specific range. The minimum possible value is the length
 *               of the longest single board (as one painter must handle it).
 *               The maximum is the sum of all board lengths (if one painter
 *               did all the work).
 *           2.  **Binary Search:** We binary search on this range of possible
 *               answers. For each `mid` value (a potential max work limit),
 *               we check if it's possible to partition the work among `k`
 *               painters.
 *           3.  **Feasibility Check:** The `painterCount` function greedily
 *               determines the minimum number of painters required if no
 *               painter can work more than `mid` units.
 *           4.  **Narrowing Down:** If the required painters are within our
 *               limit `k`, the `mid` is a possible answer, so we try for a
 *               better (smaller) one. Otherwise, we need to allow more work
 *               per painter.
 *
 * Time Complexity: O(N * log(S)), where S is the sum of all board lengths.
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int painterPartition(vector<int>& boards, int k);
int painterCount(vector<int>& boards, int mid);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Possible Maximum Board Length: "
         << painterPartition(nums, k) << endl;

    cout << endl;
  }

  return 0;
}

int painterPartition(vector<int>& boards, int k) {
  // The search space for the answer is from the largest single board
  // to the sum of all boards.
  int low = 0;
  int high = 0;
  for (int i : boards) {
    if (i > low) low = i;
    high += i;
  }

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int painters = painterCount(boards, mid);
    // If the number of painters required for this `mid` is within our limit,
    // it's a possible answer. Try to find an even smaller max length.
    // Note that as we move to the right on our search space, the no. of painter
    // decreases and vice-versa for left.
    if (painters <= k) {
      high = mid - 1;
      // Otherwise, the max length `mid` is too small, we need to allow more.
    } else {
      low = mid + 1;
    }
  }

  return low;
}

int painterCount(vector<int>& boards, int mid) {
  // Start with one painter and zero work assigned.
  int painters = 1;
  int paintLength = 0;

  for (int i = 0; i < boards.size(); i++) {
    // If the current painter can take on this board without exceeding the limit
    // `mid`.
    if (paintLength + boards[i] <= mid) {
      paintLength += boards[i];
    } else {
      // Otherwise, a new painter is required.
      painters++;
      // This new painter starts with the current board.
      paintLength = boards[i];
    }
  }

  return painters;
}
