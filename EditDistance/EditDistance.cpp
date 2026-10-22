#include <bits/stdc++.h>

// table[i][j] is the edit distance between a[0, i) and b[0, j).
std::vector<std::vector<int>> editDistanceTable(const std::string &a,
                                                const std::string &b) {
  int n = a.size(), m = b.size();
  std::vector<std::vector<int>> table(n + 1, std::vector<int>(m + 1));
  for (int i = 0; i <= n; ++i)
    table[i][0] = i;
  for (int j = 0; j <= m; ++j)
    table[0][j] = j;
  for (int i = 1; i <= n; ++i)
    for (int j = 1; j <= m; ++j)
      table[i][j] = a[i - 1] == b[j - 1]
                        ? table[i - 1][j - 1]
                        : 1 + std::min({table[i - 1][j - 1], table[i - 1][j],
                                        table[i][j - 1]});
  return table;
}

// type is 'K'eep, 'R'eplace, 'D'elete, or 'I'nsert; from/to are the
// consumed and produced characters ('\0' when absent).
struct EditOp {
  char type, from, to;
};

// One optimal alignment consuming a and producing b, left to right.
std::vector<EditOp> editOperations(const std::string &a, const std::string &b) {
  auto table = editDistanceTable(a, b);
  std::vector<EditOp> ops;
  int i = a.size(), j = b.size();
  while (i > 0 || j > 0) {
    bool both = i > 0 && j > 0;
    if (both && a[i - 1] == b[j - 1]) {
      ops.push_back({'K', a[i - 1], b[j - 1]});
      --i, --j;
    } else if (both && table[i][j] == table[i - 1][j - 1] + 1) {
      ops.push_back({'R', a[i - 1], b[j - 1]});
      --i, --j;
    } else if (i > 0 && table[i][j] == table[i - 1][j] + 1) {
      ops.push_back({'D', a[i - 1], '\0'});
      --i;
    } else {
      ops.push_back({'I', '\0', b[j - 1]});
      --j;
    }
  }
  std::reverse(ops.begin(), ops.end());
  return ops;
}

// Distance only with one row of length min(n, m) + 1.
int editDistance(std::string a, std::string b) {
  if (a.size() < b.size())
    std::swap(a, b);
  std::vector<int> row(b.size() + 1);
  std::iota(row.begin(), row.end(), 0);
  for (size_t i = 1; i <= a.size(); ++i) {
    int diagonal = row[0];
    row[0] = i;
    for (size_t j = 1; j <= b.size(); ++j) {
      int above = row[j];
      row[j] = a[i - 1] == b[j - 1]
                   ? diagonal
                   : 1 + std::min({diagonal, above, row[j - 1]});
      diagonal = above;
    }
  }
  return row.back();
}
