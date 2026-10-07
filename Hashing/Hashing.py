"""Double polynomial prefix hashes using bases 29 and 31."""


class Hash:
    def __init__(self, text, modulus=1_000_000_007):
        self.text = text
        self.modulus = modulus
        self.prefix = []
        self.powers = []
        for base in (29, 31):
            prefix, powers = [0], [1]
            for character in text:
                prefix.append(
                    (prefix[-1] * base + ord(character) - ord("a") + 1) % modulus
                )
                powers.append(powers[-1] * base % modulus)
            self.prefix.append(prefix)
            self.powers.append(powers)

    def get_hash(self, left=0, right=None):
        """Position-independent hash of the half-open substring [left, right)."""
        if right is None:
            right = len(self.text)
        return tuple(
            (prefix[right] - prefix[left] * powers[right - left]) % self.modulus
            for prefix, powers in zip(self.prefix, self.powers, strict=True)
        )
