"""Interval greedies: merge, insert, minimum removals, and minimum meeting rooms."""

import heapq
from collections.abc import Sequence


def merge_intervals(intervals: Sequence[Sequence[int]]) -> list[list[int]]:
    """Merge closed [start, end] intervals; touching ones such as [1, 2], [2, 3] merge."""
    merged: list[list[int]] = []
    for start, end in sorted(intervals):
        if merged and start <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], end)
            continue
        merged.append([start, end])
    return merged


def insert_interval(
    intervals: Sequence[Sequence[int]], new: Sequence[int]
) -> list[list[int]]:
    """Insert closed new into sorted disjoint closed intervals; touching ones merge."""
    start, end = new
    result: list[list[int]] = []
    i, n = 0, len(intervals)
    while i < n and intervals[i][1] < start:
        result.append(list(intervals[i]))
        i += 1
    while i < n and intervals[i][0] <= end:
        start = min(start, intervals[i][0])
        end = max(end, intervals[i][1])
        i += 1
    result.append([start, end])
    result.extend(list(interval) for interval in intervals[i:])
    return result


def erase_overlap_intervals(intervals: Sequence[Sequence[int]]) -> int:
    """Fewest removals leaving half-open [start, end) intervals pairwise disjoint."""
    kept, last_end = 0, None
    for start, end in sorted(intervals, key=lambda interval: interval[1]):
        if last_end is not None and start < last_end:
            continue
        kept += 1
        last_end = end
    return len(intervals) - kept


def min_meeting_rooms(intervals: Sequence[Sequence[int]]) -> int:
    """Rooms needed for half-open [start, end) meetings: a room frees at its end."""
    ends: list[int] = []  # min-heap of end times of rooms in use
    for start, end in sorted(intervals):
        if ends and ends[0] <= start:
            heapq.heapreplace(ends, end)
        else:
            heapq.heappush(ends, end)
    return len(ends)
