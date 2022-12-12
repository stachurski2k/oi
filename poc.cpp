//Autor: Stanislaw Deja
//Zlozonosc: O(nlogn)

#include<iostream>
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN=300007;
int b1[maxN]; //bajtek( starszty)
int b2[maxN];/// bajtek(mlodszy)
int indexf[maxN];
int indexb[maxN];
int n,m,k;
bool ok[maxN]={false};
int prev1[maxN];
int prev2[maxN];
int next1[maxN];
int next2[maxN];
int firstb2[maxN];
int T[maxN*2]={0};
bool done[maxN]={false};
void setT(int a,int b,int c){
    a=a+maxN-1;
    b=b+maxN+1;
    while (a/2!=b/2)
    {
        if(a%2==0){
            T[a+1]+=c;
        }
        if(b%2==1){
            T[b-1]+=c;
        }
        a/=2;
        b/=2;
    }
}
int get(int a){
    a+=maxN;
    int res=0;
    while(a>0){
        res+=T[a];
        a/=2;
    }
    return res;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>m>>k;
    for (int i = 1; i <= n; i++)
    {
        cin>>b1[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin>>b2[i];
    }
    for (int i = 0; i < maxN; i++)
    {
        indexb[i]=-1;
        indexf[i]=-1;
        prev1[i]=-1;
        prev2[i]=-1;
        next1[i]=-1;
        next2[i]=-1;
        firstb2[i]=-1;
    }
    for (int i = 1; i <=n; i++)
    {
       int x=b1[i];
       if(prev1[x]!=-1){
            next1[prev1[x]]=i;
       }
       prev1[x]=i;
    }
    for (int i = 1; i <=m; i++)
    {
       int x=b2[i];
       if(prev2[x]!=-1){
            next2[prev2[x]]=i;
       }
       prev2[x]=i;
    }
    int j=1;
    for (int i = 1; i <= n; i++)
    {
        if(b1[i]==b2[j]){
            indexf[j]=i;
            ok[i]=true;
            j++;
        }
    }
    j=m;
    for (int i = n; i > 0; i--)
    {
        if(b1[i]==b2[j]){
            indexb[j]=i;
            ok[i]=true;
            j--;
        }
    }
    for (int i = 1; i <=m; i++)
    {
        int x=b2[i];
        if(firstb2[x]==-1){
            firstb2[x]=i;
        }
    }
    //main loop;
    for (int i = 1; i <= n; i++)
    {
        if(done[i]){continue;}
        int x=b1[i];
        int start=firstb2[x];
        while(start!=-1){
            if(indexf[start]<=indexb[start]){
                setT(indexf[start],indexb[start],1);
            }
            start=next2[start];
        }
        int start2=i;
        while(start2!=-1){
            if(get(start2)>0){
                ok[start2]=true;
            }
            done[start2]=true;
            start2=next1[start2];
        }
        start=firstb2[x];
        while(start!=-1){
            if(indexf[start]<=indexb[start]){
                setT(indexf[start],indexb[start],-1);
            }
            start=next2[start];
        }
    }
    for (int i = 1; i <=n; i++)
    {
        if(ok[i]){
            cout<<1<<' ';
        }else{
            cout<<0<<' ';
        }
    }
    return 0;
}