/*
 * Problem: Rat In A Maze
 * Link: https://www.geeksforgeeks.org/problems/rat-in-a-maze-problem/1
 *
 * Approach: This is a classic backtracking problem that can be solved using a
 *           Depth-First Search (DFS) approach. We explore all possible paths
 *           from the starting cell (0, 0) to the destination (n-1, n-1).
 *
 *           1. The recursive function `findPaths` explores the maze from a
 *              given `(row, col)`.
 *           2. **Base Cases:**
 *              a) **Failure:** The path is invalid if we go out of bounds, or
 *                 if we land on a blocked or already visited cell
 *                 (`maze[row][col] == 0`). This check must come first.
 *              b) **Success:** If we reach the destination cell `(n-1, n-1)`,
 *                 we have found a valid path.
 *           3. **Backtracking:** To avoid using the same cell twice in a single
 *              path, we mark the current cell as visited (by setting
 *              `maze[row][col] = 0`) before exploring its neighbors. After the
 *              recursive calls return, we must restore the cell's original
 *              value (`maze[row][col] = 1`) so it can be part of other paths.
 *           4. **Sorting:** After the recursion completes, the collected paths
 *              are sorted lexicographically to meet the output requirements.
 *
 * Time Complexity: O(4^(N*N))
 * Space Complexity: O(N*N) - For the recursion stack and path string.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vi = vector<int>;
using vvi = vector<vi>;
using vs = vector<string>;

vs ratInMaze(vvi& maze);
void findPaths(vs& ans, vvi& maze, string& path, int row, int col);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vvi maze(n, vi(n));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < n; j++) {
        cin >> maze[i][j];
      }
    }

    cout << "Maze: [ ";
    for (auto rows : maze) {
      cout << "[ ";
      for (int j : rows) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    vs paths = ratInMaze(maze);

    cout << "Paths: [ ";
    for (auto path : paths) {
      cout << path << " ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vs ratInMaze(vvi& maze) {
  vs ans;
  string path = "";

  // Only start the search if the starting cell is not blocked.
  if (maze[0][0] == 1) {
    findPaths(ans, maze, path, 0, 0);
    sort(ans.begin(), ans.end());
  }

  return ans;
}

void findPaths(vs& ans, vvi& maze, string& path, int row, int col) {
  // Failure Base Case: Out of bounds or on a blocked/visited cell.
  // This check MUST come before the success case.
  if (row < 0 || row >= maze.size() || col < 0 || col >= maze.size() ||
      maze[row][col] == 0) {
    return;
  }

  // Success Base Case: Reached the destination.
  if (row == maze.size() - 1 && col == maze.size() - 1) {
    ans.emplace_back(path);
    return;
  }

  maze[row][col] = 0;  // Mark the cell as visited
  for (int i = 0; i < 4; i++) {
    if (i == 0) {
      path.push_back('D');
      findPaths(ans, maze, path, row + 1, col);
    } else if (i == 1) {
      path.push_back('L');
      findPaths(ans, maze, path, row, col - 1);
    } else if (i == 2) {
      path.push_back('U');
      findPaths(ans, maze, path, row - 1, col);
    } else {
      path.push_back('R');
      findPaths(ans, maze, path, row, col + 1);
    }
    path.pop_back();
  }
  maze[row][col] = 1;  // Backtrack: Un-mark the cell
}
