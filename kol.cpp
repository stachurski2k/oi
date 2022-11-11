#include<iostream>
#include<bits/stdc++.h>
using namespace std;
int world[2000][2000];
bool snake_world[2000][2000];
int s,num,m;
vector<pair<int,int>> snake;
vector<pair<int,int>> snake_cord;
int main(){
    cin>>s>>num>>m;
    int a,b,c;
    for (int i = 0; i < 2000; i++)
    {
        for (int j = 0; j < 2000; j++)
        {
            world[i][j]=-1;
            snake_world[i][j]=false;
        }
    }
    world[1][1]=0;
    snake.push_back({0,0});
    snake_cord.push_back({1,1});
    snake_world[1][1]=true;
    for (int i = 0; i < num; i++)
    {
        cin>>a>>b>>c;
        world[a][b]=c;
    }
    char x;
    for (int i = 0; i < m; i++)
    {
        cin>>x;
        if(x=='Z'){
            cin>>a>>b;
            if(!snake_world[a][b]){
                cout<<-1<<'\n';
            }else{
                cout<<world[a][b]<<'\n';
            }
        }else{
            pair<int,int> head=snake_cord[snake_cord.size()-1];
            if(x=='G')head.first--;
            else if(x=='D')head.first++;
            else if(x=='P')head.second++;
            else head.second--;
            if(world[head.first][head.second]!=-1){
                snake.push_back({world[head.first][head.second],snake_cord.size()});
                snake_world[head.first][head.second]=true;
                snake_cord.push_back(head);
            }else{
                snake_cord.push_back(head);
                world[snake_cord[snake[0].second].first][snake_cord[snake[0].second].second]=-1;
                snake_world[snake_cord[snake[0].second].first][snake_cord[snake[0].second].second]=false;
                for (int i = 0; i < snake.size(); i++)
                {
                    snake[i].second++;
                    world[snake_cord[snake[i].second].first][snake_cord[snake[i].second].second]=snake[i].first;
                    snake_world[snake_cord[snake[i].second].first][snake_cord[snake[i].second].second]=true;
                }

            }

        }
    }
    

    return 0;
}
