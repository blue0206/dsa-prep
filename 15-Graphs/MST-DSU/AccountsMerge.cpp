/*
 * Problem: Accounts Merge (LeetCode #721)
 * Link: https://leetcode.com/problems/accounts-merge/description/
 *
 * Approach:
 * This problem can be efficiently solved using the Disjoint Set Union (DSU)
 * data structure. The core idea is to group accounts that belong to the same
 * person. Two accounts belong to the same person if they share at least one
 * common email address.
 *
 * 1.  **Initialize DSU:** Create a DSU structure where each account (identified
 *     by its index in the input `accounts` vector) is initially its own
 *     separate set.
 * 2.  **Map Emails to Accounts & Union:** Iterate through all accounts. For
 *     each email in an account, use an `unordered_map` (`emailToAccountMap`)
 *     to store the first account index that email was associated with. If an
 *     email is encountered again in a different account, it means these two
 *     accounts are related. Perform a `unionBySize` operation between the
 *     current account's index and the previously stored account index for that
 *     email.
 * 3.  **Aggregate Emails:** After processing all emails and performing all
 *     unions, iterate through the original `accounts` again. For each account
 *     `i`, find its ultimate parent `p = dsu.find(i)`. Use another
 *     `unordered_map` (`mergedEmails`) to collect all emails from account `i`
 *     into the `unordered_set` associated with its parent `p`.
 * 4.  **Format Result:** For each entry in `mergedEmails`, sort the collected
 *     emails and prepend the account name (taken from `accounts[parent_id][0]`)
 *     to form the final merged account list.
 *
 * Time Complexity: O(E * α(N) + E * log E * L), where N is the number of
 *                  accounts, E is the total number of emails across all
 *                  accounts, α is the inverse Ackermann function (nearly
 *                  constant), and L is the maximum length of an email string.
 * Space Complexity: O(N + E * L) for the DSU structure, email maps, and result.
 */

#include <algorithm>
#include <iostream>
#include <numeric>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

class DisjointSet {
 private:
  vector<int> size, parent;

 public:
  DisjointSet(int n) {
    size.assign(n, 1);
    parent.assign(n, 0);
    iota(parent.begin(), parent.end(), 0);
  }

  int find(int i) {
    if (parent[i] == i) return i;

    parent[i] = find(parent[i]);
    return parent[i];
  }

  void unionBySize(int i, int j) {
    int pi = find(i);
    int pj = find(j);

    if (pi == pj) return;

    if (size[pi] >= size[pj]) {
      size[pi] += size[pj];
      parent[pj] = pi;
    } else {
      size[pj] += size[pi];
      parent[pi] = pj;
    }
  }
};

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<vector<string>> accounts(n);
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;

      accounts[i].resize(m);
      for (int j = 0; j < m; j++) {
        cin >> accounts[i][j];
      }
    }

    cout << "Accounts: [";
    for (auto account : accounts) {
      cout << "[ ";
      for (auto str : account) {
        cout << str << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    vector<vector<string>> ans = accountsMerge(accounts);

    cout << "Merged Accounts: [";
    for (auto account : ans) {
      cout << "[ ";
      for (auto str : account) {
        cout << str << " ";
      }
      cout << "] ";
    }
    cout << "]" << endl;

    cout << endl;
  }

  return 0;
}

vector<vector<string>> accountsMerge(vector<vector<string>>& accounts) {
  DisjointSet dsu(accounts.size());

  unordered_map<string, int> userMap;
  for (int i = 0; i < accounts.size(); i++) {
    for (int j = 1; j < accounts[i].size(); j++) {
      if (userMap.count(accounts[i][j])) {
        dsu.unionBySize(i, userMap[accounts[i][j]]);
      } else {
        userMap[accounts[i][j]] = i;
      }
    }
  }

  unordered_map<int, unordered_set<string>> mailMap;
  for (int i = 0; i < accounts.size(); i++) {
    int parentId = dsu.find(i);
    mailMap[parentId];
    for (int j = 1; j < accounts[i].size(); j++) {
      mailMap[parentId].insert(accounts[i][j]);
    }
  }

  vector<vector<string>> ans;
  for (auto it : mailMap) {
    vector<string> mails;
    for (auto mail : it.second) {
      mails.emplace_back(mail);
    }
    sort(mails.begin(), mails.end());

    vector<string> details = {accounts[it.first][0]};
    details.insert(details.end(), mails.begin(), mails.end());

    ans.emplace_back(details);
  }

  return ans;
}
