/*
 * Problem: Replace Elements with Greatest Element on Right Side(LeetCode #1299)
 * Link:
 * https://leetcode.com/problems/replace-elements-with-greatest-element-on-right-side/description/
 *
 * Approach:Iterate from the right and keep track of maximum element.
 *          Store the maximum element for each index and when an element greater
 *          than the maxima is found, update the maxima. This is done in a
 *          single pass from right to left, modifying the array in-place.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

vector<int> replaceElements(vector<int>& arr) {
  int maxElement = -1;
  for (int i = arr.size() - 1; i >= 0; i--) {
    int temp = arr[i];
    arr[i] = maxElement;
    maxElement = max(maxElement, temp);
  }

  return arr;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> arr(n);
    for (int i = 0; i < n; i++) cin >> arr[i];

    cout << "Array: [ ";
    for (auto i : arr) {
      cout << i << " ";
    }
    cout << "]" << endl;

    vector<int> ans = replaceElements(arr);

    cout << "Processed Array: [ ";
    for (auto i : ans) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}
