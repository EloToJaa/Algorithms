#include<bits/stdc++.h>
#define N 100002
using namespace std;
vector<int> v[N];
bitset<N> o;
queue<int> q;
void bfs(int p) {
    q.push(p);
    while(!q.empty()) {
        p = q.front();
        q.pop();
        for(int i = 0; i < v[p].size(); ++i) {
            int u = v[p][i];
            if(!o[u]) {
                q.push(u);
                o[u] = 1;
            }
        } 
    }
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    bfs(1);
    for() {
        
    }
    return 0;
}