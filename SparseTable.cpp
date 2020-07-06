#include<bits/stdc++.h>
#define MAXN 1000000
#define K 22
using namespace std;
int loga[MAXN + 2], st[MAXN + 2][K];
int n;
void init() { // O(nlogn)
    int maxn = 0;
    for(int i = 0; i < n; ++i)
        maxn = max(maxn, st[i][0]);
    for(int i = 2; i <= maxn; ++i)
        loga[i] = loga[i / 2] + 1;
    for(int j = 1; j <= K; ++j)
        for(int i = 0; i + (1 << j) <= n; ++i)
            st[i][j] = min( st[i][j-1], st[i + ( 1 << (j - 1) )][j - 1] ); // mozliwosc zamiany na max
}
int query(int l, int r) { // O(1)
    --l; --r; // poprawka numeracji
    int j = loga[r - l + 1];
    return min( st[l][j], st[r - (1 << j) + 1][j] ); // mozliwosc zmiany na max
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for(int i = 0; i < n; ++i)
        cin >> st[i][0];
    init();
    cout << query(1, 3) << "\n";
    return 0;
}