/*
 * Problem: Assign Cookies (LeetCode #455)
 * Link: https://leetcode.com/problems/assign-cookies/description/
 *
 * Approach: This is a classic greedy problem. To maximize the number of content
 *           children, we should try to satisfy the least greedy child with the
 *           smallest cookie that can satisfy them. This intuition leads to a
 *           two-pointer approach.
 *
 *           1.  **Sort:** Sort both the children's greed factors (`g`) and the
 *               cookie sizes (`s`) in non-decreasing order.
 *           2.  **Two Pointers:** Use one pointer (`l`) for the greed factors
 *               and another (`r`) for the cookie sizes.
 *           3.  **Iteration:** If the current cookie `s[r]` is large enough to
 *               satisfy the current child `g[l]`, we have a successful
 *               assignment. We increment both pointers and our content child
 *               count. If the cookie is too small, it cannot satisfy this
 *               child (or any subsequent, greedier children), so we discard
 *               the cookie by incrementing only the `r` pointer and try the
 *               next larger cookie for the same child.
 *
 * Time Complexity: O(G log G + S log S) due to sorting.
 * Space Complexity: O(1) auxiliary space (or O(log G + log S) for sorting).
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int findContentChildren(vector<int>& g, vector<int>& s);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;

    vector<int> g(n), s(m);
    for (int i = 0; i < n; i++) cin >> g[i];
    for (int i = 0; i < m; i++) cin >> s[i];

    cout << "Greed Factors: [ ";
    for (int i : g) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "Cookies: [ ";
    for (int i : s) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Content Children: " << findContentChildren(g, s) << endl;
  }

  return 0;
}

int findContentChildren(vector<int>& g, vector<int>& s) {
  sort(g.begin(), g.end());
  sort(s.begin(), s.end());

  int count = 0;
  int l = 0;
  int r = 0;
  while (l < g.size() && r < s.size()) {
    if (g[l] <= s[r]) {
      l++;
      r++;
      count++;
    } else {
      r++;
    }
  }

  return count;
}
