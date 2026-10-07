"""Prefix-function construction and Knuth-Morris-Pratt matching."""


def prefix_function(text):
    prefix = [0] * len(text)
    for index in range(1, len(text)):
        length = prefix[index - 1]
        while length and text[index] != text[length]:
            length = prefix[length - 1]
        if text[index] == text[length]:
            length += 1
        prefix[index] = length
    return prefix


def find_matches(text, pattern):
    """Return all zero-based starts, including overlapping matches."""
    if not pattern:
        return list(range(len(text) + 1))
    prefix = prefix_function(pattern)
    length = 0
    matches = []
    for index, character in enumerate(text):
        while length and character != pattern[length]:
            length = prefix[length - 1]
        if character == pattern[length]:
            length += 1
        if length == len(pattern):
            matches.append(index - length + 1)
            length = prefix[length - 1]
    return matches
