/*
 * Problem: Sudoku Solver (LeetCode #37)
 * Link: https://leetcode.com/problems/sudoku-solver/description/
 *
 * Approach: This is a classic backtracking problem. We iterate through the
 *           board cell by cell. When we find an empty cell, we try to place
 *           each valid number (1-9) in it.
 *
 *           1. **O(1) Validation:** To quickly check if a number is valid in a
 *              given cell, we use three 2D boolean arrays: `rowCheck`,
 *              `colCheck`, and `quadrantCheck`. These act as hash sets to tell
 *              us in O(1) time if a number already exists in the corresponding
 *              row, column, or 3x3 quadrant.
 *           2. **Recursive Function:** The core logic is in a recursive
 *              function that returns a boolean. It returns `true` if a
 *              solution is found from the current state, and `false`
 *              otherwise.
 *           3. **Base Case:** If we successfully fill all cells (i.e., our row
 *              index reaches 9), we have found the solution, and we return
 *              `true`.
 *           4. **Backtracking:** If we place a number and the subsequent
 *              recursive call returns `false`, we must "undo" our choice
 *              (backtrack) by resetting the cell to '.' and clearing the
 *              corresponding flags in our check arrays.
 *
 * Time Complexity: O(9^M), where M is the number of empty cells.
 * Space Complexity: O(N^2) for the recursion stack, where N=9.
 */

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

using namespace std;
using vc = vector<char>;
using vvc = vector<vc>;
using vb = vector<bool>;
using vvb = vector<vb>;

void solveSudoku(vvc& board);
bool playSudoku(vvc& board, vvb& rowCheck, vvb& colCheck, vvb& quadrantCheck,
                int row, int col);
bool isSafe(vvb& rowCheck, vvb& colCheck, vvb& quadrantCheck, int row, int col,
            int quadrant, int num);

int main() {
  int t;
  cin >> t;

  while (t--) {
    vvc board(9, vc(9));
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        cin >> board[i][j];
      }
    }

    cout << "Input Board: [ ";
    for (auto row : board) {
      cout << "[ ";
      for (auto j : row) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    solveSudoku(board);

    cout << "Solved Board: [ ";
    for (auto row : board) {
      cout << "[ ";
      for (auto j : row) {
        cout << j << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

void solveSudoku(vvc& board) {
  vvb rowCheck(9, vb(10, false));
  vvb colCheck(9, vb(10, false));
  vvb quadrantCheck(9, vb(10, false));

  for (int row = 0; row < 9; row++) {
    for (int col = 0; col < 9; col++) {
      if (board[row][col] != '.') {
        int digit = board[row][col] - '0';
        rowCheck[row][digit] = true;
        colCheck[col][digit] = true;

        int quadrantIndex = ((row / 3) * 3) + (col / 3);
        quadrantCheck[quadrantIndex][digit] = true;
      }
    }
  }

  playSudoku(board, rowCheck, colCheck, quadrantCheck, 0, 0);
}

bool playSudoku(vvc& board, vvb& rowCheck, vvb& colCheck, vvb& quadrantCheck,
                int row, int col) {
  // Base Case: If we've moved past the last cell, a solution is found.
  if (row == 9) {
    return true;
  }

  // Calculate the next cell's coordinates.
  int nextRow = (col == 8) ? row + 1 : row;
  int nextCol = (col == 8) ? 0 : col + 1;

  // If the current cell is already filled, move to the next one.
  if (board[row][col] != '.') {
    return playSudoku(board, rowCheck, colCheck, quadrantCheck, nextRow,
                      nextCol);
  }

  // Try placing numbers 1-9 in the current empty cell.
  int quadrant = ((row / 3) * 3) + (col / 3);
  for (int num = 1; num <= 9; num++) {
    if (isSafe(rowCheck, colCheck, quadrantCheck, row, col, quadrant, num)) {
      // Place the number and update checks.
      board[row][col] = '0' + num;
      rowCheck[row][num] = true;
      colCheck[col][num] = true;
      quadrantCheck[quadrant][num] = true;

      // Recurse: If the subsequent calls find a solution, propagate success.
      if (playSudoku(board, rowCheck, colCheck, quadrantCheck, nextRow,
                     nextCol)) {
        return true;
      }

      // Backtrack: If the path didn't lead to a solution, undo the choice.
      board[row][col] = '.';
      rowCheck[row][num] = false;
      colCheck[col][num] = false;
      quadrantCheck[quadrant][num] = false;
    }
  }

  // If no number from 1-9 works in this cell, this path is invalid.
  return false;
}

bool isSafe(vvb& rowCheck, vvb& colCheck, vvb& quadrantCheck, int row, int col,
            int quadrant, int num) {
  return !rowCheck[row][num] && !colCheck[col][num] &&
         !quadrantCheck[quadrant][num];
}
