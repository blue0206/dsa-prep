/*
 * Problem: N-Queens (LeetCode #51)
 * Link: https://leetcode.com/problems/n-queens/description/
 *
 * Approach: This is a classic backtracking problem. The goal is to place N
 *           queens on an N x N chessboard such that no two queens threaten
 *           each other. We place one queen per row, starting from row 0.
 *
 *           1. The recursive function `placeQueens` tries to place a queen in a
 *              given `row`, decrementing a `queens` counter.
 *           2. **Base Case:** If the `queens` counter reaches 0, it means we
 *              have successfully placed all N queens, so we have found a valid
 *              solution.
 *           3. **Recursive Step:** We iterate through each column `col` of the
 *              current `row`. For each cell `(row, col)`, we check if it's safe
 *              to place a queen there.
 *           4. **O(1) Safety Check:** To check for attacks in constant time, we
 *              use three boolean arrays (hashing):
 *              - `attackedCols`: Tracks which columns are under attack.
 *              - `attackedSumDiagonals`: Tracks diagonals where `row + col` is
 *                constant.
 *              - `attackedDiffDiagonals`: Tracks diagonals where `row - col` is
 *                constant. An offset is added to handle negative indices.
 *           5. If a cell is safe, we place a queen, update the attack arrays,
 *              and recurse for the next row (`row + 1`). After the call, we
 *              backtrack by removing the queen and reverting the attack arrays.
 *
 * Time Complexity: O(N!)
 * Space Complexity: O(N^2) - for the board and storing solutions.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vb = vector<bool>;
using vs = vector<string>;
using vvs = vector<vs>;

vvs solveNQueens(int n);
void placeQueens(vvs& ans, vs& board, vb& attackedCols,
                 vb& attackedSumDiagonals, vb& attackedDiffDiagonals,
                 int queens, int row);
bool placementPossible(vb& attackedCols, vb& attackedSumDiagonals,
                       vb& attackedDiffDiagonals, int col, int sum, int diff);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    cout << "Input: " << n << endl;

    vvs ans = solveNQueens(n);

    cout << "Placements: [ ";
    for (auto placement : ans) {
      cout << "[ ";
      for (auto row : placement) {
        cout << row << " ";
      }
      cout << " ] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vvs solveNQueens(int n) {
  vvs ans;
  vs board(n, string(n, '.'));
  vb attackedCols(n, false);
  vb attackedSumDiagonals(2 * n - 1, false);
  vb attackedDiffDiagonals(2 * n - 1, false);

  placeQueens(ans, board, attackedCols, attackedSumDiagonals,
              attackedDiffDiagonals, n, 0);
  return ans;
}

void placeQueens(vvs& ans, vs& board, vb& attackedCols,
                 vb& attackedSumDiagonals, vb& attackedDiffDiagonals,
                 int queens, int row) {
  if (queens == 0) {
    ans.emplace_back(board);
    return;
  }

  // Try placing a queen in each column of the current row.
  for (int col = 0; col < board.size(); col++) {
    int sumDiagonal = row + col;
    int diffDiagonal = (row - col) + (board.size() - 1);

    if (placementPossible(attackedCols, attackedSumDiagonals,
                          attackedDiffDiagonals, col, sumDiagonal,
                          diffDiagonal)) {
      // Place the queen and mark the attacks.
      board[row][col] = 'Q';
      attackedCols[col] = true;
      attackedSumDiagonals[sumDiagonal] = true;
      attackedDiffDiagonals[diffDiagonal] = true;

      placeQueens(ans, board, attackedCols, attackedSumDiagonals,
                  attackedDiffDiagonals, queens - 1, row + 1);

      // Backtrack: Remove the queen and un-mark the attacks.
      board[row][col] = '.';
      attackedCols[col] = false;
      attackedSumDiagonals[sumDiagonal] = false;
      attackedDiffDiagonals[diffDiagonal] = false;
    }
  }
}

bool placementPossible(vb& attackedCols, vb& attackedSumDiagonals,
                       vb& attackedDiffDiagonals, int col, int sum, int diff) {
  return !attackedCols[col] && !attackedSumDiagonals[sum] &&
         !attackedDiffDiagonals[diff];
}
