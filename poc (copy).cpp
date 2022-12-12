#include<iostream>
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN=300007;
int b1[maxN]; //bajtek( starszty)
int b2[maxN];/// bajtek(mlodszy)
int n,m,k;
int main(){
    cin>>n>>m>>k;
    for (int i = 1; i <= n; i++)
    {
        cin>>b1[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin>>b2[i];
    }

    return 0;
}