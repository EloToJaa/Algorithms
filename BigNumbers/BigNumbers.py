"""Unsigned arbitrary precision arithmetic using little-endian base-10^9 limbs."""

from __future__ import annotations

BASE = 1_000_000_000
DIGITS = 9


class BigNumber:
    def __init__(self, value: int | str = "0") -> None:
        text = str(value).lstrip("0") or "0"
        self.limbs = [
            int(text[max(0, end - DIGITS) : end])
            for end in range(len(text), 0, -DIGITS)
        ]

    @classmethod
    def _from_limbs(cls, limbs: list[int]) -> BigNumber:
        result = cls()
        result.limbs = limbs
        while len(result.limbs) > 1 and result.limbs[-1] == 0:
            result.limbs.pop()
        return result

    def __str__(self) -> str:
        return str(self.limbs[-1]) + "".join(
            f"{limb:09d}" for limb in reversed(self.limbs[:-1])
        )

    def __eq__(self, other: object) -> bool:
        if not isinstance(other, BigNumber):
            return NotImplemented
        return self.limbs == other.limbs

    def __lt__(self, other: BigNumber) -> bool:
        return (len(self.limbs), self.limbs[::-1]) < (
            len(other.limbs),
            other.limbs[::-1],
        )

    def __add__(self, other: BigNumber) -> BigNumber:
        limbs: list[int] = []
        carry = 0
        for index in range(max(len(self.limbs), len(other.limbs))):
            value = carry
            if index < len(self.limbs):
                value += self.limbs[index]
            if index < len(other.limbs):
                value += other.limbs[index]
            carry, limb = divmod(value, BASE)
            limbs.append(limb)
        if carry:
            limbs.append(carry)
        return self._from_limbs(limbs)

    def __sub__(self, other: BigNumber) -> BigNumber:
        """Unsigned subtraction: requires self >= other."""
        limbs: list[int] = []
        borrow = 0
        for index, limb in enumerate(self.limbs):
            value = (
                limb - borrow - (other.limbs[index] if index < len(other.limbs) else 0)
            )
            borrow = int(value < 0)
            limbs.append(value + borrow * BASE)
        return self._from_limbs(limbs)

    def __mul__(self, other: BigNumber | int) -> BigNumber:
        if isinstance(other, int):
            other = BigNumber(other)
        limbs = [0] * (len(self.limbs) + len(other.limbs))
        for first, a in enumerate(self.limbs):
            carry = 0
            for second, b in enumerate(other.limbs):
                carry, limbs[first + second] = divmod(
                    limbs[first + second] + a * b + carry, BASE
                )
            limbs[first + len(other.limbs)] = carry
        return self._from_limbs(limbs)

    def __divmod__(self, divisor: int) -> tuple[BigNumber, int]:
        """Long division by a positive integer; return (BigNumber, int)."""
        limbs, remainder = [0] * len(self.limbs), 0
        for index in range(len(self.limbs) - 1, -1, -1):
            limbs[index], remainder = divmod(
                remainder * BASE + self.limbs[index], divisor
            )
        return self._from_limbs(limbs), remainder

    def __floordiv__(self, divisor: int) -> BigNumber:
        return divmod(self, divisor)[0]

    def __mod__(self, divisor: int) -> int:
        return divmod(self, divisor)[1]
