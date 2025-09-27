/*
 * Problem: Find Permutation 2 (ABC #425)
 * Rating: Beginner-B
 * Link: https://atcoder.jp/contests/abc425/tasks/abc425_b
 *
 * Approach: The problem asks us to complete a partial permutation. We can solve
 *           this by first checking for invalid conditions and then greedily
 *           filling in the missing elements.
 *
 *           1.  **Validation:** A valid permutation of `1...N` cannot have
 *               duplicates or numbers greater than `N`. We can iterate through
 *               the input array once to check for these conditions. If either
 *               is found, no solution exists.
 *           2.  **Track Available Numbers:** We use a `std::set` to keep track
 *               of all numbers from `1` to `N` that are not yet used in the
 *               given partial permutation.
 *           3.  **Fill Gaps:** We create a result array. First, we place all
 *               the known numbers (non `-1` values) from the input into the
 *               result array and remove them from our set of available
 *               numbers.
 *           4.  Then, we iterate through the result array again. For any
 *               position that is still a placeholder (`-1`), we fill it with
 *               the smallest available number from our set.
 *
 * Time Complexity: O(N log N) due to set operations.
 * Space Complexity: O(N) for the map and set.
 */

#include <algorithm>
#include <iostream>
#include <set>
#include <unordered_map>
#include <vector>

using namespace std;
using ll = long long;
using vll = vector<ll>;
using umpi = unordered_map<int, int>;
using si = set<int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  ll n;
  cin >> n;

  vll a(n);
  umpi mp;
  bool duplicates = false;
  ll maxElement = 0;
  for (int i = 0; i < n; i++) {
    cin >> a[i];

    maxElement = max(maxElement, a[i]);
    mp[a[i]]++;
    if (a[i] != -1 && mp[a[i]] > 1) duplicates = true;
  }

  // A valid permutation cannot have duplicates or elements > n.
  if (duplicates || maxElement > n) {
    cout << "No\n";
  } else {
    // Find all numbers from 1 to n that are available to use.
    si st;
    for (int i = 1; i <= n; i++) {
      st.insert(i);
    }

    vll ans(n, -1);
    // Place the known numbers and remove them from the available set.
    for (int i = 0; i < n; i++) {
      if (a[i] != -1) {
        ans[i] = a[i];
        st.erase(a[i]);
      }
    }

    // Fill in the -1 gaps with the smallest available numbers.
    for (int i = 0; i < n; i++) {
      if (ans[i] == -1) {
        ans[i] = *st.begin();
        st.erase(ans[i]);
      }
    }

    cout << "Yes\n";
    for (ll i : ans) {
      cout << i << " ";
    }
    cout << "\n";
  }

  return 0;
}
