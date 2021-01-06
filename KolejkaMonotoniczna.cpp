#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
#define FORD(i,a,b) for(int i = (b); i >= (a); --i)
#define TRAV(x,T) for(auto& x: (T))
#define ALL(T) T.begin(), T.end()
#define TAB(T,a,b) (T)+a, (T)+((b)+1)
#define VAR(x) #x<<" = "<<x<<" " 
#define sz(x) (int)(x).size()
#define nwd __gcd
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
const ll INF = (ll)1e18 + 2;

class monqueue {
private:
    int pops = 0, pushes = 0;
public:
    deque<pli> Q;
    void push(const ll &val) {
        while(!Q.empty() && Q.back().st <= val) Q.pop_back();
        pushes++;
        Q.push_back({val, pushes});
    }
    void pop() {
        pops++;
        if(pops == Q.front().nd) Q.pop_front();
    }
    ll max() {
        if(Q.empty()) return -INF;
        return Q.front().st;
    }
};

monqueue Q;