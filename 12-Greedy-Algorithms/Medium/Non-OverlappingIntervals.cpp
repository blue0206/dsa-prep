/*
 * Problem: Non-overlapping Intervals (LeetCode #435)
 * Link: https://leetcode.com/problems/non-overlapping-intervals/description/
 *
 * Approach: This problem asks for the minimum number of intervals to remove to
 *           make the rest non-overlapping. This is equivalent to finding the
 *           maximum number of non-overlapping intervals we can keep. The
 *           greedy choice is to always select the interval that finishes
 *           earliest, as this leaves the most room for subsequent intervals.
 *
 *           1.  **Sort by End Time:** The crucial step is to sort the intervals
 *               based on their end times in ascending order.
 *           2.  **Greedy Selection:** Select the first interval (which now has
 *               the earliest end time). Then, iterate through the rest. If the
 *               start of the current interval is greater than or equal to the
 *               end of the previously selected interval, it means they don't
 *               overlap. We can keep this interval and update our "last end
 *               time".
 *           3.  **Calculate Removals:** The number of intervals to remove is
 *               the total number of intervals minus the count of
 *               non-overlapping intervals we were able to keep.
 *
 * Time Complexity: O(N log N) due to sorting.
 * Space Complexity: O(log N) or O(N) depending on the sort implementation.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int eraseOverlapIntervals(vector<vector<int>>& intervals);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<int>> intervals(n, vector<int>(2));
    for (int i = 0; i < n; i++) {
      cin >> intervals[i][0] >> intervals[i][1];
    }

    cout << "Intervals: [ ";
    for (auto rows : intervals) {
      cout << "[ " << rows[0] << ", " << rows[1] << " ] ";
    }
    cout << "]" << endl;

    cout << "Overlapping Intervals: " << eraseOverlapIntervals(intervals)
         << endl;
  }

  return 0;
}

int eraseOverlapIntervals(vector<vector<int>>& intervals) {
  if (intervals.empty()) {
    return 0;
  }

  // Sort intervals based on their end times.
  sort(intervals.begin(), intervals.end(),
       [](const vector<int>& a, const vector<int>& b) { return a[1] < b[1]; });

  // The first interval is always kept.
  int nonOverlappingCount = 1;
  int prevEnd = intervals[0][1];
  for (int i = 1; i < intervals.size(); i++) {
    // If the current interval starts after or at the same time the previous one
    // ended, we can keep it.
    if (intervals[i][0] >= prevEnd) {
      nonOverlappingCount++;
      prevEnd = intervals[i][1];
    }
  }

  // The number to remove is the total minus the number we kept.
  return intervals.size() - nonOverlappingCount;
}
