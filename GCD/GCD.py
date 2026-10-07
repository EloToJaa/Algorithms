"""Euclid and extended Euclid, including signed and zero inputs."""


def gcd(first, second):
    first, second = abs(first), abs(second)
    while second:
        first, second = second, first % second
    return first


def extended_gcd(first, second):
    """Return (g, x, y), where g >= 0 and first*x + second*y == g."""
    old_r, remainder = abs(first), abs(second)
    old_x, x, old_y, y = 1, 0, 0, 1
    while remainder:
        quotient = old_r // remainder
        old_r, remainder = remainder, old_r - quotient * remainder
        old_x, x = x, old_x - quotient * x
        old_y, y = y, old_y - quotient * y
    return old_r, old_x if first >= 0 else -old_x, old_y if second >= 0 else -old_y
