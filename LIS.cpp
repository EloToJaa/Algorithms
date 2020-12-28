#include <bits/stdc++.h>
using namespace std;
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define FORD(i, a, b) for (int i = (b); i >= (a); --i)
#define TRAV(x, T) for (auto &(x) : (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T, a, b) (T) + a, (T) + ((b) + 1)
#define VAR(x) #x << " = " << x << " "
#define sz(x) (int)(x).size()
#define nwd __gcd
#define pb push_back
#define st first
#define nd second
typedef long long ll;
typedef long double ld;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef vector<int> vi;
#define deb if (0)
const int N = 1e6, NT = N + 2;
const int INF = 1e9 + 1;

struct Stos {
    shared_ptr<Stos> prev;
    int head, size;
    Stos() {
        prev = nullptr;
    }
    Stos(shared_ptr<Stos> s, int e) {
        prev = s;
        head = e;
    }
};

shared_ptr<Stos> historia[NT];
int t = 1;
void push(int k, int e) {
    historia[t++] = make_shared<Stos>(historia[k], e);
}
void print_stack(int k) {
    auto s = historia[k];
    vi stos;
    while(s) {
        stos.pb(s->head);
        s = s->prev;
    }
    reverse(ALL(stos));
    TRAV(e, stos) {
        cout<<e<<" ";
    }
    cout<<"\n";
}

int A[NT];
pii B[NT];

int find(int l, int r, int val) {
    while(l < r) {
        int mid = l + (r - l) / 2;
        if(val < B[mid].st) r = mid;
        else l = mid + 1;
    }
    return l;
}

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n, ans = 1, idx = 0;;
    cin>>n;
    FOR(i, 1, n) {
        cin>>A[i];
    }
    FOR(i, 1, n) {
        B[i].st = INF;
    }
    FOR(i, 1, n) {
        int x = find(1, n, A[i]); // szukamy 1szego miejsca ze A[i] < B[x].first
        push(B[x-1].nd, A[i]); // dodajemy element do poprzedniego stosu
        if(x >= ans) {
            ans = x;
            idx = i;
        }
        B[x] = {A[i], i};
    }
    cout<<ans<<"\n";
    print_stack(idx);
    return 0;
}