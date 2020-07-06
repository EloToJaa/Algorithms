#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (a); i >= (b); --i)
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
const int N = 1e6 + 2;
const int INF = 1e9 + 1;

ll t[4 * N], lazy[4 * N];
int A[N];
int n;
// !!! - oznacza kod potrzebny przy zmianie query na sum

int fun(int a, int b)
{
    if (a != -INF && b != -INF)
        return max(a, b); // zamien do zmiany operacji na drzewie
    if (a == -INF)
        return b;
    return a;
}

void push(int v, int x)
{
    t[v * 2] += lazy[v];
    t[v * 2 + 1] += lazy[v];
    t[v] += x; // !!!
    lazy[v * 2] += lazy[v];
    lazy[v * 2 + 1] += lazy[v];
    lazy[v] = 0;
}

void insert(int v, int start, int end, int l, int r, int val)
{
    if (l > r)
        return;
    if (l == start && end == r)
    {
        //t[v] += val * (end - start + 1); // !!!
        t[v] += val;
        lazy[v] += val;
        return;
    }
    //push(v, (end - start + 1) * lazy[v]); // !!!
    push(v, 0);
    int mid = (start + end) / 2;
    insert(v * 2, start, mid, l, min(r, mid), val);
    insert(v * 2 + 1, mid + 1, end, max(l, mid + 1), r, val);
    t[v] = fun(t[v * 2], t[v * 2 + 1]);
}

int query(int v, int start, int end, int l, int r)
{
    if (l > r)
        return -INF;
    if (l <= start && end <= r)
        return t[v];
    //push(v, (end - start + 1) * lazy[v]); // !!!
    push(v, 0);
    int mid = (start + end) / 2;
    return fun(query(v * 2, start, mid, l, min(r, mid)),
               query(v * 2 + 1, mid + 1, end, max(l, mid + 1), r));
}

signed main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, a, mn = 2;
    cin >> n;
    n *= mn;
    for (int i = 1; i <= n; i += mn)
    {
        cin >> a;
        insert(1, 1, n, i, i + mn - 1, a);
    }
    insert(1, 1, n, 1, n - 1, 10);
    cout << query(1, 1, n, 2, n-1) << "\n";
    insert(1, 1, n, 1, n - 1, 10);
    FOR(i, 1, n)
        cout << query(1, 1, n, i, i) << " ";
    cout << query(1, 1, n, 2, n-1) << "\n";
    return 0;
}