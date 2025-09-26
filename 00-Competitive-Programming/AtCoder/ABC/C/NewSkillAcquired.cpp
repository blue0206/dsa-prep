/*
 * Problem: New Skill Acquired (ABC #424)
 * Rating: Beginner-C
 * Link: https://atcoder.jp/contests/abc424/tasks/abc424_c
 *
 * Approach: The problem describes a dependency system where skills can be
 *           acquired. This can be modeled as a graph traversal problem. Since
 *           a skill can be learned if *any* of its prerequisites are met, we
 *           can find all acquirable skills by starting a traversal from the
 *           skills that have no prerequisites. A Breadth-First Search (BFS) is
 *           a natural fit for this.
 *
 *           1.  **Graph Representation:** We use a `vvi unlocks` as a reverse
 *               adjacency list. `unlocks[u]` stores a list of all skills `v`
 *               for which `u` is a prerequisite.
 *           2.  **Initialization:** We use a queue for the BFS and a boolean
 *               array `skills` to track which skills have been acquired (or
 *               visited). We initialize the queue with all skills that have no
 *               prerequisites (input `a=0` and `b=0`).
 *           3.  **BFS Traversal:** We process the queue. When we dequeue a
 *               skill `u`, we consider it "acquired". We then iterate through
 *               all skills `v` in `unlocks[u]`. Since `u` is now acquired, the
 *               condition for learning `v` is met. If `v` has not been
 *               acquired yet, we mark it as acquired and enqueue it to
 *               continue the traversal.
 *           4.  **Counting:** The total number of acquired skills is the final
 *               count of `true` values in the `skills` array.
 *
 * Time Complexity: O(N + K), where K is the total number of prerequisite
 *                  relations.
 * Space Complexity: O(N + K)
 */

#include <iostream>
#include <queue>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vb = vector<bool>;
using qi = queue<int>;

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int n;
  cin >> n;

  vb skills(n + 1, false);
  vvi unlocks(n + 1);
  qi process;

  for (int i = 1; i <= n; i++) {
    int a, b;
    cin >> a >> b;

    if (a == 0 && b == 0) {
      skills[i] = true;
      process.push(i);
    } else {
      unlocks[a].emplace_back(i);
      unlocks[b].emplace_back(i);
    }
  }

  while (!process.empty()) {
    int skill = process.front();
    process.pop();

    for (int unlockedSkill : unlocks[skill]) {
      if (!skills[unlockedSkill]) {
        skills[unlockedSkill] = true;
        process.push(unlockedSkill);
      }
    }
  }

  int count = 0;
  for (int i = 1; i <= n; i++) {
    if (skills[i]) {
      count++;
    }
  }

  cout << count << "\n";

  return 0;
}
