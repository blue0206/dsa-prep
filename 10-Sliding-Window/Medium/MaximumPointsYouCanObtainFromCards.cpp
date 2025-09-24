/*
 * Problem: Maximum Points You Can Obtain from Cards (LeetCode #1423)
 * Link:
 * https://leetcode.com/problems/maximum-points-you-can-obtain-from-cards/description/
 *
 * Approach: Instead of directly calculating the maximum score from the ends,
 *           this problem can be reframed as finding a contiguous subarray of
 *           size `n - k` with the minimum possible sum. The cards we *don't*
 *           pick will always form a contiguous block in the middle of the
 *           array.
 *
 *           By maximizing the sum of the `k` cards we pick, we are implicitly
 *           minimizing the sum of the `n - k` cards we leave behind. The final
 *           answer is then `total_sum - min_subarray_sum`. We can find the
 *           minimum sum of a fixed-size subarray using a sliding window.
 *
 * Time Complexity: O(N), where N is the number of cards.
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxScore(const vector<int>& cardPoints, int k);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, k;
    cin >> n >> k;

    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "k: " << k << endl;
    cout << "Input Array: [ ";
    for (int i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Points: " << maxScore(nums, k) << endl;
  }

  return 0;
}

int maxScore(const vector<int>& cardPoints, int k) {
  int n = cardPoints.size();
  int windowSize = n - k;

  int totalSum = 0;
  for (int point : cardPoints) {
    totalSum += point;
  }

  // If we must take all cards, the score is the total sum.
  if (windowSize == 0) {
    return totalSum;
  }

  // Find the minimum sum of a subarray of size `windowSize`.
  int windowSum = 0;
  int minWindowSum = INT_MAX;
  int low = 0;
  int high = 0;
  while (high < n) {
    windowSum += cardPoints[high];

    if (high - low + 1 == windowSize) {
      minWindowSum = min(minWindowSum, windowSum);
      windowSum -= cardPoints[low];
      low++;
    }
    high++;
  }

  return totalSum - minWindowSum;
}
