///Autor: Stanislaw Deja
// Zlozonosc : n^(1/2)*n


#include<iostream>
#include<bits/stdc++.h>
// #include<fstream>
using namespace std;
constexpr int maxM=2007;
constexpr int maxSegSize=1000;
struct segment{
    int id;
    int first;
    int firstsnake;
    int size=0;
};
int world[maxM][maxM];
bool snake_world[maxM][maxM];
vector<pair<int,int>> snakecoords;
vector<segment> seg;
vector<int> snake;
int s,num,m;
// ofstream fs("res");
pair<int,int> head;
int main(){
    ios_base::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin>>s>>num>>m;
    int a,b,c;
    for (int i = 0; i < maxM; i++)
    {
        for (int j = 0; j < maxM; j++)
        {
            world[i][j]=-1;
            snake_world[i][j]=false;
        }
    }
    for (int i = 0; i < num; i++)
    {
        cin>>a>>b>>c;
        world[a][b]=c;
    }
    snake_world[1][1]=true;
    segment s;
    s.id=seg.size();
    s.first=0;
    s.size=1;
    s.firstsnake=0;
    snake.push_back(0);
    head={1,1};
    world[1][1]=s.id;
    seg.push_back(s);
    snakecoords.push_back({1,1});
    char z;
    for (int i = 0; i < m; i++)
    {
        cin>>z;
        if(z=='Z'){
            cin>>a>>b;
            if(snake_world[a][b]){
                int index=world[a][b];
                segment s=seg[index];
                // fs<<a<<" "<<b<< " "<<s.first<<"\n";
                pair<int,int> coord;;
                int res=0;
                for (int j = 0; j <s.size; j++)
                {
                    coord=snakecoords[j+s.first];
                    if(coord.first==a&&coord.second==b){
                        res=j;
                        break;;
                    }
                }
                // fs<<snake[s.firstsnake+res]<<'\n';;
                cout<<snake[s.firstsnake+res]<<'\n';

            }else{
                // fs<<-11<<'\n';
                cout<<-1<<'\n';
            }
        }else{
            pair<int,int> move=head;
            if(z=='G')move.first--;
            else if(z=='D')move.first++;
            else if(z=='P')move.second++;
            else move.second--;
            head=move;
            if(!snake_world[move.first][move.second]&&world[move.first][move.second]!=-1){
                //found new snack to eat esssa;
                segment lastseg=seg[seg.size()-1];
                if(lastseg.size>=maxSegSize){
                    segment nseg;
                    nseg.id=seg.size();
                    nseg.size=1;
                    nseg.first=snakecoords.size();
                    nseg.firstsnake=snake.size();
                    snake.push_back(world[move.first][move.second]);
                    world[move.first][move.second]=lastseg.id;
                    seg.push_back(nseg);
                }else{
                    lastseg.size=lastseg.size+1;
                    snake.push_back(world[move.first][move.second]);
                    world[move.first][move.second]=lastseg.id;
                    seg[seg.size()-1]=lastseg;
                }
                snake_world[move.first][move.second]=true;
                snakecoords.push_back(move);
            }else{
                snakecoords.push_back(move);
                pair<int,int> coord=snakecoords[seg[0].first];
                snake_world[coord.first][coord.second]=false;
                snake_world[move.first][move.second]=true;
                world[coord.first][coord.second]=-1;
                for (int j = 0; j < seg.size(); j++)
                {
                    seg[j].first++;
                    coord=snakecoords[seg[j].first+seg[j].size-1];
                    world[coord.first][coord.second]=seg[j].id;
                }
            }
        }
    }
    return 0;
}
