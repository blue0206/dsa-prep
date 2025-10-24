/*
 * Problem: Boolean Evaluation
 * Link:
 * https://www.naukri.com/code360/problems/problem-name-boolean-evaluation_1214650?leftPanelTabValue=PROBLEM
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <vector>

using namespace std;
using ll = long long;
const ll m = 1e9 + 7;

/**
 * Approach: This is a top-down DP approach (memoization). This is a classic
 *           Partition DP problem. The function `solve(i, j, isTrue)` finds the
 *           number of ways to parenthesize the sub-expression `exp[i...j]`
 *           such that it evaluates to `isTrue`. We try every operator `k` as
 *           the final operation. The total ways are the sum of ways from
 *           partitioning at each `k`, calculated from the true/false counts of
 *           the left and right sub-expressions.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2) for DP table + O(N) for recursion stack.
 */
int memoizationApproach(string& exp);
int solve(vector<vector<vector<ll>>>& dp, string& exp, bool isTrue, int i,
          int j);

/**
 * Approach: This is the tabulation (bottom-up) version. We fill a 3D DP table
 *           where `dp[i][j][isTrue]` stores the number of ways for `exp[i...j]`
 *           to evaluate to `isTrue`. The table is filled by iterating over
 *           sub-expression lengths, from small to large.
 *
 * Time Complexity: O(N^3)
 * Space Complexity: O(N^2)
 */
int tabulationApproach(string& exp);

ll countWays(char op, bool isTrue, ll leftTrue, ll leftFalse, ll rightTrue,
             ll rightFalse);
int main() {
  int t;
  cin >> t;

  while (t--) {
    string exp;
    cin >> exp;

    cout << "Expression: " << exp << endl;

    cout << "Number of Ways (Memoization): " << memoizationApproach(exp)
         << endl;
    cout << "Number of Ways (Tabulation): " << tabulationApproach(exp) << endl;

    cout << endl;
  }

  return 0;
}

//----------------------------MEMOIZATION APPROACH------------------------------
int memoizationApproach(string& exp) {
  int n = exp.length();

  vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, -1)));
  return solve(dp, exp, true, 0, n - 1);
}

int solve(vector<vector<vector<ll>>>& dp, string& exp, bool isTrue, int i,
          int j) {
  if (i == j) {
    if (isTrue) return exp[i] == 'T';
    return exp[i] == 'F';
  };
  if (dp[i][j][isTrue] != -1) return dp[i][j][isTrue];

  ll count = 0;
  for (int k = i + 1; k < j; k += 2) {
    char op = exp[k];

    ll leftTrue = solve(dp, exp, true, i, k - 1) % m;
    ll leftFalse = solve(dp, exp, false, i, k - 1) % m;
    ll rightTrue = solve(dp, exp, true, k + 1, j) % m;
    ll rightFalse = solve(dp, exp, false, k + 1, j) % m;

    ll ways = countWays(op, isTrue, leftTrue, leftFalse, rightTrue, rightFalse);
    count = ((count % m) + (ways % m)) % m;
  }

  dp[i][j][isTrue] = count;
  return dp[i][j][isTrue];
}

//-----------------------------TABULATION APPROACH------------------------------
int tabulationApproach(string& exp) {
  int n = exp.length();

  vector<vector<vector<ll>>> dp(n, vector<vector<ll>>(n, vector<ll>(2, 0)));
  for (int i = 0; i < n; i++) {
    if (exp[i] == 'T') {
      dp[i][i][1] = 1;
    } else if (exp[i] == 'F') {
      dp[i][i][0] = 1;
    }
  }

  for (int i = n - 1; i >= 0; i--) {
    for (int j = i; j < n; j++) {
      if (exp[i] == '|' || exp[j] == '|' || exp[i] == '&' || exp[j] == '&' ||
          exp[i] == '^' || exp[j] == '^')
        continue;

      for (int k = i + 1; k < j; k += 2) {
        char op = exp[k];

        ll leftTrue = dp[i][k - 1][1] % m;
        ll leftFalse = dp[i][k - 1][0] % m;
        ll rightTrue = dp[k + 1][j][1] % m;
        ll rightFalse = dp[k + 1][j][0] % m;

        ll falseCount =
            countWays(op, false, leftTrue, leftFalse, rightTrue, rightFalse);
        ll trueCount =
            countWays(op, true, leftTrue, leftFalse, rightTrue, rightFalse);

        dp[i][j][0] = ((dp[i][j][0] % m) + (falseCount % m)) % m;
        dp[i][j][1] = ((dp[i][j][1] % m) + (trueCount % m)) % m;
      }
    }
  }

  return dp[0][n - 1][1];
}

ll countWays(char op, bool isTrue, ll leftTrue, ll leftFalse, ll rightTrue,
             ll rightFalse) {
  ll count = 0;
  if (op == '&') {
    if (isTrue) {
      ll temp = (leftTrue * rightTrue) % m;
      count = ((count % m) + (temp % m)) % m;
    } else {
      ll temp1 = (leftTrue * rightFalse) % m;
      ll temp2 = (leftFalse * rightTrue) % m;
      ll temp3 = (leftFalse * rightFalse) % m;

      count = ((count % m) + (temp1)) % m;
      count = ((count % m) + (temp2)) % m;
      count = ((count % m) + temp3) % m;
    }
  } else if (op == '|') {
    if (isTrue) {
      ll temp1 = (leftTrue * rightTrue) % m;
      ll temp2 = (leftTrue * rightFalse) % m;
      ll temp3 = (leftFalse * rightTrue) % m;

      count = ((count % m) + temp1) % m;
      count = ((count % m) + temp2) % m;
      count = ((count % m) + temp3) % m;
    } else {
      ll temp = (leftFalse * rightFalse) % m;
      count = ((count % m) + (temp % m)) % m;
    }
  } else {
    if (isTrue) {
      ll temp1 = (leftTrue * rightFalse) % m;
      ll temp2 = (leftFalse * rightTrue) % m;
      count = ((count % m) + (temp1)) % m;
      count = ((count % m) + temp2) % m;
    } else {
      ll temp1 = (leftTrue * rightTrue) % m;
      ll temp2 = (leftFalse * rightFalse) % m;
      count = ((count % m) + temp1) % m;
      count = ((count % m) + temp2) % m;
    }
  }

  return count;
}
