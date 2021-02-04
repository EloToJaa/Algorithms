#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define SZ(x) (int)(x).size()
#define Nwd __gcd
#define pb push_back
#define st first
#define nd second
#define lc (v<<1)
#define rc (v<<1|1)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<int, ll> pil;
typedef pair<ll, int> pli;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if(0)
const int N = 1e6, NT = N + 2;

int NieParzyste[NT], Parzyste[NT];
void Manacher(string s) {
    int n = SZ(s), k, l = 0, r = -1;
    FOR(i, 0, n-1) {
        k = (i > r) ? 1: min(NieParzyste[l + r - i + 1], r - i + 1);
        while (0 <= i - k and i + k < n and s[i - k] == s[i + k]) k++;
        NieParzyste[i + 1] = k--;
        if (i + k > r) {
            l = i - k;
            r = i + k;
        }
    }
    l = 0, r = -1;
    FOR(i, 0, n-1) {
        k = (i > r) ? 0: min(Parzyste[l + r - i + 2], r - i + 1);
        while (0 <= i - k - 1 and i + k < n and s[i - k - 1] == s[i + k])k++;
        Parzyste[i + 1] = k--;
        if (i + k > r) {
            l = i - k - 1;
            r = i + k ;
        }
    }
}