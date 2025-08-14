/*
 * Problem: Single Element in a Sorted Array (LeetCode #540)
 * Link:
 * https://leetcode.com/problems/single-element-in-a-sorted-array/description/
 *
 * Approach: This problem is solved using a modified binary search. The key
 *           observation is that the single element is the only one that breaks
 *           the pairing pattern in the array.
 *           1.  **Pattern:** Before the single element, the first element of a
 *               pair is at an even index and the second is at an odd index.
 *               After the single element, this pattern is disrupted.
 *           2.  **Edge Cases:** The single element at the very beginning or end
 *               of the array is handled first to simplify the binary search.
 *           3.  **Binary Search:** At each `mid`, we check if it's the single
 *               element. If not, we check its pair and its own index parity
 *               (even/odd) to determine if we are in the ordered half or the
 *               disrupted half, allowing us to eliminate one side.
 *
 * Time Complexity: O(logN)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int singleNonDuplicate(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Single Element: " << singleNonDuplicate(nums) << endl;

    cout << endl;
  }

  return 0;
}

int singleNonDuplicate(vector<int>& nums) {
  // Handle edge cases to prevent too many checks
  // to prevent runtime error.
  if (nums.size() == 1) return nums[0];
  if (nums[0] != nums[1]) return nums[0];
  if (nums.back() != nums[nums.size() - 2]) return nums.back();

  int low = 1;
  int high = nums.size() - 2;
  int ans = -1;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    // If single element is found, update ans and break.
    if (nums[mid] != nums[mid - 1] && nums[mid] != nums[mid + 1]) {
      ans = nums[mid];
      break;
    }

    // The single element is always present at an even index. Therefore,
    // all pairs existing before single element are at index (even,odd)
    // and all pairs existing after single element are at index (odd, even).
    if (nums[mid] == nums[mid + 1]) {
      if (mid & 1) {
        // Since first element is odd, we are on the left of
        // single element, so we move to right.
        high = mid - 1;
      } else {
        // First element is even, so we are on right side of
        // single element, so we move to left.
        low = mid + 1;
      }
    } else {
      if (mid & 1) {
        // First element is even, so we are on right side of
        // single element, so we move to left.
        low = mid + 1;
      } else {
        // Since first element is odd, we are on the left of
        // single element, so we move to right.
        high = mid - 1;
      }
    }
  }

  return ans;
}
