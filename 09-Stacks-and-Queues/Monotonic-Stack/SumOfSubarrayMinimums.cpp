/*
 * Problem: Sum of Subarray Minimums (LeetCode #907)
 * Link: https://leetcode.com/problems/sum-of-subarray-minimums/description/
 *
 * Approach: A brute-force O(N^2) approach is too slow. The key insight is to
 *           reframe the problem: for each element `arr[i]`, how many subarrays
 *           have `arr[i]` as their minimum element? The total sum is then the
 *           sum of `arr[i] * count` for all `i`.
 *
 *           To find the count for `arr[i]`, we need to find the boundaries of
 *           subarrays where it is the minimum. This requires finding:
 *           1.  `pse[i]`: The index of the first element to the left of
 *               `i` that is strictly smaller than `arr[i]`.
 *           2.  `nse[i]`: The index of the first element to the right of
 *               `i` that is less than or equal to `arr[i]`.
 *
 *           A subarray with `arr[i]` as its minimum must start at an index `j`
 *           where `pse[i] < j <= i` and end at an index `k` where
 *           `i <= k < nse[i]`.
 *           - Number of choices for start index `j`: `i - pse[i]`
 *           - Number of choices for end index `k`: `nse[i] - i`
 *           The total count for `arr[i]` is `(i - pse[i]) * (nse[i] - i)`.
 *
 *           We can find `pse` and `nse` arrays efficiently in O(N) using two
 *           passes with a monotonic stack. The use of strict vs. non-strict
 *           inequalities is crucial to handle duplicates correctly.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

int sumSubarrayMins(const vector<int>& arr);

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

    cout << "Sum of Subarray Minimums: " << sumSubarrayMins(arr) << endl;

    cout << endl;
  }

  return 0;
}

int sumSubarrayMins(const vector<int>& arr) {
  const long long m = 1e9 + 7;

  int n = arr.size();
  vector<int> nse(n), pse(n);
  stack<int> st1, st2;

  for (int i = 0; i < n; i++) {
    while (!st1.empty() && arr[st1.top()] >= arr[i]) st1.pop();

    pse[i] = (st1.empty()) ? -1 : st1.top();
    st1.push(i);
  }
  for (int i = n - 1; i >= 0; i--) {
    while (!st2.empty() && arr[st2.top()] > arr[i]) st2.pop();

    nse[i] = (st2.empty()) ? n : st2.top();
    st2.push(i);
  }

  long long sum = 0;
  for (int i = 0; i < n; i++) {
    long long subarrays = (((i - pse[i]) % m) * ((nse[i] - i) % m)) % m;
    long long res = ((arr[i] % m) * (subarrays % m)) % m;
    sum = ((sum % m) + (res % m)) % m;
  }

  return sum;
}
