# Intervals

Sort-based greedies for merging, inserting, pruning overlaps, and counting meeting rooms.

## My solution

- `merge_intervals` (closed): sort by start; each interval either extends the last merged one (`start <= last_end`, so touching intervals merge) or opens a new one. After sorting, only the last merged interval can still overlap anything.
- `insert_interval` (closed, input sorted and disjoint): three linear phases — copy intervals ending before `new` starts, absorb every interval starting at or before the growing `new` end, then copy the rest. No sort needed, so O(n).
- `erase_overlap_intervals` (half-open): equivalent to keeping the most disjoint intervals. Sort by end and keep greedily: the interval finishing first leaves the most room for the rest (exchange argument), and anything starting before the last kept end must go.
- `min_meeting_rooms` (half-open): sort by start and keep a min-heap of end times of busy rooms. If the earliest-ending room is free by `start`, reuse it (`heapreplace`); otherwise open a room. The heap size is the answer. Sweep-line alternative: sort starts and ends separately and walk both with two pointers (or `+1` at start, `-1` at end, ends before starts on ties); the peak count is the same answer without a heap.

## Complexity

O(n log n) time for merge, removals, and rooms (sorting dominates); O(n) for insert. O(n) space for outputs and the heap.

## Usage and assumptions

Intervals are `[start, end]` pairs of integers. `merge_intervals` and `insert_interval` treat them as closed, so `[1, 2]` and `[2, 3]` merge; `insert_interval` expects a sorted, disjoint input and returns a new list. `erase_overlap_intervals` and `min_meeting_rooms` treat them as half-open `[start, end)`, so a meeting ending at 10 frees its room for one starting at 10. C++ `mergeIntervals`, `insertInterval`, `eraseOverlapIntervals`, and `minMeetingRooms` use `std::pair<int, int>` intervals with the same conventions.

```python
from Intervals.Intervals import (
    erase_overlap_intervals,
    insert_interval,
    merge_intervals,
    min_meeting_rooms,
)

merge_intervals([[1, 3], [2, 6], [8, 10], [15, 18]]) == [[1, 6], [8, 10], [15, 18]]
insert_interval([[1, 3], [6, 9]], [2, 5]) == [[1, 5], [6, 9]]
erase_overlap_intervals([[1, 2], [2, 3], [3, 4], [1, 3]]) == 1
min_meeting_rooms([[0, 30], [5, 10], [15, 20]]) == 2
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [56. Merge Intervals](https://leetcode.com/problems/merge-intervals/)
- [57. Insert Interval](https://leetcode.com/problems/insert-interval/)
- [435. Non-overlapping Intervals](https://leetcode.com/problems/non-overlapping-intervals/)
- [253. Meeting Rooms II](https://leetcode.com/problems/meeting-rooms-ii/) — premium
- [252. Meeting Rooms](https://leetcode.com/problems/meeting-rooms/) — premium; rooms needed is at most 1
- [452. Minimum Number of Arrows to Burst Balloons](https://leetcode.com/problems/minimum-number-of-arrows-to-burst-balloons/) — same greedy by end, closed intervals
- [986. Interval List Intersections](https://leetcode.com/problems/interval-list-intersections/) — two pointers over sorted lists
- [1094. Car Pooling](https://leetcode.com/problems/car-pooling/) — sweep line with capacities

## Tests

[`test_Intervals.py`](test_Intervals.py) checks the Python implementation; [`test_Intervals.cpp`](test_Intervals.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Intervals -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
