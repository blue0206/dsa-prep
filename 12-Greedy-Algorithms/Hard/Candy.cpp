/*
 * Problem: Candy (LeetCode #135)
 * Link: https://leetcode.com/problems/candy/description/
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

/**
 * Approach: This is the standard two-pass greedy approach. The problem has two
 *           conditions that must be met simultaneously. We can satisfy them by
 *           iterating twice.
 *           1.  **Left-to-Right Pass:** Iterate from left to right, ensuring
 *               that any child with a higher rating than their left neighbor
 *               gets one more candy than that neighbor. This pass handles all
 *               "uphill" slopes.
 *           2.  **Right-to-Left Pass:** Iterate from right to left, ensuring
 *               that any child with a higher rating than their right neighbor
 *               gets more candy. We take the maximum of the current candy
 *               count and the right neighbor's count plus one. This handles
 *               "downhill" slopes without violating the first condition.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(N)
 */
int candy(const vector<int>& ratings);

/**
 * Approach: This is a highly optimized single-pass approach that calculates
 *           the total candies by tracking the length of the current uphill and
 *           downhill slopes. It views the ratings array as a sequence of
 *           mountains and valleys.
 *           -   **Uphill:** When the rating increases, we are on an uphill
 *               slope. The number of candies needed is `uphill_length + 1`.
 *           -   **Downhill:** When the rating decreases, we are on a downhill
 *               slope. The number of candies needed is `downhill_length`.
 *           -   **Peak:** A special adjustment is needed at the peak of a
 *               mountain. The peak child must have more candies than both its
 *               left and right neighbors. The logic `peak >= downhill` checks
 *               if the uphill slope leading to the peak was long enough to
 *               satisfy the downhill requirement without needing an extra
 *               candy at the peak.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int optimalApproach(const vector<int>& ratings);

/**
 * Approach: This is approach identifies contiguous monotonic
 *           (uphill or downhill) segments and calculates the candies needed
 *           for each segment.
 *           1.  It iterates through the ratings, identifying the end of each
 *               uphill or downhill slope.
 *           2.  For a slope of length `len`, the candies required form an
 *               arithmetic progression `1 + 2 + ... + len`, which sums to
 *               `len * (len + 1) / 2`. This sum is added to the total.
 *           3.  A complex set of rules is used to adjust the total count at
 *               the junction between two segments (the "peak" or "valley") to
 *               avoid double-counting and ensure the rules are met.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */
int myApproach(const vector<int>& ratings);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> ratings(n);
    for (int i = 0; i < n; i++) cin >> ratings[i];

    cout << "Ratings: [ ";
    for (int i : ratings) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Candies (Good Approach): " << candy(ratings) << endl;
    cout << "Candies (Optimal Approach): " << optimalApproach(ratings) << endl;
    cout << "Candies (My Approach): " << myApproach(ratings) << endl;

    cout << endl;
  }

  return 0;
}

int candy(const vector<int>& ratings) {
  int n = ratings.size();
  if (n <= 1) return n;

  vector<int> candies(n, 1);

  // Left-to-right pass for the ascending slope condition.
  for (int i = 1; i < n; i++) {
    if (ratings[i] > ratings[i - 1]) {
      candies[i] = candies[i - 1] + 1;
    }
  }

  // Right-to-left pass for the descending slope condition.
  for (int i = n - 2; i >= 0; i--) {
    if (ratings[i] > ratings[i + 1]) {
      candies[i] = max(candies[i], candies[i + 1] + 1);
    }
  }

  return accumulate(candies.begin(), candies.end(), 0);
}

int optimalApproach(const vector<int>& ratings) {
  int n = ratings.size();
  if (n == 1) return 1;

  int uphill = 0;
  int downhill = 0;
  int candies = 1;
  int peak = 0;
  for (int i = 1; i < n; i++) {
    if (ratings[i] > ratings[i - 1]) {
      uphill++;
      downhill = 0;
      peak = uphill;
      candies += (uphill + 1);
    } else if (ratings[i] < ratings[i - 1]) {
      downhill++;
      uphill = 0;
      // Add candies for the downhill slope.
      // An extra candy is needed at the peak if the downhill is longer.
      candies += (downhill + (peak >= downhill ? 0 : 1));
    } else {
      uphill = 0;
      downhill = 0;
      peak = 0;
      candies++;
    }
  }

  return candies;
}

int myApproach(const vector<int>& ratings) {
  int n = ratings.size();
  if (n == 1) return 1;

  int totalCandies = 0;
  int low = 0;
  int high = 1;
  int prevLen = 0;
  bool prevAsc = true;
  bool reset = false;
  while (high < n) {
    if (ratings[high] > ratings[high - 1]) {
      while (high < n && ratings[high] > ratings[high - 1]) high++;
    } else if (ratings[high] < ratings[high - 1]) {
      while (high < n && ratings[high] < ratings[high - 1]) high++;
    } else {
      if (low == 0) {
        totalCandies++;
      }
      high++;
      totalCandies++;
      low = high - 1;
      reset = true;
      continue;
    }

    int len = high - low;
    totalCandies += ((len * (len + 1)) / 2);
    if (reset) {
      totalCandies -= 1;
    } else if (prevLen > len) {
      totalCandies -= (prevAsc) ? len : 1;
    } else {
      totalCandies -= (prevAsc) ? prevLen : 1;
    }
    if (ratings[low] <= ratings[high - 1]) {
      prevAsc = true;
    } else {
      prevAsc = false;
    }
    low = high - 1;
    prevLen = len;
    reset = false;
  }

  return totalCandies;
}
