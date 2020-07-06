#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define mp make_pair
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6 + 2;

int t[4 * N], A[N];
int n;

int fun(int a, int b)
{
    if (a != -1 && b != -1)
        return max(a, b); // zamien do zmiany operacji na drzewie
    if (a == -1)
        return b;
    return a;
}

void insert(int v, int start, int end, int pos, int val)
{
    if (start == end)
    {
        t[v] = val;
        return;
    }
    int mid = (start + end) / 2;
    if (pos <= mid)
        insert(v * 2, start, mid, pos, val);
    else
        insert(v * 2 + 1, mid + 1, end, pos, val);
    t[v] = fun( t[v * 2], t[v * 2 + 1]);
}

int query(int v, int start, int end, int l, int r)
{
    if (l > r)
        return -1;
    if (l == start && r == end)
        return t[v];
    int mid = (start + end) / 2;
    return fun( query(v * 2, start, mid, l, min(r, mid)), query(v * 2 + 1, mid + 1, end, max(l, mid + 1), r) );
}

void build()
{
    FOR(i, 1, n)
        t[n + i - 1] = A[i];
    FORD(i, n - 1, 1)
        t[i] = fun(t[i * 2], t[i * 2 + 1]);
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int m, a;
    cin >> n;
    FOR(i, 1, n)
    cin >> A[i];
    build();
    insert(1, 1, n, 1, 7);
    insert(1, 1, n, 8, 5);
    cout << query(1, 1, n, 1, 5) << "\n";
    insert(1, 1, n, 6, 4);
    insert(1, 1, n, 7, 5);
    cout << query(1, 1, n, 2, 8) << "\n";
    insert(1, 1, n, 1, 3);
    cout << query(1, 1, n, 3, 4) << "\n";
    FOR(i, 1, 2 * n - 1)
    cout << t[i] << " ";
    return 0;
}