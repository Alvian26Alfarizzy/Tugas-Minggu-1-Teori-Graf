#include <bits/stdc++.h>
using namespace std; const int INF=1e9; struct E{int u,v,w;};
int main(){int n=11,s,t;vector<E>e;int x[][3]={{1,2,2},{1,3,8},{1,4,1},{2,3,6},{2,5,1},{3,4,7},{3,5,5},{3,6,1},{3,7,2},{4,7,9},{5,6,3},{5,8,2},{5,9,9},{6,7,4},{6,9,6},{7,9,3},{7,10,1},{8,9,7},{8,11,9},{9,10,1},{9,11,2},{10,11,4}};for(auto &z:x){e.push_back({z[0],z[1],z[2]});e.push_back({z[1],z[0],z[2]});}
cout<<"===== BELLMAN-FORD =====\nSource Target: ";cin>>s>>t;vector<int>d(n+1,INF),p(n+1,-1);d[s]=0;
for(int i=1;i<n;i++){bool ch=false;for(auto z:e)if(d[z.u]!=INF&&d[z.v]>d[z.u]+z.w){d[z.v]=d[z.u]+z.w;p[z.v]=z.u;ch=true;}if(!ch)break;}
for(auto z:e)if(d[z.u]!=INF&&d[z.v]>d[z.u]+z.w){cout<<"Graph memiliki negative cycle.\n";return 0;}
if(d[t]==INF){cout<<"Tidak ada rute.\n";return 0;}vector<int>path;for(int v=t;v!=-1;v=p[v])path.push_back(v);reverse(path.begin(),path.end());cout<<"Jarak minimum = "<<d[t]<<"\nRute = ";for(size_t i=0;i<path.size();i++)cout<<"V"<<path[i]<<(i+1<path.size()?" -> ":"\n");}