/*
 * Problem: Count Inversions
 *
 * Statement: For a given array of integers, find the number of pairs `(i, j)`
 *            such that `i < j` and `arr[i] > arr[j]`. This pair is called an
 *            inversion. The total count can be large, so return it modulo
 *            10^9 + 7.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using ll = long long;

const ll M = 1e9 + 7;

/**
 * Approach: Use two nested loops. The outer loop iterates from `i = 0` to
 *           `n-1`, and the inner loop iterates from `j = i+1` to `n-1`. For
 *           each pair `(i, j)`, if `nums[i] > nums[j]`, increment the count.
 *
 * Time Complexity: O(N^2)
 * Space Complexity: O(1)
 */
ll bruteForceApproach(const vector<ll>& nums);

/**
 * Approach: This approach uses the "Divide and Conquer" strategy, based on the
 *           Merge Sort algorithm. The core idea is that the total number of
 *           inversions is the sum of:
 *           1. Inversions in the left half of the array.
 *           2. Inversions in the right half of the array.
 *           3. Inversions between the left and right halves (cross-inversions).
 *           The first two are found by recursive calls. The cross-inversions
 *           are counted efficiently during the standard merge process of Merge
 *           Sort.
 *
 * Time Complexity: O(N logN)
 * Space Complexity: O(N)
 */
ll optimalApproach(vector<ll> nums);

int main() {
  int t;
  cin >> t;

  int cases = t;

  while (t--) {
    int n;
    cin >> n;
    vector<ll> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "--------Test Case " << cases - t << "--------" << endl;

    cout << "Brute-Force Approach: " << bruteForceApproach(nums) << endl;
    cout << "Optimal Approach: " << optimalApproach(nums) << endl;

    cout << endl;
  }

  return 0;
}

ll bruteForceApproach(const vector<ll>& nums) {
  ll count = 0 % M;

  for (int i = 0; i < nums.size(); i++) {
    for (int j = i + 1; j < nums.size(); j++) {
      if (nums[j] < nums[i]) {
        count = (count + 1) % M;
      }
    }
  }

  return count;
}

//----------------------------OPTIMAL APPROACH---------------------------------
ll countInversions(vector<ll>& nums, int start, int mid, int end) {
  ll count = 0 % M;
  int leftSize = mid - start + 1;
  vector<ll> leftNums(leftSize);
  int leftIndex = 0;

  int rightSize = end - mid;
  vector<ll> rightNums(rightSize);
  int rightIndex = 0;

  for (int i = start; i <= mid; i++) {
    leftNums[leftIndex++] = nums[i];
  }
  for (int i = mid + 1; i <= end; i++) {
    rightNums[rightIndex++] = nums[i];
  }

  leftIndex = 0;
  rightIndex = 0;
  int index = start;
  while (leftIndex < leftSize && rightIndex < rightSize) {
    if (rightNums[rightIndex] < leftNums[leftIndex]) {
      ll remainingElements = leftSize - leftIndex;
      count = (count + remainingElements) % M;
      nums[index++] = rightNums[rightIndex++];
    } else {
      nums[index++] = leftNums[leftIndex++];
    }
  }

  while (leftIndex < leftSize) {
    nums[index++] = leftNums[leftIndex++];
  }
  while (rightIndex < rightSize) {
    nums[index++] = rightNums[rightIndex++];
  }

  return count;
}

ll divideAndCount(vector<ll>& nums, int start, int end) {
  if (start >= end) {
    return 0;
  }
  int mid = start + (end - start) / 2;
  ll count = 0 % M;
  count = (count + divideAndCount(nums, start, mid)) % M;
  count = (count + divideAndCount(nums, mid + 1, end)) % M;
  count = (count + countInversions(nums, start, mid, end)) % M;
  return count;
}

ll optimalApproach(vector<ll> nums) {
  return divideAndCount(nums, 0, nums.size() - 1);
}
