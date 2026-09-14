#include <bits/stdc++.h>
using namespace std; const int INF=1e9;
int main(){int n=11,s,t; vector<vector<pair<int,int>>> a(n+1);
int e[][3]={{1,2,2},{1,3,8},{1,4,1},{2,3,6},{2,5,1},{3,4,7},{3,5,5},{3,6,1},{3,7,2},{4,7,9},{5,6,3},{5,8,2},{5,9,9},{6,7,4},{6,9,6},{7,9,3},{7,10,1},{8,9,7},{8,11,9},{9,10,1},{9,11,2},{10,11,4}};
for(auto &x:e){a[x[0]].push_back({x[1],x[2]});a[x[1]].push_back({x[0],x[2]});}
cout<<"===== DIJKSTRA =====\nSource Target: ";cin>>s>>t; vector<int>d(n+1,INF),p(n+1,-1); priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>q;
d[s]=0;q.push({0,s}); while(!q.empty()){auto [du,u]=q.top();q.pop();if(du!=d[u])continue;for(auto [v,w]:a[u])if(d[v]>d[u]+w){d[v]=d[u]+w;p[v]=u;q.push({d[v],v});}}
if(d[t]==INF){cout<<"Tidak ada rute.\n";return 0;} vector<int> path;for(int v=t;v!=-1;v=p[v])path.push_back(v);reverse(path.begin(),path.end());
cout<<"Jarak minimum = "<<d[t]<<"\nRute = ";for(size_t i=0;i<path.size();i++)cout<<"V"<<path[i]<<(i+1<path.size()?" -> ":"\n");
}