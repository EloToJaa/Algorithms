# Trie / prefix tree

Store words while efficiently testing full-word and prefix membership.

## My solution

Each node stores transitions to child nodes and a word-ending flag. Insertion creates missing transitions; lookup follows them until the input is exhausted.

## Complexity

O(word_length) per operation and O(total_inserted_characters) nodes (C++ stores 26 transitions per node).

## Usage and assumptions

`Trie` provides `insert(word)`, `search(word)`, and `starts_with(prefix)`; C++ calls the latter `startsWith`. C++ requires lowercase a..z; Python dictionary transitions also support other characters. Empty words are supported, and the empty prefix always exists.

```python
from Trie.Trie import Trie

trie = Trie()
trie.insert("apple")
assert trie.starts_with("app") and not trie.search("app")
```

Run examples from the repository root. For examples written as expressions, evaluate them or prefix them with `assert`.

## C++ review

The original C++ implementation was retained and checked for prefixes, duplicates, and empty words.

## Tests

[`test_Trie.py`](test_Trie.py) checks the Python implementation; [`test_Trie.cpp`](test_Trie.cpp) covers C++ regressions. From the repository root run:

```sh
python3 -m unittest discover -s Trie -t . -p 'test_*.py'
python3 run_tests.py --cpp
```
