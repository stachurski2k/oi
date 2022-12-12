//Autor : Stanislaw Deja
//Zlozonosc : n^(1/2)*n
//
#include<iostream>
#include<bits/stdc++.h>
////// to do calc dist betweeen hubs;;;
using namespace std;
constexpr int maxN=1e5+7;
constexpr int maxNSqr=390;
int n,k;
int seg;
 //just a graf for now
struct edge{
    int a,b,c;
};

edge edges[maxN];
vector<int> points[maxN];
//tree
//hub data;
struct hubdata{
    vector<int> childs;
    int parent=-1;
    int waytoparent=-1;
    int index;
    long long upcost=0,downcost=0;
    int upnum=0,downnum=0;
};
vector<pair<int,int>> tree[maxN];
pair<int,int> revtree[maxN];
int syncount[maxN]={0};
vector<hubdata> hubs;
int hubstree[maxN]={0};//0 if no hub
int vertchildnum[maxN]={0};
long long dists2[maxNSqr][maxNSqr]={0};
long long vertdowncost[maxN]={0};
long long vertdownnum[maxN]={0};
bool zamki[maxN];
long long totalcost=0;
void totree(){
    queue<pair<int,int>> q;
    q.push({1,0});
    while (!q.empty())
    {
        pair<int,int> v=q.front();
        q.pop();
        for (int i = 0; i < points[v.first].size(); i++)
        {
            if(edges[points[v.first][i]].a==v.second||edges[points[v.first][i]].b==v.second){
                revtree[v.first]={edges[points[v.first][i]].c,v.second};
                continue;
            }
            
            if(edges[points[v.first][i]].a==v.first){
                tree[v.first].push_back({edges[points[v.first][i]].c,edges[points[v.first][i]].b});
                q.push({edges[points[v.first][i]].b,v.first});

            }else{
                tree[v.first].push_back({edges[points[v.first][i]].c,edges[points[v.first][i]].a});
                q.push({edges[points[v.first][i]].a,v.first});

            }
        }
        vertchildnum[v.first]=points[v.first].size()-1;
    }
}
void calcsyn(){
    stack<int> s;
    queue<int> q;
    q.push(1);
    while (!q.empty())
    {
        int v=q.front();
        q.pop();
        for (int i = 0; i < tree[v].size(); i++)
        {
            q.push(tree[v][i].second);
            s.push(tree[v][i].second);
        }
    }
    hubdata d;
    hubs.push_back(d);
    hubstree[1]=1;
    d.index=1;
    hubs.push_back(d);
    
    while(!s.empty()){
        int c=s.top();
        s.pop();
        if(syncount[c]>=maxNSqr){
            hubstree[c]=hubs.size();
            d.index=c;
            hubs.push_back(d);
            syncount[revtree[c].second]+=1;
        }else{
            syncount[revtree[c].second]+=syncount[c]+1;;
        }
    }    
}
void setrelations(){
    for (int i = 1; i < hubs.size(); i++)
    {
        // hubdata h=hubs[i];
        long long dist=revtree[hubs[i].index].first;
        int start=revtree[hubs[i].index].second;
        int prev=hubs[i].index;
        if(start==0||start<0)continue;
        while (hubstree[start]==0&&hubstree[start]!=1)
        {
            dist+=revtree[start].first;
            prev=start;
            start=revtree[start].second;
        }
        if(hubstree[start]>0&&hubstree[start]<hubs.size()){
            hubs[i].parent=start;
            hubs[i].waytoparent=prev;
            hubs[hubstree[start]].childs.push_back(hubs[i].index);
            dists2[hubstree[start]][i]=dist;
            dists2[i][hubstree[start]]=dist;
        
        }
    }
}

