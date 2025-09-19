/*
 * Problem: Trapping Rain Water (LeetCode #42)
 * Link: https://leetcode.com/problems/trapping-rain-water/description/
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * Approach: The brute-force approach is slow because we repeatedly scan for
 *           `leftMax` and `rightMax`. We can optimize this by pre-computing
 *           these values. We create a `prefixMax` array to store the maximum
 *           height up to index `i`, and a `suffixMax` array for the maximum
 *           from index `i` onwards. Then, in a single pass, we can calculate
 *           the trapped water at each bar using these pre-computed arrays.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int affixMaxApproach(const vector<int>& height);

/**
 * Approach: This approach calculates the trapped water by finding bounded
 *           regions using a monotonically decreasing stack of indices. When we
 *           encounter a bar `height[i]` taller than the bar at the stack's
 *           top, we've found a right boundary. We pop the stack, and the popped
 *           bar is the bottom of a potential water trap. The new stack top is
 *           the left boundary. The volume is `height * width`.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int monotonicStackApproach(const vector<int>& height);

/**
 * Approach: This is a space-optimized version of the affix-max approach. We
 *           use two pointers, `left` and `right`, at the ends of the array, and
 *           maintain `leftMax` and `rightMax`. At each step, we compare
 *           `height[left]` and `height[right]`. If `height[left]` is smaller,
 *           we know the water level at the `left` pointer is limited by
 *           `leftMax` (because there's a taller wall at `right`). We add
 *           `leftMax - height[left]` to the answer and move `left` inward. A
 *           similar logic applies if `height[right]` is smaller.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int twoPointerApproach(const vector<int>& height);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> height(n);
    for (int i = 0; i < n; i++) cin >> height[i];

    cout << "Input Array: [ ";
    for (int i : height) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Prefix-Max + Suffix-Max Approach: " << affixMaxApproach(height)
         << endl;
    cout << "Monotonic Stack Approach: " << monotonicStackApproach(height)
         << endl;
    cout << "Two-Pointer Approach: " << twoPointerApproach(height) << endl;

    cout << endl;
  }

  return 0;
}

int affixMaxApproach(const vector<int>& height) {
  int n = height.size();
  if (n <= 2) return 0;
  vector<int> pMax(n, height[0]);
  vector<int> sMax(n, height[n - 1]);

  for (int i = 1; i < n; i++) {
    pMax[i] = max(pMax[i - 1], height[i]);
  }
  for (int i = n - 2; i >= 0; i--) {
    sMax[i] = max(sMax[i + 1], height[i]);
  }

  int res = 0;
  for (int i = 0; i < n; i++) {
    if (pMax[i] > height[i] && sMax[i] > height[i]) {
      res += (min(pMax[i], sMax[i]) - height[i]);
    }
  }

  return res;
}

int monotonicStackApproach(const vector<int>& height) {
  stack<int> st;
  int res = 0;

  for (int i = 0; i < height.size(); i++) {
    while (!st.empty() && height[st.top()] < height[i]) {
      int bottomIndex = st.top();
      st.pop();

      if (st.empty()) break;

      int ht = min(height[st.top()], height[i]) - height[bottomIndex];
      int wd = i - st.top() - 1;
      res += (ht * wd);
    }
    st.push(i);
  }

  return res;
}

int twoPointerApproach(const vector<int>& height) {
  int n = height.size();
  if (n <= 2) return 0;
  int left = 0, right = n - 1;
  int leftMax = 0, rightMax = 0;
  int ans = 0;

  while (left < right) {
    if (height[left] < height[right]) {
      if (height[left] >= leftMax) {
        leftMax = height[left];
      } else {
        ans += leftMax - height[left];
      }
      left++;
    } else {
      if (height[right] >= rightMax) {
        rightMax = height[right];
      } else {
        ans += rightMax - height[right];
      }
      right--;
    }
  }

  return ans;
}
