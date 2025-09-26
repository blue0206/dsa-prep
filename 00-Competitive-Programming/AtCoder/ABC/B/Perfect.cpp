/*
 * Problem: Perfect (ABC #424)
 * Rating: Beginner-B
 * Link: https://atcoder.jp/contests/abc424/tasks/abc424_b
 *
 * Approach: Use a frequency array to count the number of problems solved by
 *           each participant. Iterate through the `k` submissions. For each
 *           submission by participant `p`, increment their count. If their
 *           count reaches `m`, they have achieved a "perfect" score. Store
 *           these participants' IDs. Finally, print the stored IDs.
 *
 * Time Complexity: O(K + P log P), where P is the number of perfect
 *                  participants.
 * Space Complexity: O(N)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;
using vi = vector<int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n, m, k;
  cin >> n >> m >> k;

  // Use a frequency array to count solved problems for each participant.
  vi participants(n + 1);
  vi ans;
  for (int i = 0; i < k; i++) {
    int a, b;
    cin >> a >> b;

    // Increment the count for the participant.
    participants[a]++;
    // If they reach `m` solved problems, they are "perfect".
    if (participants[a] == m) ans.emplace_back(a);
  }

  for (int i : ans) {
    cout << i << " ";
  }

  return 0;
}
