/*
 * Problem: Lemonade Change (LeetCode #860)
 * Link: https://leetcode.com/problems/lemonade-change/description/
 *
 * Approach: This is a greedy problem where we process customers one by one and
 *           check if we can provide the correct change at each step. We only
 *           need to keep track of the number of $5 and $10 bills we have.
 *
 *           1.  **Iterate through Bills:** Process each bill from the customers
 *               in order.
 *           2.  **$5 Bill:** If the customer pays with a $5 bill, we simply
 *               accept it and increment our count of $5 bills. No change is
 *               needed.
 *           3.  **$10 Bill:** If the customer pays with a $10 bill, we need to
 *               give $5 in change. We must have at least one $5 bill. If we
 *               do, we use it for change and increment our count of $10 bills.
 *           4.  **$20 Bill:** If the customer pays with a $20 bill, we need to
 *               give $15 in change. The greedy choice is to first try to give
 *               back one $10 bill and one $5 bill. This is optimal because it
 *               preserves our more versatile $5 bills. If we can't do that, we
 *               try to give back three $5 bills. If neither is possible, we
 *               cannot make change.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

bool lemonadeChange(const vector<int>& bills);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> bills(n);
    for (int i = 0; i < n; i++) cin >> bills[i];

    cout << "Bills: [ ";
    for (int i : bills) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Result: " << (lemonadeChange(bills) ? "True" : "False") << endl;
  }

  return 0;
}

bool lemonadeChange(vector<int>& bills) {
  unordered_map<int, int> mp;

  for (int i = 0; i < bills.size(); i++) {
    mp[bills[i]]++;

    if (bills[i] == 20) {
      if (mp[5] > 0 && mp[10] > 0) {
        mp[5]--;
        mp[10]--;
      } else if (mp[5] > 2) {
        mp[5] -= 3;
      } else {
        return false;
      }
      mp[20]--;
    } else if (bills[i] == 10) {
      if (mp[5] > 0) {
        mp[5]--;
      } else {
        return false;
      }
    }
  }

  return true;
}
