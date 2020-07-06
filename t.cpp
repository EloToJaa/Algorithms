#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6;

struct przyst { int x, y, id; } A[N + 2], B[N + 2];
int T[N + 2];

void insert(int p, int val, int n) {
    for(; p <= n; p += p & (-p)) T[p] = max(T[p], val);
}

int query(int p) {
    int ans = 0;
    for(; p > 0; p -= p & (-p)) ans = max(ans, T[p]);
    return ans;
}

bool fx(przyst a, przyst b) {
    if(a.x == b.x) return a.y < b.y;
    return a.x < b.x;
}

bool fy(przyst a, przyst b) {
    if(a.y == b.y) return a.x < b.x;
    return a.y < b.y;
}

void skaluj(int n, int &a, int &b) {
    int kl = 0;
    sort(B + 1, B + (n + 1), fx);
    FOR(i, 1, n) {
        if(B[i - 1].x != B[i].x) ++kl;
        A[B[i].id].x = kl;
    }
    a = kl;

    kl = 0;
    sort(B + 1, B + (n + 1), fy);
    FOR(i, 1, n) {
        if(B[i - 1].y != B[i].y) ++kl;
        A[B[i].id].y = kl;
    }
    b = kl;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, m, k;
    cin>>n>>m>>k;
    FOR(i, 1, k) {
        cin>>A[i].x>>A[i].y>>A[i].id;
        B[i].id = i;
        B[i].x = A[i].x;
        B[i].y = A[i].y;
    }

    skaluj(k, n, m);

    sort(A + 1, A + (k + 1), fy);
    FOR(i, 1, k) insert(A[i].x, query(A[i].x) + A[i].id, k);
    cout<<query(k)<<"\n";
    return 0;
}