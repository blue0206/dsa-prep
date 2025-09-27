/*
 * Problem: Ulam-Warburton Automaton (ABC #425)
 * Rating: Beginner-D
 * Link: https://atcoder.jp/contests/abc425/tasks/abc425_d
 *
 * Approach: This problem describes a cellular automaton where white cells turn
 *           black if they have exactly one black neighbor. This process occurs
 *           in discrete, simultaneous time steps. We can simulate this process
 *           generation by generation using a BFS-like approach.
 *
 *           1.  **Initialization:**
 *               -   First, we find all white cells `.` that initially have
 *                   exactly one black neighbor. These cells form the first
 *                   "layer" or generation of cells to be turned black.
 *               -   We use a queue (`currentLayerElements`) to store these
 *                   cells and a `visited` grid to prevent processing the same
 *                   cell multiple times.
 *
 *           2.  **Layer-by-Layer Simulation (BFS):**
 *               -   We process all cells in the `currentLayerElements` queue.
 *               -   For each cell we process, we turn it black (`#`).
 *               -   We then examine its four neighbors. If a neighbor is a
 *                   white cell that hasn't been visited yet, it becomes a
 *                   *potential* candidate for the next generation. We add
 *                   these candidates to a temporary list (`nextLayerElements`).
 *
 *           3.  **Filtering for Next Generation:**
 *               -   After all cells in the current layer have been turned
 *                   black, we must re-evaluate the candidates in
 *                   `nextLayerElements`.
 *               -   A candidate cell is only added to the queue for the next
 *                   generation if it *still* has exactly one black neighbor
 *                   after the entire current layer has been updated. This step
 *                   is crucial to correctly model the simultaneous nature of
 *                   the automaton's rules.
 *
 *           4.  **Termination:** The process continues until a generation
 *               produces no new cells to turn black. The final count of black
 *               cells is the answer.
 *
 * Time Complexity: O(H * W * L), where L is the number of layers. In the worst
 *                  case, this could be O((H*W)^2), but it's much faster in
 *                  practice.
 * Space Complexity: O(H * W) for the grid, visited array, and queue.
 */

#include <iostream>
#include <queue>
#include <string>
#include <vector>

using namespace std;
using vs = vector<string>;
using vb = vector<bool>;
using vvb = vector<vb>;
using pii = pair<int, int>;
using qpii = queue<pii>;
using vpii = vector<pii>;

int blackNeighborCount(vs& s, int i, int j) {
  int h = s.size();
  int w = s[0].length();
  int hashCount = 0;

  if (i > 0 && s[i - 1][j] == '#') hashCount++;
  if (i < h - 1 && s[i + 1][j] == '#') hashCount++;
  if (j > 0 && s[i][j - 1] == '#') hashCount++;
  if (j < w - 1 && s[i][j + 1] == '#') hashCount++;

  return hashCount;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);

  int h, w;
  cin >> h >> w;

  vs s(h);
  for (int i = 0; i < h; i++) {
    cin >> s[i];
  }

  int blacks = 0;
  vvb visited(h, vb(w, false));
  qpii currentLayerElements;
  // Find the initial set of cells to turn black.
  for (int i = 0; i < h; i++) {
    for (int j = 0; j < w; j++) {
      if (s[i][j] == '#') {
        blacks++;
      } else if (blackNeighborCount(s, i, j) == 1) {
        currentLayerElements.push({i, j});
        visited[i][j] = true;
      }
    }
  }

  int dx[4] = {0, 0, 1, -1};
  int dy[4] = {1, -1, 0, 0};
  // Simulate the automaton generation by generation.
  while (!currentLayerElements.empty()) {
    vpii nextLayerElements;

    // Process all cells in the current generation.
    while (!currentLayerElements.empty()) {
      auto [r, c] = currentLayerElements.front();
      currentLayerElements.pop();

      s[r][c] = '#';
      blacks++;

      // Check neighbors to find potential candidates for the next generation.
      for (int i = 0; i < 4; i++) {
        int newR = r + dy[i];
        int newC = c + dx[i];

        if (newR >= 0 && newR < h && newC >= 0 && newC < w &&
            !visited[newR][newC] && s[newR][newC] == '.' &&
            blackNeighborCount(s, newR, newC) == 1) {
          nextLayerElements.push_back({newR, newC});
          visited[newR][newC] = true;
        }
      }
    }

    // Re-evaluate candidates to ensure they are valid for the next generation.
    // This handles the simultaneous update rule.
    for (auto i : nextLayerElements) {
      auto [r, c] = i;

      if (s[r][c] == '.' && blackNeighborCount(s, r, c) == 1) {
        currentLayerElements.push({r, c});
      }
    }
  }

  cout << blacks << "\n";

  return 0;
}
