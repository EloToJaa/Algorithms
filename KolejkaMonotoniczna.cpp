#include<bits/stdc++.h>
using namespace std;
#define st first
#define nd second
const int INF = 1e9 + 2;

class monqueue {
private:
    int pops = 1, pushes = 1;
public:
    deque<pii> Q;
    void push(int a);
    void pop();
    int max();
};
void monqueue::push(int a) {
    while(!Q.empty() && Q.back().st <= a) Q.pop_back();
    Q.push_back({a, pushes});
    pushes++;
}
void monqueue::pop() {
    if(pops == Q.front().nd) Q.pop_front();
    pops++;
}
int monqueue::max() {
    if(Q.empty()) return -INF;
    return Q.front().st;
}

monqueue Q;

signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin>>n;
    Q.push(n);
    return 0;
}