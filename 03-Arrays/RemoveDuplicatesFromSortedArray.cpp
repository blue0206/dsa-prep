/*
 * Problem: Remove Duplicates from Sorted Array (LeetCode #26)
 * Link:
 * https://leetcode.com/problems/remove-duplicates-from-sorted-array/description/
 *
 * Approach: Use a two-pointer technique. A 'slow' pointer (left) tracks the
 *           end of the unique elements subarray. A 'fast' pointer (right)
 *           iterates through the array. When the fast pointer finds an element
 *           different from the one at the slow pointer, we place it at the
 *           next position in the unique subarray and advance the slow pointer.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <iostream>
#include <vector>

using namespace std;

int removeDups(vector<int>& nums) {
  int left = 0;
  int right = 1;
  while (right < nums.size()) {
    if (nums[left] != nums[right]) {
      swap(nums[++left], nums[right]);
    }
    right++;
  }

  return left + 1;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    int k = removeDups(nums);

    cout << "Number of unique elements: " << k << endl;
    cout << "Array after removing duplicates: [ ";
    for (int i = 0; i < k; i++) {
      cout << nums[i] << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}
