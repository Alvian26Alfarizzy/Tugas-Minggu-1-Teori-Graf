#include <bits/stdc++.h>
using namespace std; const long long INF=1LL<<60; struct E{int u,v;long long w;};
int main(){int n=11,s,t;vector<E>e;int x[][3]={{1,2,2},{1,3,8},{1,4,1},{2,3,6},{2,5,1},{3,4,7},{3,5,5},{3,6,1},{3,7,2},{4,7,9},{5,6,3},{5,8,2},{5,9,9},{6,7,4},{6,9,6},{7,9,3},{7,10,1},{8,9,7},{8,11,9},{9,10,1},{9,11,2},{10,11,4}};for(auto&z:x)e.push_back({z[0],z[1],z[2]}),e.push_back({z[1],z[0],z[2]});
cout<<"===== JOHNSON =====\nSource Target: ";cin>>s>>t;int S=n+1;vector<E>ex=e;for(int v=1;v<=n;v++)ex.push_back({S,v,0});vector<long long>h(n+2,INF);h[S]=0;
for(int i=1;i<=n;i++){bool ch=false;for(auto z:ex)if(h[z.u]!=INF&&h[z.v]>h[z.u]+z.w)h[z.v]=h[z.u]+z.w,ch=true;if(!ch)break;}for(auto z:ex)if(h[z.u]!=INF&&h[z.v]>h[z.u]+z.w){cout<<"Negative cycle.\n";return 0;}
vector<vector<pair<int,long long>>>a(n+1);for(auto z:e)a[z.u].push_back({z.v,z.w+h[z.u]-h[z.v]});
vector<vector<long long>>D(n+1,vector<long long>(n+1,INF));for(int st=1;st<=n;st++){vector<long long>d(n+1,INF);priority_queue<pair<long long,int>,vector<pair<long long,int>>,greater<pair<long long,int>>>q;d[st]=0;q.push({0,st});while(!q.empty()){auto [du,u]=q.top();q.pop();if(du!=d[u])continue;for(auto[v,w]:a[u])if(d[v]>du+w)d[v]=du+w,q.push({d[v],v});}for(int v=1;v<=n;v++)if(d[v]!=INF)D[st][v]=d[v]-h[st]+h[v];}
if(D[s][t]==INF)cout<<"Tidak ada rute.\n";else cout<<"Jarak minimum dari V"<<s<<" ke V"<<t<<" = "<<D[s][t]<<"\n";
}