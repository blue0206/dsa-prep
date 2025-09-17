/*
 * Problem: Build an Array With Stack Operations (LeetCode #1441)
 * Link:
 * https://leetcode.com/problems/build-an-array-with-stack-operations/description/
 *
 * Approach: This problem can be solved by simulating the build process. We can
 *           iterate through the stream of numbers from 1 to `n` and compare
 *           each number with the elements of the `target` array.
 *
 *           We use a pointer `index` to keep track of our position in the
 *           `target` array. For each number `i` from the stream (1 to `n`):
 *           - If `i` is equal to `target[index]`, it means we need this number.
 *             We perform a "Push" and advance our `index`.
 *           - If `i` is not equal to `target[index]`, it means we must discard
 *             `i`. We do this by performing a "Push" followed by a "Pop".
 *           The process stops as soon as the target array is fully built.
 *
 * Time Complexity: O(N), where N is the largest element in the target array.
 * Space Complexity: O(N) for the output array.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> buildArray(vector<int>& target, int n);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, x;
    cin >> n >> x;

    vector<int> nums(x);
    for (int i = 0; i < x; i++) cin >> nums[i];

    cout << "n: " << n << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<string> ans = buildArray(nums, n);

    cout << "Output: [ ";
    for (auto i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<string> buildArray(vector<int>& target, int n) {
  vector<string> ans;
  // `index` points to the current element we are trying to match in the target
  // array.
  int index = 0;
  // `i` represents the numbers being read from the stream [1, 2, ..., n].
  for (int i = 1; i <= n && index < target.size(); i++) {
    if (i == target[index]) {
      // The current number `i` matches the target, so we push it and keep it.
      ans.emplace_back("Push");
      index++;
    } else {
      // The current number `i` is not needed, so we push and immediately pop.
      ans.emplace_back("Push");
      ans.emplace_back("Pop");
    }
  }

  return ans;
}
