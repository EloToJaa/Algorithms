#include<bits/stdc++.h>
using namespace std;
#define FOR(i,a,b) for(int i = (a); i <= (b); ++i)
const int N = 1e6+2;
int t[4*N], B[N];
signed main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    int n,m,a,w,mx=0,T=0;
    cin>>n>>m;
    FOR(i,1,n) B[i]=1;
    FOR(i,1,m) {
        cin>>a;
        if(a > n) {
            mx = t[1];
            T = i;
        }
        else {
            w = mx + 1;
            if(B[a] > T) w = t[n + a] + 1;
            B[a] = i;
            for (t[a += n] = w; a > 1; a /= 2) t[a/2] = max( t[a] , t[a^1]); // tree insert
        }
    }
    FOR(i,1,n) {
        w = mx;
        if(B[i] > T) w = t[n+i];
        cout<<w<<" ";
    }
    return 0;
}