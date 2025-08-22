/*
 * Problem: Kth Element of Two Sorted Arrays
 * Link:
 * https://www.naukri.com/code360/problems/k-th-element-of-2-sorted-array_1164159?leftPanelTabValue=PROBLEM
 *
 * Approach: This problem is a generalization of "Median of Two Sorted Arrays"
 *           and can be solved optimally using binary search on partitions. The
 *           goal is to find a "cut" in both arrays that divides the combined
 *           elements into a left part of size `k` and a right part, where
 *           every element in the left is less than or equal to every element
 *           in the right.
 *
 *           1.  **Binary Search on Smaller Array:** To optimize, we always
 *               perform the binary search on the smaller of the two arrays.
 *               We search for the correct number of elements to take from the
 *               first array (`cut1`). The number from the second (`cut2`) is
 *               then `k - cut1`.
 *           2.  **Search Space:** We define a valid range for `cut1` to reduce
 *               unnecessary checks. This range is `[max(0, k-n2), min(k, n1)]`.
 *           3.  **Correctness Condition:** The partition is correct if the
 *               largest element of the left part is smaller than the smallest
 *               element of the right part (`l1 <= r2 && l2 <= r1`).
 *           4.  **Finding the Kth Element:** Once the correct partition is
 *               found, the k-th element is the largest element in the combined
 *               left partition, which is `max(l1, l2)`.
 *
 * Time Complexity: O(log(min(N, M)))
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int kthElement(vector<int>& arr1, vector<int>& arr2, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m, k;
    cin >> n >> m >> k;
    vector<int> nums1(n);
    vector<int> nums2(m);
    for (int i = 0; i < n; i++) cin >> nums1[i];
    for (int i = 0; i < m; i++) cin >> nums2[i];

    cout << "Array 1: [ ";
    for (auto i : nums1) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "Array 2: [ ";
    for (auto i : nums2) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Kth Element: " << kthElement(nums1, nums2, k) << endl;

    cout << endl;
  }

  return 0;
}

int kthElement(vector<int>& arr1, vector<int>& arr2, int k) {
  // Ensure binary search is on the smaller array for efficiency.
  if (arr2.size() < arr1.size()) {
    return kthElement(arr2, arr1, k);
  }

  int n1 = arr1.size();
  int n2 = arr2.size();

  // Define the search space for the number of elements to take from arr1.
  // low: We must take at least k-n2 elements from arr1 if k > n2.
  //      Otherwise, we can take 0.
  int low = max(k - n2, 0);
  // high: We can take at most k elements from arr1 (if we take 0 from arr2).
  //       We also cannot take more than n1 elements.
  int high = min(k, n1);

  while (low <= high) {
    // mid1 is the number of elements from arr1 in the left partition.
    int mid1 = low + (high - low) / 2;
    // mid2 is the number of elements from arr2 in the left partition.
    int mid2 = k - mid1;

    int l1 = (mid1 == 0) ? INT_MIN : arr1[mid1 - 1];
    int l2 = (mid2 == 0) ? INT_MIN : arr2[mid2 - 1];

    int r1 = (mid1 == n1) ? INT_MAX : arr1[mid1];
    int r2 = (mid2 == n2) ? INT_MAX : arr2[mid2];

    if (l1 <= r2 && l2 <= r1) {
      return max(l1, l2);
    } else if (l1 > r2) {
      high = mid1 - 1;
    } else {
      low = mid1 + 1;
    }
  }

  return 0;  // Should not be reached for valid inputs.
}
