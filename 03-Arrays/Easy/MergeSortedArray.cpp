/*
 * Problem: Merge Sorted Array (LeetCode #88)
 * Link: https://leetcode.com/problems/merge-sorted-array/description/
 */

/**
 * Follow-up: Given two sorted arrays, `nums1` of size `m` and `nums2` of size
 *            `n`, merge them into a single sorted sequence without using extra
 *            space. The first `m` elements of the merged sequence should be
 *            in `nums1`, and the remaining `n` elements should be in `nums2`.
 *            This is also known as merging two sorted arrays in-place.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void print(vector<int>& nums) {
  cout << "[ ";
  for (auto i : nums) {
    cout << i << " ";
  }
  cout << "]" << endl;
}

/**
 * Approach: Uses a three-pointer approach, starting from the end of `nums1`.
 *           One pointer (`index`) tracks the position to fill in `nums1`. The
 *           other two pointers (`left`, `right`) track the last valid elements
 *           in `nums1` and `nums2` respectively. The larger of the two
 *           elements is placed at `index`, and the corresponding pointers are
 *           moved inward. This avoids overwriting elements in `nums1` that
 *           haven't been processed yet.
 *
 * Time Complexity: O(M + N)
 * Space Complexity: O(1)
 */
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n);

/**
 * Approach: This approach compares the largest element of `nums1` with the
 *           smallest element of `nums2`. If the element in `nums1` is larger,
 *           they are swapped. This process continues, effectively moving the
 *           largest elements into `nums2`. After this initial pass, both
 *           arrays are sorted independently to restore their internal order.
 *
 * Time Complexity: O(M log M + N log N) due to sorting.
 * Space Complexity: O(1)
 */
void followUpApproach1(vector<int>& nums1, int m, vector<int>& nums2, int n);

/**
 * Approach: This uses the Gap Method, an algorithm derived from Shell Sort. It
 *           treats the two arrays as a single conceptual array of size `m+n`.
 *           It starts with a large `gap` and compares elements that are `gap`
 *           distance apart, swapping if they are in the wrong order. The `gap`
 *           is progressively reduced (typically halved) until it becomes 1.
 *           This process gradually sorts the entire conceptual array.
 *
 * Time Complexity: O((M+N)log(M+N))
 * Space Complexity: O(1)
 */
void followUpApproach2(vector<int>& nums1, int m, vector<int>& nums2, int n);

int main() {
  int t;
  cin >> t;

  int cases = t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    vector<int> nums1(m);
    vector<int> nums2(n);
    for (int i = 0; i < m; i++) cin >> nums1[i];
    for (int i = 0; i < n; i++) cin >> nums2[i];

    cout << "Test Case " << cases - t << "---------\n" << endl;

    //----------------------------MAIN SOLUTION---------------------------------
    cout << "--------MAIN SOLUTION--------" << endl;
    vector<int> mainSolutionArray1 = nums1;
    vector<int> mainSolutionArray2 = nums2;
    for (int i = 0; i < n; i++) {
      mainSolutionArray1.push_back(0);
    }
    cout << "Array 1: ";
    print(mainSolutionArray1);
    cout << "Array 2: ";
    print(mainSolutionArray2);

    merge(mainSolutionArray1, m, mainSolutionArray2, n);

    cout << "Result: ";
    print(mainSolutionArray1);
    cout << endl;

    //--------------------------FOLLOW-UP APPROACH 1----------------------------
    cout << "--------FOLLOW-UP APPROACH 1--------" << endl;
    vector<int> followUpApproach1Array1 = nums1;
    vector<int> followUpApproach1Array2 = nums2;

    cout << "Array 1: ";
    print(followUpApproach1Array1);
    cout << "Array 2: ";
    print(followUpApproach1Array2);

    followUpApproach1(followUpApproach1Array1, m, followUpApproach1Array2, n);
    cout << "Final Array 1: ";
    print(followUpApproach1Array1);
    cout << "Final Array 2: ";
    print(followUpApproach1Array2);
    cout << endl;

    //--------------------------FOLLOW-UP APPROACH 2----------------------------
    cout << "--------FOLLOW-UP APPROACH 2--------" << endl;
    vector<int> followUpApproach2Array1 = nums1;
    vector<int> followUpApproach2Array2 = nums2;

    cout << "Array 1: ";
    print(followUpApproach2Array1);
    cout << "Array 2: ";
    print(followUpApproach2Array2);

    followUpApproach2(followUpApproach2Array1, m, followUpApproach2Array2, n);

    cout << "Final Array 1: ";
    print(followUpApproach2Array1);
    cout << "Final Array 2: ";
    print(followUpApproach2Array2);
    cout << endl;

    cout << endl;
  }

  return 0;
}

// Main Solution
void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  int index = nums1.size() - 1;
  int left = m - 1;
  int right = n - 1;

  while (left >= 0 && right >= 0) {
    if (nums1[left] > nums2[right]) {
      nums1[index--] = nums1[left--];
    } else {
      nums1[index--] = nums2[right--];
    }
  }
  while (left >= 0) {
    nums1[index--] = nums1[left--];
  }
  while (right >= 0) {
    nums1[index--] = nums2[right--];
  }
}

// Follow-Up Approach 1
void followUpApproach1(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  int left = m - 1;
  int right = 0;

  while (left >= 0 && right < n) {
    if (nums1[left] > nums2[right]) {
      swap(nums1[left--], nums2[right++]);
    } else {
      break;
    }
  }
  sort(nums1.begin(), nums1.end());
  sort(nums2.begin(), nums2.end());
}

// Follow-Up Approach 2
void swapGreater(vector<int>& nums1, int left, vector<int>& nums2, int right) {
  if (nums1[left] > nums2[right]) {
    swap(nums1[left], nums2[right]);
  }
}
void followUpApproach2(vector<int>& nums1, int m, vector<int>& nums2, int n) {
  // Uses gap method derived from shell-sort.

  int k = m + n;
  int gap = (k / 2) + (k % 2);

  while (gap > 0) {
    int left = 0;
    int right = left + gap;

    while (right < k) {
      // left in nums1 and right in nums2
      if (left < m && right >= m) {
        swapGreater(nums1, left, nums2, right - m);
      }
      // left in nums2 and right in nums2
      else if (left >= m) {
        swapGreater(nums2, left - m, nums2, right - m);
      }
      // left in nums1 and right in nums1
      else {
        swapGreater(nums1, left, nums1, right);
      }
      left++;
      right++;
    }

    if (gap <= 1) break;
    gap = (gap / 2) + (gap % 2);
  }
}
