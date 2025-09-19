/*
 * Problem: Next Greater Element II (LeetCode #503)
 * Link: https://leetcode.com/problems/next-greater-element-ii/description/
 *
 * Approach: This problem extends the "Next Greater Element" concept to a
 *           circular array. The monotonic stack pattern is still the ideal
 *           approach. To handle the circularity, we can simulate iterating
 *           through the array twice.
 *
 *           1.  **Simulate a Doubled Array:** Instead of actually creating a
 *               new array of size `2*n`, we can loop from `i = 2*n - 1` down to
 *               `0`. The index into the original `nums` array is then `i % n`.
 *               This effectively processes the array `nums` concatenated with
 *               itself.
 *           2.  **Monotonic Stack:** We use a stack to maintain a monotonically
 *               decreasing sequence of elements.
 *               -   For each element `x = nums[i % n]`, pop elements from the
 *                   stack that are less than or equal to `x`.
 *               -   The element now at the top of the stack is the next greater
 *                   element.
 *               -   We only update our answer array `ans` when `i < n`, which
 *                   corresponds to the actual elements of the original array.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

vector<int> nextGreaterElements(vector<int>& nums);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = nextGreaterElements(nums);

    cout << "Result: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> nextGreaterElements(vector<int>& nums) {
  int n = nums.size();
  stack<int> nge;
  vector<int> ans(n, -1);
  for (int i = 2 * n - 1; i >= 0; i--) {
    // Use modulo to wrap around the array, simulating a circular traversal.
    int index = i % n;

    // Pop elements from the stack that are smaller than or equal to the current
    // element to maintain the monotonic decreasing property.
    while (!nge.empty() && nge.top() <= nums[index]) {
      nge.pop();
    }

    // We only care about setting the answer for the original array elements,
    // which corresponds to the second half of our conceptual doubled array.
    if (i < n && !nge.empty()) {
      ans[i] = nge.top();
    }
    nge.push(nums[index]);
  }

  return ans;
}
