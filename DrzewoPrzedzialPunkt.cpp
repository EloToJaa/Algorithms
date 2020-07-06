#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (a); i >= (b); --i)
#define pb push_back
#define st first
#define nd second
#define fun(a,b) max(a,b)
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6+2;

int t[3*N], A[N];
int n;

void init() {
    FOR(i, 1, n) {
        t[n + i - 1] = A[i];
    }
    FORD(i, n - 1, 1) {
        t[i] = fun(t[i*2], t[i*2+1]);
    }
}

void insert(int v, int tl, int tr, int l, int r, int val) {
    if(l <= tl && r >= tr) {
        t[v] = val;
        return;
    }
    int tm = (tl + tr) / 2;
    if(l <= tm) insert(2 * v, tl, tm, l, r, val);
    if(r > tm) insert(2 * v + 1, tm + 1, tr, l, r, val);
    t[v] = fun( t[v * 2], t[v * 2 + 1]);
}
int query(int v, int tl, int tr, int pos) {
    if(pos == tl && pos == tr) {
        return t[v];
    }
    int tm = (tl + tr) / 2;
    if(pos <= tm) return query(2 * v, tl, tm, pos);
    else return query(2 * v + 1, tm + 1, tr, pos);
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin>>n;
    FOR(i,1,n) {
        cin>>A[i];
    }
    init();
    insert(1,1,n,1,5,3);
    insert(1,1,n,3,6,5);
    cout<<query(1,1,n,4)<<"\n";
    insert(1,1,n,6,8,7);
    insert(1,1,n,1,7,2);
    cout<<query(1,1,n,5)<<"\n";
    cout<<query(1,1,n,8)<<"\n";
    insert(1,1,n,3,5,8);
    cout<<query(1,1,n,4)<<"\n";
    FOR(i,n,2*n-1) {
        cout<<t[i]<<" ";
    }
    return 0;
}