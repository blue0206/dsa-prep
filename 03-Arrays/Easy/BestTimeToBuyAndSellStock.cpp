/*
 * Problem: Best Time to Buy and Sell Stock (LeetCode #121)
 * Link:
 * https://leetcode.com/problems/best-time-to-buy-and-sell-stock/description/
 *
 * Approach:We know that profit = selling price - buying price.
 *          Initialize variables to keep track of minimum element (which should
 *          be our ideal buying price, initialized at value at 0th index) and
 *          the maximum profit.
 *
 *          Iterate through the array and find the profit at each iteration by
 *          taking current element as selling price and minimum element as
 *          buying price. Update the maximum profit if the current profit is
 *          greater.
 *          Also, update the minimum element is current element is smaller.
 *          This works because for each day (or index), we can only buy a stock
 *          before we sell it. Therefore, since buying comes before selling,
 *          the minimum element ALWAYS comes before the iteration giving
 *          maximum profit, i.e., the maximum element in the array range after
 *          it.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxProfit(vector<int>& prices) {
  int profit = 0;
  int minElement = prices[0];

  for (int i = 0; i < prices.size(); i++) {
    int currentProfit = prices[i] - minElement;
    profit = max(profit, currentProfit);
    minElement = min(minElement, prices[i]);
  }

  return profit;
}

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> prices(n);
    for (int i = 0; i < n; i++) cin >> prices[i];

    cout << "Array: [ ";
    for (auto i : prices) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Achievable Profit: " << maxProfit(prices) << endl;

    cout << endl;
  }

  return 0;
}
