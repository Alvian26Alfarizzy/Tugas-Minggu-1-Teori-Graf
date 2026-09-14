#include <bits/stdc++.h>
using namespace std; const int INF=1e9;
int main(){int n=11,s,t;vector<vector<int>>d(n+1,vector<int>(n+1,INF)),nx(n+1,vector<int>(n+1,-1));for(int i=1;i<=n;i++)d[i][i]=0,nx[i][i]=i;
int e[][3]={{1,2,2},{1,3,8},{1,4,1},{2,3,6},{2,5,1},{3,4,7},{3,5,5},{3,6,1},{3,7,2},{4,7,9},{5,6,3},{5,8,2},{5,9,9},{6,7,4},{6,9,6},{7,9,3},{7,10,1},{8,9,7},{8,11,9},{9,10,1},{9,11,2},{10,11,4}};for(auto &z:e){d[z[0]][z[1]]=d[z[1]][z[0]]=z[2];nx[z[0]][z[1]]=z[1];nx[z[1]][z[0]]=z[0];}
cout<<"===== FLOYD-WARSHALL =====\nSource Target: ";cin>>s>>t;for(int k=1;k<=n;k++)for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)if(d[i][k]!=INF&&d[k][j]!=INF&&d[i][j]>d[i][k]+d[k][j])d[i][j]=d[i][k]+d[k][j],nx[i][j]=nx[i][k];
if(d[s][t]==INF){cout<<"Tidak ada rute.\n";return 0;}cout<<"Jarak minimum = "<<d[s][t]<<"\nRute = V"<<s;int u=s;while(u!=t){u=nx[u][t];cout<<" -> V"<<u;}cout<<"\n";}