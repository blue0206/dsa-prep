/*
 * Problem: Minimum Platforms
 * Link: https://www.geeksforgeeks.org/problems/minimum-platforms-1587115620/1
 *
 * Approach: This problem can be modeled as an event-based simulation. We can
 *           treat each arrival and departure as an event happening at a
 *           specific time. An arrival requires a platform (+1), and a
 *           departure frees one up (-1).
 *
 *           1.  **Create Events:** Create a list of events. For each train,
 *               add two events: `{arrival_time, +1}` and
 *               `{departure_time, -1}`.
 *           2.  **Sort Events:** Sort the list of all events. The primary
 *               sorting key is the time. For events at the same time, we must
 *               process arrivals before departures to correctly account for a
 *               train arriving at the exact moment another leaves.
 *           3.  **Sweep Line:** Iterate through the sorted events, maintaining
 *               a running count of currently needed platforms. The maximum
 *               value this count reaches is the minimum number of platforms
 *               required.
 *
 * Time Complexity: O(N log N) due to sorting.
 * Space Complexity: O(N) to store the events.
 */

#include <algorithm>
#include <iostream>
#include <utility>
#include <vector>

using namespace std;
using pii = pair<int, int>;

int minPlatform(const vector<int>& arr, const vector<int>& dep);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> start(n);
    for (int i = 0; i < n; i++) cin >> start[i];
    vector<int> end(n);
    for (int i = 0; i < n; i++) cin >> end[i];

    cout << "Arrival: [ ";
    for (int i : start) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "Departure: [ ";
    for (int i : end) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Min Platforms: " << minPlatform(start, end) << endl;
  }

  return 0;
}

int minPlatform(const vector<int>& arr, const vector<int>& dep) {
  vector<pii> trains;
  for (int i = 0; i < arr.size(); i++) {
    trains.push_back({arr[i], 1});   // Arrival event
    trains.push_back({dep[i], -1});  // Departure event
  }

  sort(trains.begin(), trains.end(), [](pii& one, pii& two) {
    if (one.first != two.first) {
      return one.first < two.first;
    }
    return one.second > two.second;
  });

  int maxPlatforms = 0;  // Tracks the peak number of platforms needed.
  int platforms = 0;     // Tracks the current number of platforms in use.
  for (const auto& event : trains) {
    platforms += event.second;
    maxPlatforms = max(maxPlatforms, platforms);
  }

  return maxPlatforms;
}
