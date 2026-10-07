"""Trie storing word endings and character-to-node transitions."""


class Trie:
    def __init__(self):
        self.children = [{}]
        self.endings = [False]

    def insert(self, word):
        node = 0
        for character in word:
            if character not in self.children[node]:
                self.children[node][character] = len(self.children)
                self.children.append({})
                self.endings.append(False)
            node = self.children[node][character]
        self.endings[node] = True

    def _walk(self, text):
        node = 0
        for character in text:
            node = self.children[node].get(character)
            if node is None:
                return None
        return node

    def search(self, word):
        node = self._walk(word)
        return node is not None and self.endings[node]

    def starts_with(self, prefix):
        return self._walk(prefix) is not None
