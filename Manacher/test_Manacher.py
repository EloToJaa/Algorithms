import random
import unittest

from Manacher.Manacher import manacher


class TestManacher(unittest.TestCase):
    def test_against_center_expansion(self):
        rng = random.Random(6)
        for _ in range(100):
            text = "".join(rng.choices("abc", k=rng.randrange(40)))
            odd, even = [], []
            for i in range(len(text)):
                radius = 1
                while (
                    i - radius >= 0
                    and i + radius < len(text)
                    and text[i - radius] == text[i + radius]
                ):
                    radius += 1
                odd.append(radius)
                radius = 0
                while (
                    i - radius - 1 >= 0
                    and i + radius < len(text)
                    and text[i - radius - 1] == text[i + radius]
                ):
                    radius += 1
                even.append(radius)
            self.assertEqual(manacher(text), (odd, even))


if __name__ == "__main__":
    unittest.main()
