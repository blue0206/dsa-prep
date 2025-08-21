/*
 * Problem: Minimize Max Distance to Gas Station
 * Link:
 * https://www.naukri.com/code360/problems/minimise-max-distance_7541449?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <cmath>
#include <iomanip>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using ld = long double;

/**
 * Approach: This is a greedy simulation. For each of the `k` stations to be
 *           placed, we iterate through all existing segments between stations.
 *           We find the segment with the currently largest distance and place a
 *           new station in its middle, effectively splitting it. We repeat
 *           this `k` times. To keep track of how many stations are in each
 *           original segment, we use a counter array.
 *
 * Time Complexity: O(k * N)
 * Space Complexity: O(N)
 */
ld bruteForceApproach(vector<int> stations, int k);

/**
 * Approach: This is an optimized version of the brute-force approach. Instead
 *           of linearly scanning to find the largest segment in each step, we
 *           use a max-priority queue. The priority queue stores pairs of
 *           `{current_distance, segment_index}`. In each of the `k` steps, we
 *           extract the segment with the max distance, place a station in it
 *           (by incrementing a counter for that segment), calculate the new,
 *           smaller distance for that segment, and insert it back into the
 *           priority queue.
 *
 * Time Complexity: O((N+k) * logN)
 * Space Complexity: O(N)
 */
ld pqApproach(vector<int> stations, int k);

/**
 * Approach: This is a "Binary Search on Answer" approach. The answer (the
 *           minimum possible value for the maximum distance) must lie in a
 *           range.
 *           1.  **Search Space**: The smallest possible answer is 0. The
 *               largest is the maximum distance between any two adjacent
 *               stations initially.
 *           2.  **Binary Search**: We binary search on this range of possible
 *               distances. For a given distance `d` (our `mid`), we check if
 *               it's achievable with at most `k` new stations.
 *           3.  **Feasibility Check (`possible` function)**: For a given max
 *               distance `d`, we calculate how many new stations are required.
 *           4.  **Narrowing Down**: If distance `d` is possible, we try for an
 *               even smaller distance (`high = mid`). If not, we need to allow
 *               a larger distance (`low = mid`).
 *
 * Time Complexity: O(N * log(Range/precision))
 * Space Complexity: O(1)
 */
ld optimalApproach(vector<int> stations, int k);
bool possible(vector<int> &stations, int k, ld mid);

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

    cout << fixed << setprecision(6);

    cout << "Minimum Possible Maximum Distance (Brute-Force Approach): "
         << bruteForceApproach(nums, k) << endl;

    cout << "Minimum Possible Maximum Distance (Priority-Queue Approach): "
         << pqApproach(nums, k) << endl;

    cout << "Minimum Possible Maximum Distance (Optimal Approach): "
         << optimalApproach(nums, k) << endl;

    cout << endl;
  }

  return 0;
}

ld bruteForceApproach(vector<int> stations, int k) {
  vector<int> ans(stations.size(), 0);

  // Place k stations one by one.
  for (int stationsToPlace = 1; stationsToPlace <= k; stationsToPlace++) {
    ld maxDistance = 0;
    int maxIndex = 0;
    for (int j = 0; j < stations.size() - 1; j++) {
      ld diff = stations[j + 1] - stations[j];
      ld distance = diff / ((ld)(ans[j] + 1));
      if (distance > maxDistance) {
        maxDistance = distance;
        maxIndex = j;
      }
    }
    ans[maxIndex]++;
  }

  ld maxDistance = 0;
  for (int i = 0; i < stations.size() - 1; i++) {
    ld diff = stations[i + 1] - stations[i];
    ld distance = diff / ((ld)(ans[i] + 1));

    maxDistance = max(maxDistance, distance);
  }

  return maxDistance;
}

ld pqApproach(vector<int> stations, int k) {
  vector<int> ans(stations.size(), 0);
  priority_queue<pair<ld, int> > pq;

  for (int i = 0; i < stations.size() - 1; i++) {
    ld diff = stations[i + 1] - stations[i];
    pq.push({diff, i});
  }

  for (int stationsToPlace = 1; stationsToPlace <= k; stationsToPlace++) {
    int maxIndex = pq.top().second;
    ans[maxIndex]++;
    pq.pop();
    ld diff = stations[maxIndex + 1] - stations[maxIndex];
    ld distance = diff / ((ld)(ans[maxIndex] + 1));
    pq.push({distance, maxIndex});
  }

  return pq.top().first;
}

//-----------------------------OPTIMAL APPROACH---------------------------------
ld optimalApproach(vector<int> stations, int k) {
  ld low = 0;
  ld high = 0;
  for (int i = 0; i < stations.size() - 1; i++) {
    ld distance = stations[i + 1] - stations[i];
    if (distance > high) high = distance;
  }

  // Binary search for the answer with a certain precision.
  ld maxDiff = 1e-7;
  while (high - low > maxDiff) {
    ld mid = low + (high - low) / (2.0);

    if (possible(stations, k, mid)) {
      high = mid;
    } else {
      low = mid;
    }
  }

  return high;
}

bool possible(vector<int> &stations, int k, ld mid) {
  int totalStationsPlaced = 0;

  for (int i = 0; i < stations.size() - 1; i++) {
    ld diff = stations[i + 1] - stations[i];
    // Number of new stations needed in this segment is ceil(diff/mid) - 1
    totalStationsPlaced += ceil(diff / mid) - 1;
  }

  return totalStationsPlaced <= k;
}
