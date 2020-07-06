#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i=(a); i<=(b); ++i)
#define FORD(i,a,b) for(int i=(a); i>=(b); --i)
#define TRAV(x,T) for(auto& (x): (T))
#define ALL(x) x.begin(), x.end()
#define TAB(x,n) (x)+1, (x)+((n)+1) 
#define sz(x) (int)(x).size()
#define pb push_back
#define pf push_front
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
const int N = 1e6;

int A[N + 2], ILE[N + 2], ANS[N + 2];
struct zap { int x, y, id; } Q[N + 2];

int BL, ans = 0;
int blok(int x) { return x / BL; }

void add(int x) {
    if(ILE[x] == 0) ++ans;
    ILE[x]++;
}

void remove(int x) {
    ILE[x]--;
    if(ILE[x] == 0) --ans;
}

int L = 0, R = 0;
int query(int l, int r) {
    while(R < r) {
        ++R;
        add(A[R]);
    }
    while(R > r) {
        remove(A[R]);
        --R;
    }
    while(L < l - 1) {
        ++L;
        remove(A[L]);
    }
    while(L >= l) {
        add(A[L]);
        --L;
    }
    return ans;
}

bool cmp(zap a, zap b) {
    if(blok(a.x) != blok(b.x)) return a.x < b.x;
    return a.y < b.y;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    // wprowadzanie danych
    int n, m;
    cin>>n>>m;
    FOR(i, 1, n) cin>>A[i];
    FOR(i, 1, m) {
        cin>>Q[i].x>>Q[i].y;
        Q[i].id = i;
    }
    
    // wyliczenie pierwiastka
    BL = sqrt(n);

    // sortowanie zapytan po blokach
    sort(TAB(Q, m), cmp);

    FOR(i, 1, m) ANS[Q[i].id] = query(Q[i].x, Q[i].y);
    FOR(i, 1, m) cout<<ANS[i]<<" "; cout<<"\n";
    return 0;
}