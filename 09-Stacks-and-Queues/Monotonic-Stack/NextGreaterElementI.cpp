/*
 * Problem: Next Greater Element I (LeetCode #496)
 * Link: https://leetcode.com/problems/next-greater-element-i/description/
 *
 * Approach: This problem can be solved efficiently by first pre-computing the
 *           "next greater element" for every number in `nums2` and storing the
 *           results in a hash map. A monotonic stack is the ideal tool for
 *           this pre-computation.
 *
 *           1.  **Pre-computation with Monotonic Stack:**
 *               -   Iterate through `nums2` from right to left.
 *               -   Use a stack to maintain a monotonically decreasing sequence
 *                   of elements.
 *               -   For each element `x` from `nums2`, pop elements from the
 *                   stack that are less than or equal to `x`.
 *               -   The element now at the top of the stack is the next greater
 *                   element for `x`. If the stack is empty, `x` has no next
 *                   greater element.
 *               -   Store this mapping in a hash map: `map[x] = next_greater`.
 *               -   Push `x` onto the stack to maintain the monotonic property.
 *           2.  **Result Generation:** Iterate through `nums1`. For each
 *               element, look up its next greater element in the pre-computed
 *               hash map and add it to the result array.
 *
 * Time Complexity: O(N + M)
 * Space Complexity: O(M)
 */

#include <algorithm>
#include <iostream>
#include <stack>
#include <unordered_map>
#include <vector>

using namespace std;

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<int> nums1(n), nums2(m);
    for (int i = 0; i < n; i++) cin >> nums1[i];
    for (int i = 0; i < m; i++) cin >> nums2[i];

    cout << "nums1: [ ";
    for (int i : nums1) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "nums2: [ ";
    for (int i : nums2) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = nextGreaterElement(nums1, nums2);

    cout << "Result: [ ";
    for (int i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<int> nextGreaterElement(vector<int>& nums1, vector<int>& nums2) {
  stack<int> nge;
  unordered_map<int, int> mp;

  for (int i = nums2.size() - 1; i >= 0; i--) {
    // While stack is not empty and the current element is greater than the
    // stack's top, pop from the stack. This maintains the monotonic
    // (decreasing) property.
    while (!nge.empty() && nums2[i] >= nge.top()) {
      nge.pop();
    }
    // If the stack is empty, there is no greater element to the right.
    mp[nums2[i]] = -1;
    if (!nge.empty()) {
      // The top of the stack is the next greater element.
      mp[nums2[i]] = nge.top();
    }

    nge.push(nums2[i]);
  }

  // Build the result array using the pre-computed map.
  vector<int> ans;
  for (int i = 0; i < nums1.size(); i++) {
    ans.emplace_back(mp[nums1[i]]);
  }

  return ans;
}
