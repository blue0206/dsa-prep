/*
 * Problem: Surrounded Regions (LeetCode #130)
 * Link: https://leetcode.com/problems/surrounded-regions/description/
 *
 * Approach: The key insight is to work backward. Instead of finding regions
 *           of 'O's that are surrounded, we find the regions of 'O's that are
 *           *not* surrounded and change everything else.
 *           1.  An 'O' is not surrounded if it is on the border of the grid or
 *               is connected to an 'O' on the border.
 *           2.  We iterate through the cells on the four borders of the grid.
 *           3.  If we find an 'O', we start a Depth-First Search (DFS) from
 *               that cell. The DFS traverses all connected 'O's and marks
 *               them with a temporary character (e.g., '.').
 *           4.  After checking all borders, any cell that is still an 'O' must
 *               be surrounded. We iterate through the grid one last time,
 *               flipping these 'O's to 'X's and reverting the temporary '.'
 *               markers back to 'O's.
 *
 * Time Complexity: O(M * N), where M and N are the grid dimensions.
 * Space Complexity: O(M * N) in the worst case for the recursion stack.
 */
#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

void solve(vector<vector<char>>& board);
void dfs(vector<vector<char>>& board, int r, int c);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int m, n;
    cin >> m >> n;

    vector<vector<char>> board(m, vector<char>(n));
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        cin >> board[i][j];
      }
    }

    cout << "Input Board: [ ";
    for (auto rows : board) {
      cout << "[ ";
      for (char val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    solve(board);

    cout << "Surrounded Regions: [ ";
    for (auto rows : board) {
      cout << "[ ";
      for (char val : rows) {
        cout << val << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;
  }

  return 0;
}

void solve(vector<vector<char>>& board) {
  int m = board.size();
  int n = board[0].size();
  for (int i = 0; i < n; i++) {
    if (board[0][i] == 'O') {
      dfs(board, 0, i);
    }
    if (board[m - 1][i] == 'O') {
      dfs(board, m - 1, i);
    }
  }

  for (int i = 0; i < m; i++) {
    if (board[i][0] == 'O') {
      dfs(board, i, 0);
    }
    if (board[i][n - 1] == 'O') {
      dfs(board, i, n - 1);
    }
  }

  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      if (board[i][j] == '.') {
        board[i][j] = 'O';
      } else if (board[i][j] == 'O') {
        board[i][j] = 'X';
      }
    }
  }
}

void dfs(vector<vector<char>>& board, int r, int c) {
  if (r < 0 || r >= board.size() || c < 0 || c >= board[0].size() ||
      board[r][c] != 'O') {
    return;
  }

  board[r][c] = '.';
  dfs(board, r + 1, c);
  dfs(board, r - 1, c);
  dfs(board, r, c + 1);
  dfs(board, r, c - 1);
}
