/*
 * Problem: Intersection of Two Linked Lists (LeetCode #160)
 * Link:
 * https://leetcode.com/problems/intersection-of-two-linked-lists/description/
 */

#include <algorithm>
#include <iostream>

using namespace std;

struct ListNode {
 public:
  int val;
  ListNode* next;
  ListNode(int x) : val(x), next(NULL) {}
};

/**
 * Approach: This method aligns the starting points of the two lists.
 *           1. Calculate the lengths of both lists (lenA, lenB).
 *           2. Determine the length difference `k`.
 *           3. Advance the pointer of the longer list by `k` nodes.
 *           4. Now, both pointers are equidistant from the end. Traverse them
 *              together. The node where they meet is the intersection.
 *
 * Time Complexity: O(M + N)
 * Space Complexity: O(1)
 */
ListNode* lengthDiffApproach(ListNode* headA, ListNode* headB);

/**
 * Approach: This elegant approach uses two pointers that traverse both lists.
 *           When a pointer reaches the end of its list, it "jumps" to the
 *           head of the other list. This ensures that after the first pass,
 *           both pointers have the same distance to travel to the end. They
 *           will meet at the intersection point on the second pass. If there's
 *           no intersection, they will both become NULL at the same time.
 *
 * Time Complexity: O(M + N)
 * Space Complexity: O(1)
 */
ListNode* pointerJumpApproach(ListNode* headA, ListNode* headB);

/**
 * Approach: This creative approach transforms the problem into a cycle
 *           detection problem. It is destructive and restores the list later.
 *           1. Reverse list A. The original head of A is now its tail.
 *           2. Connect the new tail of A (original head) to the head of B. If
 *              the lists intersect, this creates a cycle.
 *           3. Use Floyd's cycle-finding algorithm to find the start of the
 *              cycle, which is the intersection node.
 *           4. Restore list A by breaking the cycle and reversing it again.
 *
 * Time Complexity: O(M + N)
 * Space Complexity: O(1)
 */
ListNode* cycleApproach(ListNode* headA, ListNode* headB);
ListNode* reverseList(ListNode* head);
ListNode* detectCycle(ListNode* head);

int main() {
  int t;
  cin >> t;

  while (t--) {
    int a, b, c;
    cin >> a >> b >> c;

    // 1. Build common part
    ListNode* commonHead = NULL;
    if (c > 0) {
      ListNode* dummy = new ListNode(0);
      ListNode* temp = dummy;
      for (int i = 0; i < c; i++) {
        int x;
        cin >> x;
        temp->next = new ListNode(x);
        temp = temp->next;
      }
      commonHead = dummy->next;
      delete dummy;
    }

    // 2. Build list A
    ListNode* headA = NULL;
    ListNode* dummyA = new ListNode(0);
    ListNode* tempA = dummyA;
    if (a > 0) {
      for (int i = 0; i < a; i++) {
        int x;
        cin >> x;
        tempA->next = new ListNode(x);
        tempA = tempA->next;
      }
    }
    tempA->next = commonHead;
    headA = dummyA->next;
    delete dummyA;

    // 3. Build list B
    ListNode* headB = NULL;
    ListNode* dummyB = new ListNode(0);
    ListNode* tempB = dummyB;
    if (b > 0) {
      for (int i = 0; i < b; i++) {
        int x;
        cin >> x;
        tempB->next = new ListNode(x);
        tempB = tempB->next;
      }
    }
    tempB->next = commonHead;
    headB = dummyB->next;
    delete dummyB;

    // Uncomment the approach to be used.
    ListNode* intersection = pointerJumpApproach(headA, headB);
    // ListNode* intersection = lengthDiffApproach(headA, headB);
    // ListNode* intersection = cycleApproach(headA, headB);

    if (intersection) {
      cout << "Intersection found at node with value: " << intersection->val
           << endl;
    } else {
      cout << "No intersection found." << endl;
    }

    // Clean up memory correctly to avoid double-freeing.
    // Delete unique part of A
    ListNode* curr = headA;
    while (curr != NULL && curr != intersection) {
      ListNode* toDelete = curr;
      curr = curr->next;
      delete toDelete;
    }
    // Delete unique part of B
    curr = headB;
    while (curr != NULL && curr != intersection) {
      ListNode* toDelete = curr;
      curr = curr->next;
      delete toDelete;
    }
    // Delete common part
    curr = intersection;
    while (curr != NULL) {
      ListNode* toDelete = curr;
      curr = curr->next;
      delete toDelete;
    }
    cout << endl;
  }

  return 0;
}

//---------------------------LENGTH-DIFF APPROACH-------------------------------
ListNode* lengthDiffApproach(ListNode* headA, ListNode* headB) {
  int lengthA = 0;
  ListNode* iterA = headA;
  while (iterA != NULL) {
    lengthA++;
    iterA = iterA->next;
  }

  int lengthB = 0;
  ListNode* iterB = headB;
  while (iterB != NULL) {
    lengthB++;
    iterB = iterB->next;
  }

  // Ensure headA is longer list.
  if (lengthB > lengthA) {
    swap(headA, headB);
    swap(lengthA, lengthB);
  }

  int k = lengthA - lengthB;
  iterA = headA;
  for (int i = 0; (i < k && iterA != NULL); i++) {
    iterA = iterA->next;
  }
  iterB = headB;

  while (iterA != iterB) {
    iterA = iterA->next;
    iterB = iterB->next;
  }

  return iterA;
}

//----------------------------POINTER-JUMP APPROACH-----------------------------
ListNode* pointerJumpApproach(ListNode* headA, ListNode* headB) {
  if (headA == NULL || headB == NULL) return NULL;

  ListNode* iterA = headA;
  ListNode* iterB = headB;

  while (iterA != iterB) {
    iterA = (iterA == NULL) ? headB : iterA->next;
    iterB = (iterB == NULL) ? headA : iterB->next;
  }

  return iterA;
}

//-------------------------------CYCLE APPROACH---------------------------------
ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
  // Get tail of listA
  ListNode* tailA = headA;
  while (tailA->next != NULL) {
    tailA = tailA->next;
  }
  // Create a loop.
  tailA->next = headB;

  ListNode* intersectionNode = detectCycle(headA);

  // Break loop.
  tailA->next = NULL;

  return intersectionNode;
}

ListNode* detectCycle(ListNode* head) {
  if (head == NULL || head->next == NULL) return NULL;
  if (head->next == head) return head;

  ListNode* slow = head;
  ListNode* fast = head;

  while (fast != NULL && fast->next != NULL) {
    slow = slow->next;
    fast = fast->next->next;
    if (slow == fast) {
      slow = head;
      while (slow != fast) {
        slow = slow->next;
        fast = fast->next;
      }
      return slow;
    }
  }

  return NULL;
}
