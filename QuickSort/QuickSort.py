"""Quicksort with a middle pivot moved to the partition's final slot."""


def quick_sort(values):
    """Return a sorted copy using an explicit stack and Lomuto partitioning."""
    result = list(values)
    stack = [(0, len(result) - 1)]
    while stack:
        left, right = stack.pop()
        if left >= right:
            continue
        middle = (left + right) // 2
        result[middle], result[right] = result[right], result[middle]
        pivot = result[right]
        position = left
        for index in range(left, right):
            if result[index] < pivot:
                result[position], result[index] = result[index], result[position]
                position += 1
        result[position], result[right] = result[right], result[position]
        # Process the smaller side first, keeping the explicit stack small.
        parts = [(left, position - 1), (position + 1, right)]
        parts.sort(key=lambda part: part[1] - part[0], reverse=True)
        stack.extend(parts)
    return result
