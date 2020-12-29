#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define pocz first
#define kon second.first
#define poz second.second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6 + 2;
const int R = 23;

pair<int,pii> A[N];
int KMR[N][R];
void kmr(string s) {
    int n = s.size() - 1;
    int r = log2(n) + 1, pot = 1;
    FOR(i, 1, n) {
        KMR[i][0] = s[i] - 'a' + 1;
    }
    FOR(k, 1, r) {
        FOR(i, 1, n) {
            if(i + pot > n) A[i] = { KMR[i][k - 1], {-1, i} };
            else A[i] = { KMR[i][k - 1], {KMR[i + pot][k - 1], i} };
        }
        sort(A + 1, A + (n + 1));
        int kl = 0;
        pii p = {-1,-1}, a; // poprzedni element
        FOR(i, 1, n) {
            a = {A[i].pocz, A[i].kon};
            if(p != a) {
                p = a;
                ++kl;
            }
            KMR[A[i].poz][k] = kl;
        }
        pot *= 2;
    }
    cout<<"KMR:\n"; FOR(k, 0, r) { FOR(i, 1, n) cout<<KMR[i][k]<<" "; cout<<"\n"; } // wypisz tablice
}

int SA[N], RANK[N]; // SA - przechowuje informacje o kolejnosci w SA, RANK - informuje ktory leksykograficznie jest ity sufiks
void sa(string s) { // suffix array
    int n = s.size() - 1;
    int r = log2(n) + 1; // ostatnia warstwa KMR
    FOR(i, 1, n) {
        SA[KMR[i][r]] = i;
        RANK[i] = KMR[i][r]; // RANK pomaga przy nawigacji po SA, jest to odwrotnosc SA
    }
    cout<<"SA:\n";
    FOR(i, 1, n) {
        cout<<SA[i]<<": ";
        FOR(j, SA[i], n) cout<<s[j]; cout<<"\n";
    }
    cout<<"RANK:\n";
    FOR(i, 1, n) cout<<RANK[i]<<" "; cout<<"\n";
}

int LCP[N];

int czescwspolna(string s, int a, int b) {
    int n = s.size() - 1, i = 0;
    while(a + i <= n && b + i <= n) {
        if(s[a + i] != s[b + i]) break;
        ++i;
    }
    return i;
}

void lcp(string s) { // longest common prefix
    int n = s.size() - 1;
    FOR(i, 1, n) {
        if(RANK[i] == 1) LCP[1] = -1; // jezeli jest pierwszy leksykograficznie to -1 bo nie ma dla niego pary
        else LCP[RANK[i]] = czescwspolna(s, i, SA[RANK[i] - 1]);
    }
    cout<<"LCP:\n"; FOR(i, 1, n) cout<<LCP[i]<<" "; cout<<"\n";
}

int porownaj(int a, int b, int c, int d) { // 0 - s(a,b) < s(c,d), 1 - s(a,b) == s(c,d), 2 - s(a,b) > s(c,d)
    int n = b - a + 1, m = d - c + 1, pot = 1, pota = -1, potb = -1, qa, qb;
    bool oa = 0, ob = 0;
    FOR(i, 2, 20) {
        pot *= 2;
        if(pot > n && !oa) {
            pota = pot / 2;
            qa = i - 2; // nie jestem pewny dlaczego i - 2, a nie i - 1
            oa = 1;
        }
        if(pot > m && !ob) {
            potb = pot / 2;
            qb = i - 2; // ^^^ (same here lulz)
            ob = 1;
        }
        if(pot > n && pot > m ) break;
    }
    pii x, y;
    x = {KMR[a][qa], KMR[b - pota + 1][qa]};
    y = {KMR[c][qb], KMR[d - potb + 1][qb]};
    if(x < y) return 0;
    else if(x == y) return 1;
    else return 2;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    string s;
    cin>>s;
    //cin>>a>>b>>c>>d;
    s = "#" + s;
    kmr(s);
    sa(s);
    lcp(s);
    return 0;
}