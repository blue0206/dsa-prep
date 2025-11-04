/*
 * Problem: Nezuko in the Clearing (Codeforces Div. 3 #2149F)
 * Rating: 1900
 * Link: https://codeforces.com/problemset/problem/2149/F
 *
 * Approach: The problem asks for the minimum total number of moves (`k`) to
 *           survive. The number of damage moves is fixed at `d`. This means
 *           the number of rest moves is `k - d`.
 *           The core insight is that the survivability is monotonic. If we can
 *           survive with `k` total moves, we can also survive with `k+1` moves
 *           (as the extra move can be a rest, increasing health). This allows
 *           us to use binary search on the answer `k`.
 *           For a given `k`, we check if it's possible to survive. To maximize
 *           survival chances, we must minimize the total damage taken. This is
 *           achieved by distributing the `d` damage moves as evenly as
 *           possible among the `k - d + 1` "slots" created by the rest moves.
 *           We calculate the total damage for this optimal distribution and
 *           check if it's less than the total health (initial health `h` plus
 *           health gained from rests).
 *
 * Time Complexity: O(log N)
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>

using namespace std;
using ll = long long;

ll sumN(ll n) { return ((n * (n + 1)) / 2); }

bool possible(ll h, ll d, ll total) {
  ll rests = total - d;
  ll totalHealth = rests + h;

  ll slots = rests + 1;
  ll longMoveLen = d / slots + 1;
  ll shortMoveLen = d / slots;
  ll longMoves = d % slots;
  ll shortMoves = slots - longMoves;

  ll shortMoveDamage = sumN(shortMoveLen) * shortMoves;
  ll longMoveDamage = sumN(longMoveLen) * longMoves;
  ll totalDamage = shortMoveDamage + longMoveDamage;

  return (totalHealth > totalDamage);
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int t;
  cin >> t;

  while (t--) {
    ll h, d;
    cin >> h >> d;

    ll low = d;
    ll high = 2LL * d;

    while (low <= high) {
      ll mid = low + (high - low) / 2;

      if (possible(h, d, mid)) {
        high = mid - 1;
      } else {
        low = mid + 1;
      }
    }

    cout << low << "\n";
  }

  return 0;
}
