/*
 * Problem: Sliding Window Maximum (LeetCode #239)
 * Link: https://leetcode.com/problems/sliding-window-maximum/description/
 *
 * Approach: This problem is solved using a sliding window approach combined
 *           with a monotonic deque. The deque stores indices of elements from
 *           the input array, ensuring that the corresponding values are in
 *           decreasing order.
 *
 *           1.  **Window Management:** Two pointers, `low` and `high`, define
 *               the current window. The `high` pointer expands the window to
 *               the right.
 *           2.  **Deque Maintenance:**
 *               -   **Front:** Before processing a new element, indices that
 *                   are no longer in the `[low, high]` window are removed from
 *                   the front of the deque.
 *               -   **Back:** To maintain the decreasing monotonic property,
 *                   indices corresponding to elements smaller than or equal to
 *                   the current element (`nums[high]`) are removed from the
 *                   back.
 *           3.  **Element Addition:** The index of the current element (`high`)
 *               is always added to the back of the deque.
 *           4.  **Result Calculation:** When the window size (`high - low + 1`)
 *               reaches `k`, the maximum element for that window is
 *               `nums[dq.front()]`. This value is added to the result, and the
 *               window is slid forward by incrementing `low`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(k)
 */

#include <algorithm>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

vector<int> maxSlidingWindow(const vector<int>& nums, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "k: " << k << endl;

    vector<int> ans = maxSlidingWindow(nums, k);

    cout << "Result: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> maxSlidingWindow(const vector<int>& nums, int k) {
  deque<int> dq;
  vector<int> ans;

  int low = 0;
  int high = 0;
  while (high < nums.size()) {
    // 1. Maintain Window (Front): Remove indices from the front that are out of
    // the current window [low, high].
    if (!dq.empty() && dq.front() < low) dq.pop_front();

    // 2. Maintain Monotonicity (Back): Remove indices from the back that
    // correspond to elements smaller than or equal to the current element.
    while (!dq.empty() && nums[dq.back()] <= nums[high]) dq.pop_back();

    // 3. Add Current Element: Add the current index to the back of the deque.
    dq.push_back(high);

    // 4. Check if Window is Full and Add to Result:
    if (high - low + 1 == k) {
      ans.emplace_back(nums[dq.front()]);
      low++;  // Slide the window forward by incrementing the left pointer.
    }

    high++;  // Always expand the window by incrementing the right pointer.
  }

  return ans;
}
