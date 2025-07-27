# Hashing

Pre-store and fetch when required.

## Number Hashing

We can create an array and access indices as the number and value as its frequency.
However, this will only work if we know the upper limit of possible values and the
limit is within the following constraints:
- For type 'int', the max size with which array can be initialized is:
  - inside main: $10^6$
  - global: $10^7$
- For type 'bool', the max size with which array can be initialized is:
  - inside main: $10^7$
  - global: $10^8$

If the upper limit is not known or outside array limits, we use a Map.

### Map and Unordered Map

| Feature                  | `std::map` (Ordered Map)                                              | `std::unordered_map` (Hash Map)                                                                 |
| :----------------------- | :-------------------------------------------------------------------- | :---------------------------------------------------------------------------------------------- |
| **Time Complexity**      | O(log N) for insertions, deletions, and lookups.                      | O(1) on best and average. O(N) in the worst case (due to hash collisions).                      |
| **Ordering**             | Keys are stored in sorted order.                                      | No guaranteed order of elements.                                                                |
| **Key Requirements**     | Keys must have a strict weak ordering comparison (e.g., `operator<`). | Keys must be hashable. Most built-in types are; custom structs/classes require a hash function. |
| **Underlying Structure** | Self-Balancing Binary Search Tree (typically a Red-Black Tree)        | Hash Table                                                                                      |

## Character Hashing

We create an array and treat its index numbers as ASCII values. there are a total
of 256 ASCII values (0-255).
Therefore, we can always use an array in this case as the the number of characters
can at most be only 256 which is easily within limits, unlike with numbers.
