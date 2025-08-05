/*
 * Problem: Next Permutation (LeetCode #31)
 * Link: https://leetcode.com/problems/next-permutation/description/
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

/**
 * Approach: Use the `next_permutation()` STL algorithm.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
void stlApproach(vector<int>& nums);

/**
 * Approach:There are 3 major parts to this solution:
 *          1.  Match the longest possible prefix as the next permutation will
 *              always have prefix match with current one (unless it is last.)
 *              Once matched, we find the last element of such prefix which is
 *              the break-point element. The element next to break-point
 *              element is always greater.
 *              In case of an array in descending order, there is no break-point
 *              element and hence we simply return it after sorting it in
 *              ascending order by a simple reverse.
 *          2.  Once the break-point element is found, we look for the smallest
 *              possible element that is greater than the break-point element
 *              in the right half of array. We can simply do this by iterating
 *              from the back as the array after the break-point index is always
 *              in descending order.
 *              Once we find the smallest element greater than break-point
 *              element, we swap it with our break-point element as it will form
 *              the break-point of the next permutation. Note that the right
 *              half of array will still be in descending order as we just
 *              swapped the smallest element with an even smaller element.
 *          3.  Once we have swapped the break-point element, we now have the
 *              break-point of the next permutation in its right place. However,
 *              the permutation might still not be the smallest possible one
 *              since we haven't made the right half to be smallest possible.
 *              Since the right half is in descending order, this means that it
 *              is maximum possible permutation of itself. In order to make it
 *              minimum, we simply make it in ascending order! Just sort it with
 *              a reverse and that's it, we have our next permutation.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
void twoPointerApproach(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    vector<int> stlApproachArr = nums;
    vector<int> twoPointerApproachArr = nums;

    stlApproach(stlApproachArr);
    cout << "STL Approach: [ ";
    for (auto i : stlApproachArr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    twoPointerApproach(twoPointerApproachArr);
    cout << "Two-Pointer Approach: [ ";
    for (auto i : twoPointerApproachArr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

void stlApproach(vector<int>& nums) {
  next_permutation(nums.begin(), nums.end());
}

void twoPointerApproach(vector<int>& nums) {
  int breakPointIndex = -1;
  // Find and store break-point index.
  for (int i = nums.size() - 2; i >= 0; i--) {
    if (nums[i] < nums[i + 1]) {
      breakPointIndex = i;
      break;
    }
  }

  // If break-point index does not exist, the array is in
  // descending order, i.e., the permutation is of highest order.
  // Therefore, we just return a permutation of lowest order by making
  // the array back to ascending order with a simple reverse.
  if (breakPointIndex == -1) {
    reverse(nums.begin(), nums.end());
    return;
  }

  // If break-point index is found, we now look for the smallest greater
  // element than the break-point element that occurs in array after
  // the break-point index.
  // Once found, we simply swap as this element will form the next
  // permutation.
  for (int i = nums.size() - 1; i > breakPointIndex; i--) {
    if (nums[i] > nums[breakPointIndex]) {
      swap(nums[i], nums[breakPointIndex]);
      break;
    }
  }

  // Since we need the next permutation, we simple sort the array after
  // the new break-point element to ensure it is the smallest possible
  // permutation with that break-point element.
  reverse(nums.begin() + breakPointIndex + 1, nums.end());
}
