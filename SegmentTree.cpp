#include<bits/stdc++.h>
#define N 100002
#define R 400002
// R = 4 * N
using namespace std;
int A[N], t[R];
int n;
void init(int v, int tl, int tr) {
    if (tl == tr)
        t[v] = A[tl];
    else {
        int tm = (tl + tr) / 2;
        init(v * 2, tl, tm);
        init(v * 2 + 1, tm + 1, tr);
        //t[v] = t[v * 2] + t[v * 2 + 1];
        t[v] = max( t[v * 2], t[v * 2 + 1]);
    }
}
void insert(int v, int tl, int tr, int pos, int new_val) {
    if (tl == tr)
        t[v] = new_val;
    else {
        int tm = (tl + tr) / 2;
        if (pos <= tm)
            insert(v * 2, tl, tm, pos, new_val);
        else
            insert(v * 2 + 1, tm + 1, tr, pos, new_val);
        //t[v] = t[v * 2] + t[v * 2 + 1];
        t[v] = max( t[v * 2], t[v * 2 + 1] );
    }
}
int query(int v, int tl, int tr, int l, int r) {
    if (l > r) 
        return 0;
    if (l == tl && r == tr)
        return t[v];
    int tm = (tl + tr) / 2;
    return max( query(v * 2, tl, tm, l, min(r, tm)), query(v * 2 + 1, tm + 1, tr, max(l, tm + 1), r) );
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> A[i];
    // wywolywanie v = 1, tl = 0, tr = n - 1
    init(1, 0, n - 1);
    insert(1, 0, n - 1, 2, 20);
    cout << query(1, 0, n - 1, 0, n - 1) << "\n";
    return 0;
}