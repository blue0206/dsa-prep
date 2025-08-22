/*
 * Problem: Median of Two Sorted Arrays (LeetCode #4)
 * Link: https://leetcode.com/problems/median-of-two-sorted-arrays/description/
 *
 * Approach: This problem can be solved optimally using a binary search approach
 *           on the partitions of the arrays. The goal is to find a "cut" in
 *           both arrays that divides all elements into a "left part" and a
 *           "right part", where every element in the left part is less than or
 *           equal to every element in the right part.
 *
 *           1.  **Partitioning Idea:** Imagine a single merged sorted array of
 *               size `n1 + n2`. The median is the element (or average of two
 *               elements) that splits this array into two equal halves. The
 *               left half should contain `(n1 + n2 + 1) / 2` elements.
 *           2.  **Binary Search on Smaller Array:** To optimize, we always
 *               perform the binary search on the smaller of the two arrays.
 *               We search for the correct cut point (`cut1`) in the smaller
 *               array. The corresponding cut in the other array (`cut2`) is
 *               then determined automatically.
 *           3.  **Boundary Elements:** For any given `cut1` and `cut2`, we are
 *               interested in four boundary elements: `l1`, `r1`, `l2`, `r2`.
 *               These represent the elements to the left and right of the
 *               cuts in both arrays.
 *           4.  **Correctness Condition:** The partition is correct if
 *               `l1 <= r2` AND `l2 <= r1`. This ensures all elements in the
 *               combined left part are smaller than all elements in the
 *               combined right part.
 *           5.  **Finding the Median:** Once the correct partition is found,
 *               the median is `max(l1, l2)` for an odd total length, or
 *               `(max(l1, l2) + min(r1, r2)) / 2.0` for an even total length.
 *
 * Time Complexity: O(log(min(N, M)))
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;
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

    cout << "Median of Sorted Two Arrays: "
         << findMedianSortedArrays(nums1, nums2) << endl;

    cout << endl;
  }

  return 0;
}

double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
  // Ensure binary search is on the smaller array for efficiency.
  if (nums2.size() < nums1.size()) {
    return findMedianSortedArrays(nums2, nums1);
  }

  int n1 = nums1.size();
  int n2 = nums2.size();
  int totalSize = n1 + n2;
  int low = 0;
  int high = n1;
  // The left partition should have (n1+n2+1)/2 elements
  int leftPartitionSize = (totalSize + 1) / 2;

  while (low <= high) {
    // mid1 is the number of elements from nums1 in the left partition
    int mid1 = low + (high - low) / 2;
    // mid2 is the number of elements from nums2 in the left partition
    int mid2 = leftPartitionSize - mid1;

    // l1, r1 are the boundary elements for nums1's partition
    int l1 = (mid1 == 0) ? INT_MIN : nums1[mid1 - 1];
    int r1 = (mid1 == n1) ? INT_MAX : nums1[mid1];

    // l2, r2 are the boundary elements for nums2's partition
    int l2 = (mid2 == 0) ? INT_MIN : nums2[mid2 - 1];
    int r2 = (mid2 == n2) ? INT_MAX : nums2[mid2];

    // Check if we found a valid partition
    if (l1 <= r2 && l2 <= r1) {
      // If total length is odd, median is the max of left elements
      if (totalSize % 2 == 1) {
        return max(l1, l2);
      }
      // If total length is even, median is avg of max of left and min of right
      return ((double)max(l1, l2) + (double)min(r1, r2)) / 2.0;
    } else if (l1 > r2) {
      // Move left in nums1
      high = mid1 - 1;
    } else {
      // Move right in nums1
      low = mid1 + 1;
    }
  }

  return 0.0;  // Should not be reached for valid inputs
}
