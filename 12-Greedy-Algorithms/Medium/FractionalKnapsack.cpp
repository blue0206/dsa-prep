/*
 * Problem: Fractional Knapsack
 * Link: https://www.geeksforgeeks.org/problems/fractional-knapsack-1587115620/1
 *
 * Approach: The Fractional Knapsack problem is a classic example of a greedy
 *           algorithm. The greedy choice is to always pick the item with the
 *           highest value-to-weight ratio first.
 *
 *           1.  **Calculate Ratios:** For each item, calculate its
 *               value-to-weight ratio (`value / weight`).
 *           2.  **Sort:** Store the items along with their ratios and sort them
 *               in descending order based on these ratios.
 *           3.  **Fill Knapsack:** Iterate through the sorted items. For each
 *               item, if it can be taken whole (its weight is less than or
 *               equal to the remaining capacity), add its full value to the
 *               total and update the capacity. If it cannot be taken whole,
 *               take a fraction of it that fills the remaining capacity, add
 *               the corresponding fractional value, and then stop.
 *
 * Time Complexity: O(N log N) due to sorting.
 * Space Complexity: O(N) to store the items and their ratios.
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

struct Item {
  double ratio;
  double val;
  double wt;
};

double fractionalKnapsack(const vector<int>& val, const vector<int>& wt,
                          int capacity);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, capacity;
    cin >> n >> capacity;

    vector<int> val(n), wt(n);
    for (int i = 0; i < n; i++) cin >> val[i];
    for (int i = 0; i < n; i++) cin >> wt[i];

    cout << "Capacity: " << capacity << endl;
    cout << "Values: [ ";
    for (int i : val) {
      cout << i << " ";
    }
    cout << "]" << endl;
    cout << "Weights: [ ";
    for (int i : wt) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Fractional Knapsack: " << fractionalKnapsack(val, wt, capacity)
         << endl;
  }

  return 0;
}

double fractionalKnapsack(const vector<int>& val, const vector<int>& wt,
                          int capacity) {
  vector<Item> ratios;
  for (int i = 0; i < val.size(); i++) {
    double value = val[i];
    double weight = wt[i];
    double ratio = value / weight;
    Item item = {ratio, value, weight};

    ratios.emplace_back(item);
  }

  sort(ratios.begin(), ratios.end(),
       [](Item& item1, Item& item2) { return item1.ratio > item2.ratio; });

  double maxVal = 0;
  double remCapacity = capacity;
  for (int i = 0; i < ratios.size(); i++) {
    if (ratios[i].wt <= remCapacity) {
      maxVal += ratios[i].val;
      remCapacity -= ratios[i].wt;
    } else {
      double fract = remCapacity / ratios[i].wt;
      maxVal += (fract * ratios[i].val);
      break;
    }
  }

  return maxVal;
}
