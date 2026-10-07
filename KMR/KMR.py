"""Karp-Miller-Rosenberg doubling ranks, suffix array, and LCP."""


class KMR:
    def __init__(self, text):
        self.text = text
        size = len(text)
        alphabet = {char: rank for rank, char in enumerate(sorted(set(text)), 1)}
        self.levels = [[alphabet[char] for char in text]]
        width = 1
        while width < size:
            previous = self.levels[-1]
            pairs = [
                (previous[i], previous[i + width] if i + width < size else -1)
                for i in range(size)
            ]
            ranks = {pair: rank for rank, pair in enumerate(sorted(set(pairs)), 1)}
            self.levels.append([ranks[pair] for pair in pairs])
            width *= 2
        self.suffix_array = sorted(
            range(size), key=lambda index: self.levels[-1][index]
        )
        self.rank = [0] * size
        for position, index in enumerate(self.suffix_array):
            self.rank[index] = position
        # Kasai's algorithm avoids the original quadratic LCP scan.
        self.lcp = [0] * size
        common = 0
        for index in range(size):
            position = self.rank[index]
            if position == 0:
                common = 0
                continue
            previous = self.suffix_array[position - 1]
            while (
                index + common < size
                and previous + common < size
                and text[index + common] == text[previous + common]
            ):
                common += 1
            self.lcp[position] = common
            common = max(0, common - 1)

    def compare(self, left, right, other_left, other_right):
        """Compare half-open substrings: 0 = less, 1 = equal, 2 = greater."""
        first_length, second_length = right - left, other_right - other_left
        shared = min(first_length, second_length)
        for level in range(len(self.levels) - 1, -1, -1):
            width = 1 << level
            if (
                width > shared
                or self.levels[level][left] != self.levels[level][other_left]
            ):
                continue
            left += width
            other_left += width
            shared -= width
        if shared:
            first, second = self.text[left], self.text[other_left]
        else:
            first, second = first_length, second_length
        return 0 if first < second else 2 if first > second else 1
