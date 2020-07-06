#include<bits/stdc++.h>
#define N 100002
using namespace std;
vector<int> v[N];
bitset<N> o;
void dfs(int p) {
    o[p] = 1;
    for(int i = 0; i < v[p].size(); ++i) {
        int u = v[p][i];
        if(!o[u]) {
            dfs(u);
        }
    } 
}
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    dfs(1);
    return 0;
}