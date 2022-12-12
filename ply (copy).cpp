#include<iostream>
#include<bits/stdc++.h>
#include<fstream>
using namespace std;
constexpr int maxH=500007;
constexpr int maxN=1000007;
int T[maxH]={0};
int sumy[maxN]={0};
int pary[maxN];
int n,h;
string s;
ofstream fs("res");
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>h;
    cin>>s;
    for (int i = 0; i < maxH; i++)
    {
        T[i]=-1;
        pary[i]=-1;
    }
    for (int i = 0; i < s.size(); i++)
    {
        if(s[i]=='('){
            sumy[i+1]=sumy[i]+1;
            T[sumy[i+1]]=i+1;
        }else{
            sumy[i+1]=sumy[i]-1;
            int prev=T[sumy[i]];
            pary[i+1]=prev;
            pary[prev]=i+1;
        }
    }
    int besttotal=INT_MAX;
    for (int x = 1; x <= h; x++)
    {
        int total=0;
        int d=0;
        string ss=string(s);
        for (int i = 0; i < n; i++)
        {
            if(ss[i]=='('){
                d+=1;
                if(d>x){
                    total+=2;
                    d-=2;
                    ss[pary[i+1]-1]='(';
                    ss[i]=')';
                }
            }else{
                d-=1;
            }
        }
        fs<<ss<<'\n';
        fs<<total<<'\n';
        if(total<besttotal){
            besttotal=total;
        }
    }
    
    cout<<besttotal<<'\n';
    
    fs.close();
    return 0;
}