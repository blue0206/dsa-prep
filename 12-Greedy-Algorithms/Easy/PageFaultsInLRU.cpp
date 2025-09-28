/*
 * Problem: Page Faults in LRU
 * Link: https://www.geeksforgeeks.org/problems/page-faults-in-lru5603/1
 *
 * Approach: This problem requires simulating a Least Recently Used (LRU)
 *           cache. We can build an efficient LRU cache using a combination of
 *           a hash map and a doubly-linked list (`std::list`).
 *
 *           1.  **`unordered_map<int, list<int>::iterator> mp`**: This map
 *               provides O(1) average time complexity for checking if a page
 *               is in the cache. It stores the page number as the key and an
 *               iterator to the page's position in the list as the value.
 *           2.  **`list<int> lru`**: This list maintains the order of pages by
 *               recency. The front of the list is the most recently used (MRU)
 *               page, and the back is the least recently used (LRU) page.
 *
 *           For each page access:
 *           -   **Cache Hit:** If the page is found in the map, we use its
 *               iterator to move it to the front of the list, marking it as
 *               the MRU.
 *           -   **Cache Miss (Page Fault):** If the page is not in the map, we
 *               increment the fault count. If the cache is full, we evict the
 *               LRU page (from the back of the list and the map). Then, we add
 *               the new page to the front of the list and update the map.
 *
 * Time Complexity: O(N)
 * Space Complexity: O(C), where C is the cache capacity.
 */

#include <algorithm>
#include <iostream>
#include <list>
#include <unordered_map>
#include <vector>

using namespace std;

int pageFaults(const vector<int>& pages, int N, int C);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, c;
    cin >> n >> c;

    vector<int> pages(n);
    for (int i = 0; i < n; i++) cin >> pages[i];

    cout << "Capacity: " << c << endl;
    cout << "Pages: [ ";
    for (int i : pages) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Page Faults: " << pageFaults(pages, n, c) << endl;
  }

  return 0;
}

int pageFaults(const vector<int>& pages, int N, int C) {
  list<int> lru;
  unordered_map<int, list<int>::iterator> mp;
  int faults = 0;

  for (int page : pages) {
    // Cache Hit: Page is already in the cache.
    if (mp.find(page) != mp.end()) {
      auto it = mp[page];
      // Move the accessed page to the front (most recently used).
      lru.splice(lru.begin(), lru, it);
    } else {
      // Cache Miss: Page fault occurs.
      faults++;
      // If the cache is full, evict the least recently used page.
      if (lru.size() >= C) {
        mp.erase(lru.back());
        lru.pop_back();
      }
      // Add the new page to the front of the cache.
      lru.push_front(page);
      mp[page] = lru.begin();
    }
  }

  return faults;
}
