#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>


using namespace std;


const int INF = 1e9;


struct Edge {
    int u, v, w;
};


int main() {
    int n, m;
    int source, target;


    cout << "===== DIJKSTRA =====\n";


    cout << "Masukkan jumlah vertex dan edge: ";
    cin >> n >> m;


    vector<vector<pair<int, int>>> adj(n + 1);


    cout << "Masukkan edge (u v bobot):\n";


    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;


        // Graph tidak berarah
        adj[u].push_back({v, w});
        adj[v].push_back({u, w});
    }


    cout << "Masukkan source dan target: ";
    cin >> source >> target;


    vector<int> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);


    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > pq;


    dist[source] = 0;
    pq.push({0, source});


    cout << "\n===== PROSES DIJKSTRA =====\n";


    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();


        if (d != dist[u]) {
            continue;
        }


        cout << "\nMengunjungi V" << u
             << " dengan jarak " << d << endl;


        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;


            int jarakBaru = dist[u] + w;


            cout << "  Periksa V" << v
                 << " | jarak baru = " << jarakBaru;


            if (jarakBaru < dist[v]) {
                dist[v] = jarakBaru;
                parent[v] = u;


                pq.push({dist[v], v});


                cout << " -> UPDATE";
            }


            cout << endl;
        }
    }


    cout << "\n===== HASIL DIJKSTRA =====\n";


    if (dist[target] == INF) {
        cout << "Tidak ada rute.\n";
    } else {
        cout << "Jarak minimum = " << dist[target] << endl;


        vector<int> path;
        int current = target;


        while (current != -1) {
            path.push_back(current);
            current = parent[current];
        }


        reverse(path.begin(), path.end());


        cout << "Rute = ";
        for (int i = 0; i < path.size(); i++) {
            cout << "V" << path[i];


            if (i != path.size() - 1) {
                cout << " -> ";
            }
        }


        cout << endl;
    }


    return 0;
}
