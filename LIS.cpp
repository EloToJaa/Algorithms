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
const int N = 1e6 + 3;

int T[N], DP[N], B[N], C[N];
pii A[N];
int n;

void insert(int p, int val) {
    for(; p <= n; p += p & (-p)) T[p] = max(T[p], val);
}

int query(int p) {
    int ans = 0;
    for(; p > 0; p -= p & (-p)) ans = max(ans, T[p]);
    return ans;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    FOR(i, 1, n) {
        cin>>C[i];
        A[i].st = C[i]; A[i].nd = i;
    }

    // skalowanie
    sort(A + 1, A + (n + 1));
    int kl = 0;
    FOR(i, 1, n) {
        if(A[i].st == A[i - 1].st) B[ A[i].nd ] = B[ A[i - 1].nd ];
        else B[ A[i].nd ] = ++kl;
    }

    // wyliczanie DP[]
    int ans = 0;
    FOR(i, 1, n) {
        DP[i] = query(B[i] - 1) + 1;
        ans = max(ans, DP[i]);
        insert(B[i], DP[i]);
    }
    
    FOR(i, 1, n) cout<<DP[i]<<" "; cout<<"\n"<<ans<<"\n";
    return 0;
}