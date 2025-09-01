/*
 * Problem: Merge k Sorted Lists (LeetCode #23)
 * Link: https://leetcode.com/problems/merge-k-sorted-lists/description/
 */

#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct ListNode {
 public:
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

using pil = pair<int, ListNode*>;
using vpil = vector<pil>;
using min_pil = priority_queue<pil, vpil, greater<pil>>;

/**
 * Approach: This approach uses a divide-and-conquer strategy, similar to
 *           Merge Sort. It recursively merges pairs of lists.
 *           1. The base case is when there's only one list to merge.
 *           2. The list of lists is split into two halves.
 *           3. The function is called recursively on both halves.
 *           4. The two sorted lists returned from the recursive calls are then
 *              merged using a standard two-pointer merge helper function.
 *
 * Time Complexity: O(N * log(k)), where N is the total number of nodes and k
 *                  is the number of lists.
 * Space Complexity: O(log(k)) for the recursion stack.
 */
ListNode* mergeSortApproach(vector<ListNode*>& lists);
ListNode* merge(ListNode* list1, ListNode* list2);
ListNode* mergeLists(vector<ListNode*>& lists, int low, int high);

/**
 * Approach: This approach uses a min-priority queue (min-heap) to efficiently
 *           find the smallest node among all the lists at any given time.
 *           1. A min-heap is created, and the head of each non-empty list is
 *              inserted.
 *           2. While the heap is not empty, the node with the smallest value
 *              is extracted, appended to the result list, and the next node
 *              from the same list is inserted into the heap.
 *
 * Time Complexity: O(N * log(k))
 * Space Complexity: O(k) for the min-heap.
 */
ListNode* minHeapApproach(vector<ListNode*>& lists);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int n;
    cin >> n;

    vector<ListNode*> lists(n);
    for (int i = 0; i < n; i++) {
      int m;
      cin >> m;

      ListNode* dummy = new ListNode(0);
      ListNode* temp = dummy;
      for (int j = 0; j < m; j++) {
        int x;
        cin >> x;
        temp->next = new ListNode(x);
        temp = temp->next;
      }
      ListNode* head = dummy->next;
      delete dummy;
      lists[i] = head;
    }

    cout << "Linked Lists: [ ";
    for (int i = 0; i < n; i++) {
      ListNode* temp = lists[i];
      cout << "[ ";
      while (temp != NULL) {
        cout << temp->val << " ";
        temp = temp->next;
      }
      cout << "] ";
    }
    cout << "]" << endl;

    // Uncomment the approach to be used.
    // ListNode* head = mergeSortApproach(lists);
    ListNode* head = minHeapApproach(lists);

    cout << "Merged and Sorted List: [ ";
    ListNode* temp = head;
    while (temp != NULL) {
      cout << temp->val << " ";
      temp = temp->next;
    }
    cout << "]" << endl;

    // Clean up.
    temp = head;
    while (temp != NULL) {
      ListNode* toDelete = temp;
      temp = temp->next;
      delete toDelete;
    }
    cout << endl;
  }

  return 0;
}

//----------------------------MERGE-SORT APPROACH-------------------------------
ListNode* mergeSortApproach(vector<ListNode*>& lists) {
  if (lists.size() == 0) return NULL;
  if (lists.size() == 1) return lists[0];

  return mergeLists(lists, 0, lists.size() - 1);
}

ListNode* merge(ListNode* list1, ListNode* list2) {
  ListNode* dummy = new ListNode(0);
  ListNode* iter = dummy;

  ListNode* l1 = list1;
  ListNode* l2 = list2;
  while (l1 != NULL && l2 != NULL) {
    if (l1->val <= l2->val) {
      iter->next = l1;
      iter = l1;
      l1 = l1->next;
    } else {
      iter->next = l2;
      iter = l2;
      l2 = l2->next;
    }
  }

  if (l1 != NULL) {
    iter->next = l1;
  }
  if (l2 != NULL) {
    iter->next = l2;
  }

  ListNode* newHead = dummy->next;
  delete dummy;
  return newHead;
}

ListNode* mergeLists(vector<ListNode*>& lists, int low, int high) {
  if (low == high) {
    return lists[low];
  }

  int mid = low + (high - low) / 2;
  ListNode* list1 = mergeLists(lists, low, mid);
  ListNode* list2 = mergeLists(lists, mid + 1, high);
  return merge(list1, list2);
}

//-----------------------------MIN-HEAP APPROACH-------------------------------
ListNode* minHeapApproach(vector<ListNode*>& lists) {
  if (lists.size() == 0) return NULL;
  if (lists.size() == 1) return lists[0];

  min_pil minHeap;
  for (int i = 0; i < lists.size(); i++) {
    // Store node in min heap if it exists.
    if (lists[i]) {
      minHeap.push({lists[i]->val, lists[i]});
    }
  }

  ListNode* dummy = new ListNode(0);
  ListNode* iter = dummy;
  while (!minHeap.empty()) {
    // Get the node with min value.
    ListNode* minNode = minHeap.top().second;
    // Pop the node from min-heap.
    minHeap.pop();

    // If the min node points to another node,
    // store that node in the heap.
    if (minNode->next != NULL) {
      ListNode* nextNode = minNode->next;
      minHeap.push({nextNode->val, nextNode});
      minNode->next = NULL;
    }

    // Add min node to the answer list.
    iter->next = minNode;
    iter = minNode;
  }

  ListNode* newHead = dummy->next;
  delete dummy;
  return newHead;
}
