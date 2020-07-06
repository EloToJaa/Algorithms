#include<bits/stdc++.h>
#define N 1000002
using namespace std;
int t[N];
bool warunek = 1;
int szukaj(int p, int k)
{
    int w = 1;
    while (p < k)
    {
        int sr = (p + k) / 2;
        if (warunek)
        {
            p = sr + 1;
            w = sr;
        }
        else
            k = sr;
    }
    return w;
}
int main() {
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout << szukaj(1, N - 2, 1);
    return 0;
}