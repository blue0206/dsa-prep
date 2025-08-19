/*
 * Problem: Book Allocation
 * Link:
 * https://www.codechef.com/practice/course/nutanix-interview-questions/NUTANIXCON01/problems/NUTANIX06
 *
 * Approach: This is a variation of the "Binary Search on Answer" problem. We
 *           aim to find the minimum possible value of the maximum number of
 *           pages allocated to a student, such that all books are allocated
 *           and the number of students does not exceed 'm'.
 *           1. **Define Search Space:** The minimum possible value for the
 *              maximum number of pages is the largest book size and the maximum
 *              possible value is the sum of all book sizes. Therefore, the
 *              search space is defined within this range.
 *           2. **Binary Search:** Apply binary search to find a possible
 *              minimum value. For every mid value, check if it's possible to
 *              allocate the books to 'm' students such that no student gets
 *              more than 'mid' pages.
 *           3. **Feasibility Check:** The `countAllocations` function checks
 *              greedily if it's possible to allocate books such that the
 *              maximum number of pages assigned to a student is no more than
 *              'mid'. It returns the number of students required for a given
 *              'mid'.
 *           4. **Adjust Search Space:** If the number of students required is
 *              less than or equal to 'm', it means we can try to minimize the
 *              maximum number of pages, so we search on the left half.
 *              Otherwise, we search on the right half.
 *
 * Time Complexity: O(N log(Sum of pages))
 * Space Complexity: O(1)
 */

#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

int allocateBooks(vector<int>& books, int m);
int countAllocations(vector<int>& books, int mid);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n, m;
    cin >> n >> m;
    vector<int> nums(n);
    for (int i = 0; i < n; i++) cin >> nums[i];

    cout << "Array: [ ";
    for (auto i : nums) {
      cout << i << " ";
    }
    cout << "]" << endl;

    cout << "Minimum Possible Maximum Pages: " << allocateBooks(nums, m)
         << endl;

    cout << endl;
  }

  return 0;
}

int allocateBooks(vector<int>& books, int m) {
  if (m > books.size()) {
    return -1;
  }

  int low = books[0];
  int high = 0;

  for (int i = 0; i < books.size(); i++) {
    if (books[i] > low) {
      low = books[i];
    }
    high += books[i];
  }

  while (low <= high) {
    int mid = low + (high - low) / 2;

    int allocations = countAllocations(books, mid);
    if (allocations <= m) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }

  return low;
}

int countAllocations(vector<int>& books, int mid) {
  int allocations = 1;
  int pages = 0;

  for (int i = 0; i < books.size(); i++) {
    if (pages + books[i] <= mid) {
      pages += books[i];
    } else {
      allocations++;
      pages = books[i];
    }
  }

  return allocations;
}
