/*
 * Problem: Aggressive Cows
 *
 * Statement: You are given an array with unique elements of stalls[],
 *            which denote the positions of stalls. You are also given an
 *            integer k which denotes the number of aggressive cows.
 *            The task is to assign stalls to k cows such that the minimum
 *            distance between any two of them is the maximum possible.
 *
 * Approach: This is a classic "Binary Search on Answer" problem. We need to
 *           maximize the minimum distance, which suggests an optimization
 *           problem solvable with binary search.
 *           1.  **Sort:** First, sort the stall positions. This is crucial for
 *               the greedy placement strategy in the feasibility check.
 *           2.  **Search Space:** The answer (the minimum distance) must lie
 *               in a range. The minimum possible distance is 1. The maximum
 *               possible distance is `stalls.back() - stalls.front()`.
 *           3.  **Binary Search:** We binary search on this range of distances.
 *               For each `mid` value (a potential minimum distance), we check
 *               if it's possible to place `k` cows with at least that distance
 *               apart.
 *           4.  **Check Feasibility:** The `possible` function greedily places
 *               cows to see if a configuration is valid for the given distance.
 *           5.  **Narrowing Down:** If a distance is possible, we store it as a
 *               potential answer and try for a larger one (`low = mid + 1`).
 *               If not, we need a smaller distance (`high = mid - 1`).
 *
 * Time Complexity: O(N log N + N * log(max_pos))
 * Space Complexity: O(1) auxiliary space.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int aggressiveCows(vector<int>& stalls, int k);
bool possible(vector<int>& stalls, int k, int mid);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Possible Minimum Distance: " << aggressiveCows(nums, k)
         << endl;

    cout << endl;
  }

  return 0;
}

int aggressiveCows(vector<int>& stalls, int k) {
  sort(stalls.begin(), stalls.end());
  int low = 1;
  int high = stalls.back() - stalls.front();
  int ans = 0;

  while (low <= high) {
    int mid = low + (high - low) / 2;

    if (possible(stalls, k, mid)) {
      ans = mid;
      low = mid + 1;
    } else {
      high = mid - 1;
    }
  }

  return ans;
}

bool possible(vector<int>& stalls, int k, int mid) {
  int cowsPlaced = 1;
  int lastPosition = stalls[0];
  for (int i = 1; i < stalls.size(); i++) {
    if (stalls[i] - lastPosition >= mid) {
      cowsPlaced++;
      lastPosition = stalls[i];
    }
  }
  return cowsPlaced >= k;
}