void putcastle(int z){
    queue<pair<long long,int>> q;
    queue<int> q2;
    bool done[seg]={false};
    bool donevert[maxN]={false};
    q.push({0,z});
    int tophub=1;
    int ss=z;
    int prev=z;
    do{
        prev=ss;
        ss=revtree[ss].second;
    }while (hubstree[ss]==0&&hubstree[ss]!=1);
    int castlecount=0;
    int hubcount=0;
    int last=1;
    q.push({0,z});
    while (!q.empty())
    {
        auto x=q.front();
        q.pop();
        if(donevert[x.second]){
            continue;;
        }
        donevert[x.second]=true;
        if(hubstree[x.second]!=0){
            if(done[hubstree[x.second]])continue;
                ///hub found on the botom
            totalcost+= (hubs[hubstree[x.second]].downcost+hubs[hubstree[x.second]].downnum*x.first)*2;
            hubs[hubstree[x.second]].upnum+=1;
            hubs[hubstree[x.second]].upcost+=x.first;
            done[hubstree[x.second]]=true;
            hubcount++;
            castlecount+=hubs[hubstree[x.second]].downnum;
            last=x.second;
            if(zamki[x.second]){
                totalcost+=x.first*2;
                castlecount++;
            }
            for (int f = 0; f < hubs[hubstree[x.second]].childs.size(); f++)
            {
                q2.push(hubs[hubstree[x.second]].childs[f]);
            }
            while (!q2.empty())
            {
                int f=q2.front();
                q2.pop();
                if(!done[hubstree[f]]){
                    hubs[hubstree[f]].upnum+=1;
                    hubs[hubstree[f]].upcost+=x.first+dists2[hubstree[x.second]][hubstree[f]];
                     for (int ff = 0; ff < hubs[hubstree[f]].childs.size(); ff++)
                    {
                    q2.push(hubs[hubstree[f]].childs[ff]);
                    }
                }
                done[hubstree[f]]=true;
            }
        }else{
            if(zamki[x.second]){
                totalcost+=x.first*2;
                castlecount++;
            }
            for (int i = 0; i < tree[x.second].size(); i++)
            {
                q.push(make_pair(x.first+tree[x.second][i].first,tree[x.second][i].second));
            }
            
        }
        if(hubcount>=hubs[hubstree[ss]].childs.size()&&castlecount>=vertdownnum[prev]){
            break;
        }
    }
  
    while (!q.empty())
    {
        q.pop();
    }
    
    
    long long dist=0;;
    int s=z;
    queue<long long> qx;
    queue<int> qy;
    do{
        dist+=revtree[s].first;
        if(zamki[revtree[s].second]&&(hubstree[revtree[s].second]==0||hubstree[revtree[s].second]==1)){
            totalcost+=2*dist;
            if(hubstree[revtree[s].second]==0)
                castlecount++;
        }
        if(hubstree[revtree[s].second]==0){
            for (int j = 0; j < tree[revtree[s].second].size(); j++)
            {
                if(tree[revtree[s].second][j].second!=s){
                    qx.push(dist+tree[revtree[s].second][j].first);
                    qy.push(tree[revtree[s].second][j].second);

                    //q.push(make_pair(dist+tree[revtree[s].second][j].first,tree[revtree[s].second][j].second));
                }
            }
        }
        
        while(!qx.empty()){
            auto x=qx.front();
            int y=qy.front();
            qx.pop();
            qy.pop();

            if(donevert[y]){
                continue;;
            }
            donevert[y]=true;
            if(hubstree[y]!=0){///hub found on the top
                totalcost+= (hubs[hubstree[y]].downcost+hubs[hubstree[y]].downnum*(x))*2;
                hubs[hubstree[y]].upnum+=1;
                hubs[hubstree[y]].upcost+=x;
                done[hubstree[y]]=true;
                hubcount++;
                castlecount+=hubs[hubstree[y]].downnum;
                if(zamki[y]){
                    totalcost+=x*2;
                    castlecount++;
                }
                for (int f = 0; f < hubs[hubstree[y]].childs.size(); f++)
                {
                    q2.push(hubs[hubstree[y]].childs[f]);
                }
                while (!q2.empty())
                {
                    int f=q2.front();
                    q2.pop();
                    if(!done[hubstree[f]]){
                        hubs[hubstree[f]].upnum+=1;
                        hubs[hubstree[f]].upcost+=x+dists2[hubstree[y]][hubstree[f]];
            
                    }
                 
                    
                    done[hubstree[f]]=true;

                    for (int ff = 0; ff < hubs[hubstree[f]].childs.size(); ff++)
                    {
                        q2.push(hubs[hubstree[f]].childs[ff]);
                    }
                    
                }
            }else{
                if(zamki[y]){
                    totalcost+=x*2;
                    castlecount++;
                }
                for (int i = 0; i < tree[y].size(); i++)
                {
                    qx.push(x+tree[y][i].first);
                    qy.push(tree[y][i].second);
                }
            }
        }
        s=revtree[s].second;
        
       
    }while(hubstree[s]==0&&hubstree[s]!=1);
    s=ss;
    // if(hubcount!=hubs[hubstree[ss]].childs.size()&&castlecount!=vertdownnum[prev]){
    //     fs<<hubcount<<" "<<hubs[hubstree[ss]].childs.size()<<" "<<castlecount<<" "<<vertdownnum[prev]<<'\n';
    // }
    // go through hubs sons;// to be optimized
    int starth=s;
   
    if(hubstree[s]!=-1){
        totalcost+=(hubs[hubstree[s]].upcost+hubs[hubstree[s]].upnum*dist)*2;
        totalcost+=(hubs[hubstree[s]].downcost-vertdowncost[prev]+(hubs[hubstree[s]].downnum-vertdownnum[prev])*dist)*2;
        while (s!=-1)
        {
            done[hubstree[s]]=true;
            hubs[hubstree[s]].downcost+=dist+dists2[hubstree[s]][hubstree[starth]];
            hubs[hubstree[s]].downnum+=1;
            vertdowncost[prev]+=dist+dists2[hubstree[s]][hubstree[starth]];
            vertdownnum[prev]+=1;
            prev=hubs[hubstree[s]].waytoparent;
            s=hubs[hubstree[s]].parent;
        }
    }
    for (int i = 2; i < seg&&i<hubs.size(); i++)
    {
        if(!done[i]){
        
            hubs[i].upcost+=dist+dists2[i][hubstree[starth]];
            hubs[i].upnum+=1;
        }
    }
 
    zamki[z]=true;
}
void calcdist(){
    queue<pair<long long,int>> q;
    queue<pair<long long,int>> q3;
    queue<int> q2;
    for (int i = 0; i < hubs.size(); i++)
    {
        q.push({0,hubs[i].index});//first go through your sons
        while (!q.empty())
        {
            auto x=q.front();
            q.pop();
            dists2[hubstree[x.second]][i]=x.first;
            dists2[i][hubstree[x.second]]=x.first;
           
            auto h=hubs[hubstree[x.second]];
            for (int j = 0; j < h.childs.size(); j++)
            {
                q.push({x.first+dists2[hubstree[x.second]][hubstree[h.childs[j]]],h.childs[j]});
            }
        }
        //now go through your neighbours
        int s=hubs[i].index;
        long long dist=0;
        if(i>1){
            do{
                dist+=revtree[s].first;
                for (int j = 0; j < tree[revtree[s].second].size(); j++)
                {
                    if(tree[revtree[s].second][j].second!=s){
                        q.push({dist+tree[revtree[s].second][j].first,tree[revtree[s].second][j].second});
                    }
                }
                while(!q.empty()){
                    auto x=q.front();
                    q.pop();
                    if(hubstree[x.second]!=0){///hub found on the top
                        dists2[hubstree[x.second]][i]=x.first;                  
                        dists2[i][hubstree[x.second]]=x.first;      
                                
                        for (int f = 0; f < hubs[hubstree[x.second]].childs.size(); f++)
                        {
                            q3.push({x.first+dists2[hubstree[x.second]][hubstree[hubs[hubstree[x.second]].childs[f]]],hubs[hubstree[x.second]].childs[f]});
                        }
                        while (!q3.empty())
                        {
                            auto f=q3.front();
                            q3.pop();
                            dists2[i][hubstree[f.second]]=f.first;
                            dists2[hubstree[f.second]][i]=f.first;
                           
                            for (int ff = 0; ff < hubs[hubstree[f.second]].childs.size(); ff++)
                            {
                                q3.push({f.first+dists2[hubstree[f.second]][hubstree[hubs[hubstree[f.second]].childs[ff]]],hubs[hubstree[f.second]].childs[ff]});
                            }
                        }
                    }else{
                        for (int i = 0; i < tree[x.second].size(); i++)
                        {
                            q.push({x.first+tree[x.second][i].first,tree[x.second][i].second});
                        }
                    }
                }
                s=revtree[s].second;
            } while(hubstree[s]==0&&hubstree[s]!=1);
        }
    }
    for (int i = 0; i < hubs.size(); i++)
    {
        int p=hubs[i].parent;//now go above your parent
        long long dist=dists2[i][hubstree[p]];
        while (p!=-1&&p!=1)
        {
            auto z=hubs[hubstree[hubs[hubstree[p]].parent]];
            for (int j = 0; j < z.childs.size(); j++)
            {
                if(p!=z.childs[j]){
                    q.push({dist+dists2[hubstree[z.childs[j]]][hubstree[p]]
                    ,z.childs[j]});
                }
            }
            while (!q.empty())
            {
                auto x=q.front();
                q.pop();
                dists2[hubstree[x.second]][i]=x.first;
                dists2[i][hubstree[x.second]]=x.first;
               
                auto h=hubs[hubstree[x.second]];
                for (int j = 0; j < h.childs.size(); j++)
                {
                    q.push({x.first+dists2[hubstree[x.second]][hubstree[h.childs[j]]],h.childs[j]});
                }
            }
            dist+=dists2[hubstree[hubs[hubstree[p]].parent]][hubstree[p]];
            p=hubs[hubstree[p]].parent;
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>n>>k;
    seg=sqrt(n);
    int a,b,c;
    for (int i = 1; i < n; i++)
    {
        cin>>a>>b>>c;
        edges[i]={a,b,c};
        points[a].push_back(i);
        points[b].push_back(i);
    }
    totree();
    calcsyn();
    setrelations();
    calcdist();
    
    
    int z;
    zamki[1]=true;
    for (int i = 2; i < hubs.size(); i++)
    {
        hubs[i].upcost+=dists2[1][i];
        hubs[i].upnum++;
    }
    
    
    for (int i = 1; i <= k; i++)
    {
        
        cin>>z;
       putcastle(z);
      
       
        cout<<totalcost<<'\n';
    }
    
    //seg= 316 dla n 100000;
    return 0;
}