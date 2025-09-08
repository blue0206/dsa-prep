/*
 * Problem: Word Search (LeetCode #79)
 * Link: https://leetcode.com/problems/word-search/description/
 *
 * Approach: This problem is a classic application of recursive backtracking or
 *           Depth-First Search (DFS). The main idea is to traverse the grid to
 *           find a path that spells out the given word.
 *
 *           1. We iterate through every cell of the board. If a cell's
 *              character matches the first character of the word, we start a
 *              DFS from that cell.
 *           2. The `wordSearch` recursive function explores the grid.
 *           3. **Base Cases:**
 *              a) **Failure:** The search fails if we go out of bounds (invalid
 *                 row/col) or if the character at the current board cell does
 *                 not match the character we are looking for at the current
 *                 `index` of the word.
 *              b) **Success:** The search succeeds if we have found all the
 *                 characters, i.e., when `index` reaches the last character of
 *                 the word.
 *           4. **Backtracking:** To avoid using the same cell multiple times in
 *              one path, we mark the current cell as "visited" before exploring
 *              its neighbors (e.g., by changing it to '#'). After the recursive
 *              calls for its neighbors return, we must "un-mark" the cell by
 *              restoring its original character. This is the backtracking step.
 *
 * Time Complexity: O(N * M * 4^L), where N, M are board dimensions and L is
 * word length. Space Complexity: O(L) for the recursion stack depth.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vc = vector<char>;
using vvc = vector<vc>;

bool exist(vvc& board, string word);
bool wordSearch(vvc& board, string& word, int row, int col, int index);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vvc board(n, vc(m));
    for (int i = 0; i < n; i++) {
      for (int j = 0; j < m; j++) {
        cin >> board[i][j];
      }
    }

    string word;
    cin >> word;

    cout << "Board: [ ";
    for (auto row : board) {
      cout << "[ ";
      for (auto j : row) {
        cout << j << " ";
      }
      cout << "]";
    }
    cout << " ]" << endl;

    cout << "Word: " << word << endl;

    cout << "Result: " << (exist(board, word) ? "True" : "False") << endl;

    cout << endl;
  }

  return 0;
}

bool exist(vvc& board, string word) {
  for (int i = 0; i < board.size(); i++) {
    for (int j = 0; j < board[0].size(); j++) {
      if (board[i][j] == word[0]) {
        if (wordSearch(board, word, i, j, 0)) {
          return true;
        }
      }
    }
  }

  return false;
}

bool wordSearch(vvc& board, string& word, int row, int col, int index) {
  // Failure Base Case: If out of bounds or the character doesn't match.
  if (row < 0 || row >= board.size() || col < 0 || col >= board[0].size() ||
      board[row][col] != word[index]) {
    return false;
  }

  // Success Base Case: If we've reached the end of the word, we've found it.
  if (index == word.length() - 1) {
    return true;
  }

  // Mark the current cell as visited to avoid reusing it in the same path.
  char originalChar = board[row][col];
  board[row][col] = '#';

  // Explore all 4 directions (up, down, left, right).
  bool found = wordSearch(board, word, row + 1, col, index + 1) ||
               wordSearch(board, word, row - 1, col, index + 1) ||
               wordSearch(board, word, row, col + 1, index + 1) ||
               wordSearch(board, word, row, col - 1, index + 1);

  // Backtrack: Restore the original character so it can be used in other paths.
  board[row][col] = originalChar;
  return found;
}
