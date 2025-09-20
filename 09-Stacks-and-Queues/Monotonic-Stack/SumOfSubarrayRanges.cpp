/*
 * Problem: Sum of Subarray Ranges (LeetCode #2104)
 * Link: https://leetcode.com/problems/sum-of-subarray-ranges/description/
 *
 * Approach: The sum of all subarray ranges can be expressed as:
 *           Sum(max(subarray) - min(subarray)) for all subarrays.
 *           This can be rewritten as:
 *           Sum(max(subarray)) - Sum(min(subarray)).
 *
 *           This breaks the problem into two independent subproblems:
 *           1.  **Sum of Subarray Maximums:** For each element `nums[i]`, we
 *               calculate how many subarrays have `nums[i]` as their maximum.
 *               This is done by finding the "previous greater element" and
 *               "next greater element" using a monotonic stack.
 *           2.  **Sum of Subarray Minimums:** Similarly, for each `nums[i]`,
 *               we calculate how many subarrays have it as their minimum by
 *               finding the "previous smaller element" and "next smaller
 *               element".
 *
 *           The final answer is the difference between these two sums. This
 *           approach is a direct application of the logic from "Sum of
 *           Subarray Minimums" (LeetCode #907).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;
using ll = long long;

ll subArrayRanges(vector<int>& nums);
ll getMaxSum(vector<int>& nums, int n);
ll getMinSum(vector<int>& nums, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Input Array: [ ";
    for (int i : arr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Sum of Subarray Ranges: " << subArrayRanges(arr) << endl;

    cout << endl;
  }

  return 0;
}

ll subArrayRanges(vector<int>& nums) {
  ll maxSum = getMaxSum(nums, nums.size());
  ll minSum = getMinSum(nums, nums.size());

  return maxSum - minSum;
}

ll getMaxSum(vector<int>& nums, int n) {
  vector<int> nge(n), pge(n);
  stack<int> st1, st2;
  for (int i = 0; i < n; i++) {
    while (!st1.empty() && nums[st1.top()] <= nums[i]) st1.pop();

    pge[i] = (st1.empty()) ? -1 : st1.top();
    st1.push(i);
  }
  for (int i = n - 1; i >= 0; i--) {
    while (!st2.empty() && nums[st2.top()] < nums[i]) st2.pop();

    nge[i] = (st2.empty()) ? n : st2.top();
    st2.push(i);
  }

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    ll leftSize = i - pge[i];
    ll rightSize = nge[i] - i;

    sum += (nums[i] * leftSize * rightSize);
  }

  return sum;
}

ll getMinSum(vector<int>& nums, int n) {
  vector<int> nse(n), pse(n);
  stack<int> st1, st2;

  for (int i = 0; i < n; i++) {
    while (!st1.empty() && nums[st1.top()] >= nums[i]) st1.pop();

    pse[i] = (st1.empty()) ? -1 : st1.top();
    st1.push(i);
  }
  for (int i = n - 1; i >= 0; i--) {
    while (!st2.empty() && nums[st2.top()] > nums[i]) st2.pop();

    nse[i] = (st2.empty()) ? n : st2.top();
    st2.push(i);
  }

  ll sum = 0;
  for (int i = 0; i < n; i++) {
    ll leftSize = i - pse[i];
    ll rightSize = nse[i] - i;

    sum += (nums[i] * leftSize * rightSize);
  }

  return sum;
}
