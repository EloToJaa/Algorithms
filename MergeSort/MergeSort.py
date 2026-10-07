"""Stable merge sort using one auxiliary buffer."""


def merge_sort(values):
    """Return a sorted copy; leave the input unchanged."""
    result = list(values)
    auxiliary = result.copy()

    def sort(left, right):
        if right - left <= 1:
            return
        middle = (left + right) // 2
        sort(left, middle)
        sort(middle, right)
        auxiliary[left:right] = result[left:right]
        first, second = left, middle
        for position in range(left, right):
            if second == right or (
                first < middle and auxiliary[first] <= auxiliary[second]
            ):
                result[position] = auxiliary[first]
                first += 1
            else:
                result[position] = auxiliary[second]
                second += 1

    sort(0, len(result))
    return result
