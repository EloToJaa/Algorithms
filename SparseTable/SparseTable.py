"""Static range minima with overlapping power-of-two blocks."""

from collections.abc import Sequence


class SparseTable:
    def __init__(self, values: Sequence[float]) -> None:
        self.size = len(values)
        self.levels = [list(values)]
        width = 2
        while width <= self.size:
            previous = self.levels[-1]
            half = width // 2
            self.levels.append(
                [
                    min(previous[i], previous[i + half])
                    for i in range(self.size - width + 1)
                ]
            )
            width *= 2

    def query(self, left: int, right: int) -> float:
        """Minimum of the zero-based inclusive interval [left, right]."""
        if not 0 <= left <= right < self.size:
            raise ValueError("invalid range")
        level = (right - left + 1).bit_length() - 1
        return min(
            self.levels[level][left], self.levels[level][right - (1 << level) + 1]
        )
