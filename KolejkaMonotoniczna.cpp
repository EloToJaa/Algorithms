#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second
typedef pair<int, int> pii; 
const int INF = 1e9 + 2;

class monqueue {
private:
    int pops, pushes;
public:
    deque<pii> Q;
    void push(int a) {
        while(!Q.empty() && Q.back().st <= a) Q.pop_back();
        pushes++;
        Q.push_back({a, pushes});
    }
    void pop() {
        pops++;
        if(pops == Q.front().nd) Q.pop_front();
    }
    int max() {
        if(Q.empty()) return -INF;
        return Q.front().st;
    }
};

monqueue Q;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    Q.push(n);
    return 0;
}