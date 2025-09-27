/*
 * Problem: N Meetings in One Room
 * Link:
 * https://www.geeksforgeeks.org/problems/n-meetings-in-one-room-1587115620/1
 *
 * Approach: This is a classic greedy problem. To maximize the number of
 *           meetings, we should always choose the meeting that finishes the
 *           earliest. This strategy leaves the meeting room available as soon
 *           as possible, maximizing the time remaining for subsequent
 *           meetings.
 *
 *           1.  **Combine and Sort:** Combine the start and end times into
 *               pairs or a struct. Sort these meetings based on their end
 *               times in ascending order.
 *           2.  **Greedy Selection:** Select the first meeting in the sorted
 *               list. Then, iterate through the rest of the meetings. For each
 *               meeting, if its start time is after the finish time of the
 *               last selected meeting, we can schedule it. We then select this
 *               meeting and update our "last finish time".
 *
 * Time Complexity: O(N log N) due to sorting.
 * Space Complexity: O(N) to store the meetings.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int maxMeetings(vector<int>& start, vector<int>& end);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<int> start(n);
    vector<int> end(n);
    for (int i = 0; i < n; i++) {
      cin >> start[i];
      cin >> end[i];
    }

    cout << "Start: [ ";
    for (int i : start) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "End: [ ";
    for (int i : end) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Max Meetings: " << maxMeetings(start, end) << endl;
  }

  return 0;
}

int maxMeetings(const vector<int>& start, const vector<int>& end) {
  if (start.empty()) return 0;

  vector<pair<int, int>> meetings;
  for (int i = 0; i < start.size(); i++) {
    meetings.push_back({end[i], start[i]});
  }

  // Sort meetings based on their end times.
  sort(meetings.begin(), meetings.end());

  // The first meeting is always selected.
  int maxMeeting = 1;
  int lastEndTime = meetings[0].first;

  for (int i = 1; i < meetings.size(); i++) {
    // If the current meeting starts after the last one ended, select it.
    if (meetings[i].second > lastEndTime) {
      maxMeeting++;
      lastEndTime = meetings[i].first;
    }
  }

  return maxMeeting;
}
