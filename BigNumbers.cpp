#include <bits/stdc++.h>

using namespace std;

const int BASE = 1000000000; // podstawa
const int DIGS =
    9; // liczba cyfr dziesietnych kazdej cyfry w zapisie powyzszej podstawie
const int LEN = 1000; // stala dlugosc liczb

struct liczba {
  int t[LEN];
  int l; /* faktyczna dlugosc liczby */
};

void wypisz(liczba x) {
  printf("%d", x.t[x.l - 1]);
  for (int i = x.l - 2; i >= 0; i--)
    printf("%0*d", DIGS, x.t[i]);
}

void czytaj(liczba &x) {
  char s[LEN * DIGS + 1];
  scanf("%s", s); /* czytamy lancuch - zakladamy, ze nie ma zer wiodacych */
  /* Ustalamy dlugosc liczby */
  int j = strlen(s); /* pozycja w lancuchu s */
  if (j % DIGS == 0)
    x.l = j / DIGS;
  else
    x.l = j / DIGS + 1;
  j--;
  for (int i = 0; i < x.l; i++) {
    /* ustalamy i-ta cyfre */
    x.t[i] = 0;
    for (int k = max(0, j - DIGS + 1); k <= j; k++)
      x.t[i] = 10 * x.t[i] + (s[k] - '0');
    j -= DIGS;
  }
}

liczba operator+(liczba x, liczba y) {
  liczba z; /* wynik */
  /* Do dlugosci mniejszej z liczb: */
  z.l = min(x.l, y.l);
  int c = 0; /* na poczatek zerowy bit przeniesienia */
  for (int i = 0; i < z.l; i++) {
    z.t[i] = (x.t[i] + y.t[i] + c) % BASE;
    c = (x.t[i] + y.t[i] + c) / BASE;
  }
  /* Jezeli liczba x jest dluzsza: */
  while (z.l < x.l) {
    z.t[z.l] = (x.t[z.l] + c) % BASE;
    c = (x.t[z.l] + c) / BASE;
    z.l++;
  }
  /* Jezeli liczba y jest dluzsza: */
  while (z.l < y.l) {
    z.t[z.l] = (y.t[z.l] + c) % BASE;
    c = (y.t[z.l] + c) / BASE;
    z.l++;
  }
  /* Jezeli pozostalo jakies przeniesienie (to c=1): */
  if (c > 0) {
    z.t[z.l] = c;
    z.l++;
  }
  return z;
}

liczba operator-(liczba x, liczba y) {
  liczba z; /* wynik */
  z.l = x.l;
  int c = 0; /* nie ma pozyczki na poczatek */
  for (int i = 0; i < x.l; i++) {
    if (i < y.l) /* odjemnik sie jeszcze nie skonczyl */
      z.t[i] = x.t[i] - y.t[i] + c;
    else /* odjemnik sie skonczyl */
      z.t[i] = x.t[i] + c;
    if (z.t[i] < 0) /* musimy pozyczyc */
    {
      z.t[i] += BASE;
      c = -1;
    } else
      c = 0;
  }
  /* Ucinamy ewentualne zera wiodace */
  while (z.l > 1 && z.t[z.l - 1] == 0)
    z.l--;
  return z;
}

bool operator<(liczba x, liczba y) {
  if (x.l < y.l)
    return true;
  if (x.l > y.l)
    return false;
  int i = x.l - 1;
  while (i >= 0 && x.t[i] == y.t[i])
    i--;
  if (i < 0)
    return false;
  if (x.t[i] < y.t[i])
    return true;
  return false;
}

bool operator>(liczba x, liczba y) { return y < x; }

bool operator==(liczba x, liczba y) { return !(x < y) && !(y < x); }

/* Dla ulatwienia zalozmy, ze y nie jest zerem. */
liczba operator*(liczba x, int y) {
  liczba z;
  z.l = x.l;
  int c = 0;
  for (int i = 0; i < x.l; i++) {
    z.t[i] = int(((long long)(x.t[i]) * y + c) % BASE);
    c = int(((long long)(x.t[i]) * y + c) / BASE);
  }
  while (c > 0) {
    z.t[z.l] = c % BASE;
    c /= BASE;
    z.l++;
  }
  return z;
}

liczba operator*(liczba x, liczba y) {
  liczba z;
  z.l = 1;
  z.t[0] = 0; /* z to początkowo 0 */
  for (int i = 0; i < y.l; i++) {
    liczba pom(x * y.t[i]);
    /* przesuwamy liczbe pom, dodajac i zer na koncu */
    for (int j = pom.l - 1; j >= 0; j--)
      pom.t[j + i] = pom.t[j];
    for (int j = 0; j < i; j++)
      pom.t[j] = 0;
    pom.l = pom.l + i;
    z = z + pom;
  }
  return z;
}

int operator%(liczba x, int y) {
  long long z = (long long)(x.t[x.l - 1]) % y;
  for (int i = x.l - 2; i >= 0; i--)
    z = (z * BASE + x.t[i]) % y;
  return int(z);
}

liczba operator/(liczba x, int y) {
  liczba z;
  int c = 0; /* przeniesienie */
  z.l = x.l;
  for (int i = x.l - 1; i >= 0; i--) {
    z.t[i] = int(((long long)(c)*BASE + (long long)x.t[i]) / y);
    c = int(((long long)(c)*BASE + (long long)x.t[i]) % y);
  }
  /* Usuwamy ewentualne nowopowstale zera wiodace */
  while (z.l > 1 && z.t[z.l - 1] == 0)
    z.l--;
  return z;
}

signed main() {
  ios_base::sync_with_stdio(0);
  cin.tie(0);
  liczba a, b;
  czytaj(a);
  czytaj(b);
  cout << (a < b) << "\n";
  return 0;
}
