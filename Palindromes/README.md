# Palindrome DPs

Quadratic interval DPs for palindromic substrings, the longest palindromic subsequence, and minimum palindrome partitioning.

## My solution

- `palindrome_table`: `text[i..j]` is a palindrome when its ends match and `text[i+1..j-1]` is one; fill i descending so the inner interval is ready.
- `longest_palindromic_subsequence`: on matching ends add 2 to the inner interval, otherwise drop one end.
- `min_palindrome_cuts`: `cuts[j]` is the answer for the first j characters, minimized over every palindromic last piece `text[i..j-1]`; `cuts[0] = -1` so one piece costs zero cuts.

For only the longest palindromic substring or per-center radii, [Manacher](../Manacher/README.md) is linear.

## Complexity

O(n^2) time and O(n^2) space for each function.

## Usage and assumptions

`palindrome_table(text)` returns an inclusive `table[i][j]`; `longest_palindromic_subsequence(text)` returns a length; `min_palindrome_cuts(text)` returns the fewest cuts (0 for empty text). Python accepts any sequence; C++ `palindromeTable`, `longestPalindromicSubsequence`, and `minPalindromeCuts` work on strings with zero-based indices.

```python
from Palindromes.Palindromes import longest_palindromic_subsequence, min_palindrome_cuts

longest_palindromic_subsequence("bbbab") == 4
min_palindrome_cuts("aab") == 1
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

New snippet.

## LeetCode problems

- [516. Longest Palindromic Subsequence](https://leetcode.com/problems/longest-palindromic-subsequence/)
- [132. Palindrome Partitioning II](https://leetcode.com/problems/palindrome-partitioning-ii/)
- [131. Palindrome Partitioning](https://leetcode.com/problems/palindrome-partitioning/) — backtrack using the table
- [647. Palindromic Substrings](https://leetcode.com/problems/palindromic-substrings/) — count true table entries
- [1312. Minimum Insertion Steps to Make a String Palindrome](https://leetcode.com/problems/minimum-insertion-steps-to-make-a-string-palindrome/) — n minus the longest subsequence

## Tests

[`test_Palindromes.py`](test_Palindromes.py) checks the Python implementation; [`test_Palindromes.cpp`](test_Palindromes.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Palindromes -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
