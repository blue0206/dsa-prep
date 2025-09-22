/*
 * Problem: Largest Rectangle in Histogram (LeetCode #84)
 * Link:
 * https://leetcode.com/problems/largest-rectangle-in-histogram/description/
 */
#include <algorithm>
#include <iostream>
#include <stack>
#include <vector>

using namespace std;

/**
 * Approach: For each bar `i`, the largest rectangle that can be formed with
 *           `heights[i]` as the smallest bar is determined by the first bar to
 *           its left that is smaller (`pse`) and the first bar to its right
 *           that is smaller (`nse`). The width of this rectangle is `nse[i] -
 *           pse[i] - 1`. This approach uses two monotonic stacks in two
 *           separate passes to pre-compute the `pse` and `nse` arrays for all
 *           bars. A final third pass calculates the area for each bar and
 *           finds the maximum.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int largestRectangleArea(const vector<int>& heights);

/**
 * Approach: This is an optimized approach using a single pass and one monotonic
 *           stack. The stack stores indices of bars in increasing height
 *           order. When we encounter a bar `heights[i]` that is smaller than
 *           the bar at the stack's top, it means we've found the "next smaller
 *           element" (`i`) for the bar at the stack's top. We can then pop the
 *           stack. The "previous smaller element" for the popped bar is the new
 *           element at the top of the stack. With these boundaries, we can
 *           calculate the area and update the maximum. A sentinel value (0) is
 *           added to the end of the heights array to ensure all bars are
 *           processed.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int singlePassApproach(vector<int> heights);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> heights(n);
    for (int i = 0; i < n; i++) cin >> heights[i];

    cout << "Input Array: [ ";
    for (int i : heights) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Three-Pass Approach: " << largestRectangleArea(heights) << endl;
    cout << "Single-Pass Approach: " << singlePassApproach(heights) << endl;

    cout << endl;
  }

  return 0;
}

int largestRectangleArea(const vector<int>& heights) {
  vector<int> pse(heights.size()), nse(heights.size());
  stack<int> st1, st2;

  for (int i = 0; i < heights.size(); i++) {
    while (!st1.empty() && heights[st1.top()] >= heights[i]) st1.pop();

    pse[i] = (st1.empty()) ? -1 : st1.top();
    st1.push(i);
  }
  for (int i = heights.size() - 1; i >= 0; i--) {
    while (!st2.empty() && heights[st2.top()] >= heights[i]) st2.pop();

    nse[i] = (st2.empty()) ? heights.size() : st2.top();
    st2.push(i);
  }

  int maxArea = 0;
  for (int i = 0; i < heights.size(); i++) {
    int w = nse[i] - pse[i] - 1;
    int area = w * heights[i];
    maxArea = max(maxArea, area);
  }

  return maxArea;
}

int singlePassApproach(vector<int> heights) {
  int n = heights.size() + 1;
  int maxArea = 0;

  // Add a sentinel bar of height 0 to process all remaining bars in the stack.
  heights.emplace_back(0);
  stack<int> st;
  for (int i = 0; i < n; i++) {
    while (!st.empty() && heights[st.top()] >= heights[i]) {
      int height = heights[st.top()];
      st.pop();

      int pse = (st.empty()) ? -1 : st.top();
      int width = i - pse - 1;

      int area = height * width;
      maxArea = max(maxArea, area);
    }
    st.push(i);
  }

  return maxArea;
}
