/*
 * Problem: Fruit Into Baskets (LeetCode #904)
 * Link: https://leetcode.com/problems/fruit-into-baskets/description/
 *
 * Approach: This problem is a variation of "longest substring with at most K
 *           distinct characters," where K=2. We can solve it efficiently using
 *           a sliding window.
 *
 *           1.  **Window and State:** We use two pointers, `low` and `high`, to
 *               define the current window. An `unordered_map` (`basket`) is
 *               used to store the frequency of each type of fruit in the
 *               current window.
 *           2.  **Expansion:** The `high` pointer moves to the right,
 *               expanding the window and adding a new fruit. We update its
 *               count in the `basket`.
 *           3.  **Contraction:** If the number of distinct fruit types in our
 *               `basket` (`basket.size()`) exceeds 2, the window is invalid.
 *               We shrink the window from the left by moving the `low` pointer
 *               and decrementing the count of the fruit at `fruits[low]`. If a
 *               fruit's count drops to zero, we remove it from the map. This
 *               continues until the window is valid again
 *               (`basket.size() <= 2`).
 *           4.  **Update Answer:** After each step, the window is valid, and we
 *               update `maxFruits` with the current window size
 *               (`high - low + 1`).
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

int totalFruit(const vector<int>& fruits);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> fruits(n);
    for (int i = 0; i < n; i++) cin >> fruits[i];

    cout << "Fruits Array: [ ";
    for (int i : fruits) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Maximum Fruits: " << totalFruit(fruits) << endl;
  }

  return 0;
}

int totalFruit(const vector<int>& fruits) {
  unordered_map<int, int> basket;
  int low = 0;
  int high = 0;

  int maxFruits = 0;
  while (high < fruits.size()) {
    basket[fruits[high]]++;

    while (basket.size() > 2) {
      basket[fruits[low]]--;
      if (basket[fruits[low]] == 0) {
        basket.erase(fruits[low]);
      }
      low++;
    }

    maxFruits = max(maxFruits, high - low + 1);

    high++;
  }

  return maxFruits;
}
