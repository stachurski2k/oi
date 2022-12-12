//Autor: Stanislaw Deja
//Zlozonosc : Podzadanie 1 i 2 =O(n) Podzadanie 3 =O(n^2)
#include<iostream>
#include<bits/stdc++.h>
using namespace std;
constexpr int maxN=100007;
struct truck{
    int x, d,w,m;
    double s;
    void setspeed(){
        s=(double)w/m;
    }
    double speed(){
        return s;
    }
};
int n;
int D,W,M;
truck trucks[maxN];
int total=1;
double times[maxN]={0};
int sumy[maxN]={0};
void binarySearch(int i,int low,int high){
    int mid=low;
    while(low<high){
        mid=(low+high)/2;
        double speed=(trucks[i].speed()-trucks[mid].speed());
        int d=sumy[mid]-sumy[i];
        double dist=(trucks[mid].x+trucks[mid].speed()*times[mid-1])-d-(trucks[i].x+trucks[i].speed()*times[mid-1]);
        double time=times[mid-1]+dist/speed;
        if(time<=times[mid]){
            low=mid+1;
        }else{
            high=mid;
        }
    }
     double speed=(trucks[i].speed()-trucks[mid].speed());
    int d=sumy[mid]-sumy[i];
    double dist=(trucks[mid].x+trucks[mid].speed()*times[mid-1])-d-(trucks[i].x+trucks[i].speed()*times[mid-1]);
    double time=times[mid-1]+dist/speed;
    times[i]=time;
}
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>D>>W>>M;
    bool isup=true;
    for(int i=1;i<=n;i++){
        cin>>trucks[i].x>>trucks[i].d>>trucks[i].w>>trucks[i].m;
        trucks[i].setspeed();
        if(i>1&&trucks[i-1].speed()>trucks[i].speed()){
            isup=false;
        }
    }
    if(isup){
        for (int i = 1; i < n; i++)
        {
            int dist=trucks[i+1].x-trucks[i+1].d-trucks[i].x;
            if(dist>=D){
                total++;
                continue;
            }
            int todo=D-dist;
            double speed=trucks[i+1].speed()-trucks[i].speed();
            double tt=todo/speed;
            double t=((double)trucks[i].x+D)/((double)W/M-trucks[i].speed());
            if(t>=tt){
                total++;
            }
        }
    }else{
        times[n]=DBL_MAX;
        for (int i = n-1; i >0; i--)
        {
            int d=0;
            for (int j=i+1; i <= n; j++)
            {
                d+=trucks[j].d;
                if(times[j]==DBL_MAX){
                    if(trucks[i].speed()<trucks[j].speed()){
                        times[i]=DBL_MAX;
                    }else{
                        double speed=(trucks[i].speed()-trucks[j].speed());
                        double dist=(trucks[j].x+trucks[j].speed()*times[j-1])-d-(trucks[i].x+trucks[i].speed()*times[j-1]);
                        double time=times[j-1]+dist/speed;
                        times[i]=time;
                    }
                    break;
                }
                if(trucks[i].speed()<trucks[j].speed()){
                    continue;
                }
                double speed=(trucks[i].speed()-trucks[j].speed());
                double dist=(trucks[j].x+trucks[j].speed()*times[j-1])-d-(trucks[i].x+trucks[i].speed()*times[j-1]);
                double time=times[j-1]+dist/speed;
                if(time<=times[j]){
                    times[i]=time;
                    break;
                }
            }
        }
        for (int i = 1; i < n; i++)
        {
            double t=(trucks[i].x+D)/((double)W/M-trucks[i].speed());
            int d=0;
            int c2=i+1;
            
            if(t>=times[i]){
                continue;
            }
            for (int j = i+1; j <= n; j++)
            {
                d+=trucks[j].d;
                if(times[j]>=t){
                    c2=j;
                    break;
                }
            }
            double x2=trucks[c2].x-d+trucks[c2].speed()*t;
            if(x2-(trucks[i].x+trucks[i].speed()*t)>=D){
                total++;
            }
            
        }
    }
    cout<<total<<'\n';
    return 0;
}