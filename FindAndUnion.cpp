#include<bits/stdc++.h>
#define N 1000002
using namespace std;
int rep[N], ile[N];
int n;
void Union(int a, int b) {
    a = Find(a); b = Find(b);
    if(ile[a] > ile[b]) swap(a, b);
    rep[a] = b;
    ile[b] += ile[a];
}
int Find(int a) {
    if(rep[a] != a) rep[a] = Find(rep[a]);
    return rep[a];
}
void init() {
    for(int i=1; i<=n; ++i) {
        rep[i] = i;
        ile[i] = 1;
    }
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    n = 2;
    init();
    Union(1,2);
    cout<<Find(1)<<" "<<Find(2)<<"\n";
    return 0;
}