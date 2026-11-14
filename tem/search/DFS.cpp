#include <bits/stdc++.h>
using namespace std;
int n,m,t;
int sx,sy,fx,fy;
int z[15][15]={0};
int v[15][15];
int dx[]={0,1,0,-1};
int dy[]={1,0,-1,0};
int answer;
void DFS (int x,int y){
    if (x==fx && y==fy)
    {
        answer++;
        return;
    }
    v[x][y]=1;
    for (int i = 0; i < 4; i++)
    {
        int xx=x+dx[i];
        int yy=y+dy[i];
        if (xx>=1 && xx<=n && yy>=1 &&yy<=m && z[xx][yy]==0 && v[xx][yy]==0)
        {
           DFS(xx,yy);
        }
        
    }
   v[x][y]=0;  
}
int main(){
    cin>>n>>m>>t;
    cin>>sx>>sy>>fx>>fy;
    for (int i = 0; i < t; i++)
    {
        int x,y;
        cin>>x>>y;
        z[x][y]=1;
    }
    DFS(sx,sy);
    cout<<answer;
    return 0;
}