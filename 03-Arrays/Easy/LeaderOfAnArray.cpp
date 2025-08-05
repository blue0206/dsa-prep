/*
 * Problem: Leader of an Array (CodeChef)
 * Link:
 * https://www.codechef.com/learn/course/arrays/ARRAYS02/problems/DSAAGP11?tab=statement
 *
 * Approach:Iterate from the right and keep track of maximum element. Store the
 *          element greater than current maximum element as it is the leader.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N) for storing leaders.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void printLeaders(vector<int>& arr) {
  int maxElement = INT_MIN;
  vector<int> ans;

  for (int i = arr.size() - 1; i >= 0; i--) {
    if (arr[i] > maxElement) {
      maxElement = arr[i];
      ans.push_back(arr[i]);
    }
  }

  reverse(ans.begin(), ans.end());

  cout << "Leaders: [ ";
  for (auto i : ans) {
    cout << i << " ";
  }
  cout << "]" << endl;
}

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

    printLeaders(nums);

    cout << endl;
  }

  return 0;
}
