"""Linear-time odd and even palindrome radii."""


def manacher(text):
    """odd[i] includes center i; even[i] is centered just before i."""
    size = len(text)
    odd, even = [0] * size, [0] * size
    left, right = 0, -1
    for center in range(size):
        radius = (
            1 if center > right else min(odd[left + right - center], right - center + 1)
        )
        while (
            center - radius >= 0
            and center + radius < size
            and text[center - radius] == text[center + radius]
        ):
            radius += 1
        odd[center] = radius
        if center + radius - 1 > right:
            left, right = center - radius + 1, center + radius - 1
    left, right = 0, -1
    for center in range(size):
        radius = (
            0
            if center > right
            else min(even[left + right - center + 1], right - center + 1)
        )
        while (
            center - radius - 1 >= 0
            and center + radius < size
            and text[center - radius - 1] == text[center + radius]
        ):
            radius += 1
        even[center] = radius
        if center + radius - 1 > right:
            left, right = center - radius, center + radius - 1
    return odd, even
