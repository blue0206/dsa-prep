/*
 * Problem: Hand of Straights (LeetCode #846)
 * Link: https://leetcode.com/problems/hand-of-straights/description/
 *
 * Approach: This problem can be solved by greedily forming straights starting
 *           from the smallest available card. An ordered map (`std::map`) is
 *           the perfect data structure for this, as it keeps card counts and
 *           automatically maintains the cards in sorted order.
 *
 *           1.  **Feasibility Check & Frequency Count:** First, if the total
 *               number of cards is not divisible by `groupSize`, it's
 *               impossible to form the groups. Otherwise, count the frequency
 *               of each card and store it in the ordered map.
 *           2.  **Greedy Group Formation:** While the map is not empty, start a
 *               new group with the smallest card currently in the map
 *               (`map.begin()->first`). Then, check for the existence of the
 *               next `groupSize - 1` consecutive cards. If any card is
 *               missing, return `false`. As we use each card, we decrement its
 *               count and remove it from the map if the count becomes zero.
 *
 * Time Complexity: O(N log N), where N is the number of cards.
 * Space Complexity: O(N) in the worst case, to store the frequency map.
 */

#include <algorithm>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

bool isNStraightHand(const vector<int>& hand, int groupSize);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, groupSize;
    cin >> n >> groupSize;

    vector<int> hand(n);
    for (int i = 0; i < n; i++) cin >> hand[i];

    cout << "Group Size: " << groupSize << endl;
    cout << "Input Array: [ ";
    for (int i : hand) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Result: " << (isNStraightHand(hand, groupSize) ? "True" : "False")
         << endl;
  }

  return 0;
}

bool isNStraightHand(const vector<int>& hand, int groupSize) {
  if (hand.size() % groupSize != 0) {
    return false;
  }

  // Use a map to store the frequency of cards, which keeps them sorted.
  map<int, int> mp;
  for (int card : hand) {
    mp[card]++;
  }

  // Greedily form groups starting from the smallest card.
  while (!mp.empty()) {
    // Get the smallest card to start a new straight.
    int start = mp.begin()->first;

    // Check for the next `groupSize` consecutive cards.
    for (int i = 0; i < groupSize; i++) {
      int current = start + i;

      // If a required card is not available, it's impossible.
      if (mp.find(current) == mp.end()) return false;

      mp[current]--;
      // If the count of a card becomes zero, remove it from the map.
      if (mp[current] == 0) mp.erase(current);
    }
  }
  return true;
}
