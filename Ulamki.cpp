#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define TRAV(x,T) for(auto& (x): (T))
#define ALL(x) x.begin(), x.end()
#define TAB(x,n) (x)+1, (x)+((n)+1)
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define pf push_front
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
const int N = 1e6 + 2;

int nww(int a, int b) {
    return a / nwd(a, b) * b;
}

class Ulamek {
    public:
    int calosc, licznik, mianownik, znak = 1; // gora, dol

    private:
    void skroc_ulamek() {
        if(licznik < 0 || calosc < 0) {
            znak *= -1;
            if(licznik < 0) licznik *= -1;
        }
        // skracanie
        int x = nwd(licznik, mianownik);
        licznik /= x;
        mianownik /= x;
        // wyrzucanie czesci calkowitej
        if(licznik >= mianownik) {
            calosc += (licznik / mianownik);
            licznik %= mianownik;
        }
    }
    void zmien_wartosc(int wejscie_a, int wejscie_b, int wejscie_c) {
        calosc = wejscie_a;
        licznik = wejscie_b;
        mianownik = wejscie_c;
        skroc_ulamek();
    }
    
    public:
    Ulamek() {}
    Ulamek(int licznik_w) {
        zmien_wartosc(0, licznik_w, 1);
    }
    Ulamek(int licznik_w, int mianownik_w) {
        zmien_wartosc(0, licznik_w, mianownik_w);
    }
    Ulamek(int calosc_w, int licznik_w, int mianownik_w) {
        zmien_wartosc(calosc_w, licznik_w, mianownik_w);
    }
    void ustaw(int licznik_w) {
        zmien_wartosc(0, licznik_w, 1);
    }
    void ustaw(int licznik_w, int mianownik_w) {
        zmien_wartosc(0, licznik_w, mianownik_w);
    }
    void ustaw(int calosc_w, int licznik_w, int mianownik_w) {
        zmien_wartosc(calosc_w, licznik_w, mianownik_w);
    }
    void ustaw(Ulamek ulamek_w) {
        zmien_wartosc(ulamek_w.calosc, ulamek_w.licznik, ulamek_w.mianownik);
        znak = ulamek_w.znak;
    }
};

bool operator< (Ulamek x, Ulamek y) {
    if(x.znak != y.znak)
        return x.znak < y.znak;
    if(x.calosc != y.calosc) {
        if(x.znak == -1) return x.calosc > y.calosc;
        else return x.calosc < y.calosc;
    }
    int a = x.licznik, b = x.mianownik, c = y.licznik, d = y.mianownik;
    int nw = nww(b, d);
    return (a * (nw / b)) < (c * (nw / d));
}

bool operator> (Ulamek x, Ulamek y) {
	return y < x;
}

bool operator== (Ulamek x, Ulamek y) {
	return !(x < y) && !(y < x);
}

Ulamek operator+ (Ulamek x, Ulamek y) {
    int a = x.licznik, b = x.mianownik, c = y.licznik, d = y.mianownik;
    int nw = nww(b, d);
    Ulamek wynik;
    if(x.znak == y.znak) {
        wynik.ustaw(x.calosc + y.calosc, a * (nw / b) + c * (nw / d), nw);
        if(x.znak == -1) wynik.znak = -1;
        return wynik;
    }
    if(x.znak == -1) { // (-x) + y
        //wynik.ustaw(y.calosc - x.calosc, )
        Ulamek por_x, por_y;
        por_x.ustaw(x);
        por_x.znak = 1; 
        por_y.ustaw(y);
        por_y.znak = 1;
        if(por_x < por_y) {
            Ulamek temp;
            temp.ustaw(x);
            x.ustaw(y);
            y.ustaw(temp);
        }
    }
    // x + (-y)
    return wynik;
}

Ulamek operator- (Ulamek x, Ulamek y) {
    y.znak *= -1;
    return x + y;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    Ulamek a(1, 2), b(2, 3);
    cout<<(a + b).calosc<<" "<<(a + b).licznik<<"/"<<(a + b).mianownik<<"\n";
    return 0;
}