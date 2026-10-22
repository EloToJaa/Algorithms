# Sliding window

Variable-size windows over a sequence: longest window without repeats, minimum covering window, and at most / exactly k distinct values.

## My solution

Generic template, valid whenever validity is monotone (if `[l, r]` is valid, every inner window `[l', r']` is too, so the best left end never moves back):

```text
left = 0
for right in range(n):
    add(values[right])
    while window [left, right] is invalid:
        remove(values[left]); left += 1
    use(left, right)   # [left, right] is the longest valid window ending at right
```

Each index enters and leaves once, so the scan is linear. "Minimum" problems flip the loop: shrink while the window is still valid, recording the answer before each removal.

- `longest_unique_substring`: remember the last index of every value; on a repeat inside the window jump `left` past it directly instead of shrinking one step at a time.
- `min_window`: `need[c]` counts how many more `c` the window requires (negative means surplus) and `missing` how many pattern characters are still uncovered. Once `missing == 0`, drop surplus characters from the left, record the window, then drop one required character to search for the next cover.
- `at_most_k_distinct_windows`: the template with a counter whose size is the number of distinct values; yields the smallest valid `left` for every `right`.
- `longest_at_most_k_distinct`: maximum `right - left + 1` over those windows.
- `count_at_most_k_distinct`: every subarray ending at `right` that starts in `[left, right]` is valid, so add `right - left + 1`.
- `count_exactly_k_distinct`: "exactly k" is not monotone, but `exactly(k) = atMost(k) - atMost(k - 1)` is a difference of two monotone counts.

For the maximum or minimum inside a window, combine this with [MonoQueue](../MonoQueue/README.md).

## Complexity

O(n) time (expected, with hashing) for every function. O(distinct values) space; `min_window` is O(n + m) time.

## Usage and assumptions

`longest_unique_substring(values)` and `longest_at_most_k_distinct(values, k)` return lengths; `count_at_most_k_distinct(values, k)` and `count_exactly_k_distinct(values, k)` return subarray counts (exactly is 0 for `k <= 0`). `min_window(text, pattern)` returns the leftmost shortest substring of `text` containing every character of `pattern` with multiplicity, or `""` if none (or if `pattern` is empty). Python accepts any sequence of hashable values; C++ `longestUniqueSubstring` and `minWindow` work on byte strings, `longestAtMostKDistinct`, `countAtMostKDistinct`, and `countExactlyKDistinct` on `std::vector<int>` with `long long` counts.

```python
from SlidingWindow.SlidingWindow import (
    count_exactly_k_distinct,
    longest_unique_substring,
    min_window,
)

longest_unique_substring("abcabcbb") == 3
min_window("ADOBECODEBANC", "ABC") == "BANC"
count_exactly_k_distinct([1, 2, 1, 2, 3], 2) == 7
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [3. Longest Substring Without Repeating Characters](https://leetcode.com/problems/longest-substring-without-repeating-characters/)
- [76. Minimum Window Substring](https://leetcode.com/problems/minimum-window-substring/)
- [904. Fruit Into Baskets](https://leetcode.com/problems/fruit-into-baskets/) — longest window with at most 2 distinct
- [340. Longest Substring with At Most K Distinct Characters](https://leetcode.com/problems/longest-substring-with-at-most-k-distinct-characters/)
- [992. Subarrays with K Different Integers](https://leetcode.com/problems/subarrays-with-k-different-integers/) — atMost(k) - atMost(k - 1)
- [209. Minimum Size Subarray Sum](https://leetcode.com/problems/minimum-size-subarray-sum/) — positive values make the sum monotone
- [424. Longest Repeating Character Replacement](https://leetcode.com/problems/longest-repeating-character-replacement/)
- [1004. Max Consecutive Ones III](https://leetcode.com/problems/max-consecutive-ones-iii/) — at most k zeros

## Tests

[`test_SlidingWindow.py`](test_SlidingWindow.py) checks the Python implementation; [`test_SlidingWindow.cpp`](test_SlidingWindow.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s SlidingWindow -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
