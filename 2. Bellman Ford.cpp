#include <iostream>
#include <vector>
#include <algorithm>


using namespace std;
const int INF = 1e9;
struct Edge {
    int u, v, w;
};
int main() {
    int n, m;
    int source, target;
    cout << "===== BELLMAN-FORD =====\n";


    cout << "Masukkan jumlah vertex dan edge: ";
    cin >> n >> m;
    vector<Edge> edges;
    cout << "Masukkan edge (u v bobot):\n";
    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        // Graph tidak berarah
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    }
    cout << "Masukkan source dan target: ";
    cin >> source >> target;


    vector<int> dist(n + 1, INF);
    vector<int> parent(n + 1, -1);


    dist[source] = 0;


    cout << "\n===== PROSES BELLMAN-FORD =====\n";
    // Relaksasi sebanyak V - 1 kali
    for (int i = 1; i <= n - 1; i++) {
        bool berubah = false;
        cout << "\nIterasi " << i << ":\n";
        for (auto edge : edges) {
            int u = edge.u;
            int v = edge.v;
            int w = edge.w;
            if (dist[u] != INF &&
                dist[v] > dist[u] + w) {
                cout << "  Update V" << v
                     << " melalui V" << u
                     << " : " << dist[v]
                     << " -> " << dist[u] + w
                     << endl;
                dist[v] = dist[u] + w;
                parent[v] = u;
                berubah = true;
            }
        }


        if (!berubah) {
            cout << "Tidak ada perubahan.\n";
            break;
        }
    }
    // Mengecek negative cycle
    bool negativeCycle = false;


    for (auto edge : edges) {
        int u = edge.u;
        int v = edge.v;
        int w = edge.w;


        if (dist[u] != INF &&
            dist[v] > dist[u] + w) {


            negativeCycle = true;
            break;
        }
    }


    if (negativeCycle) {
        cout << "\nGraph memiliki negative cycle.\n";
        return 0;
    }


    cout << "\n===== HASIL BELLMAN-FORD =====\n";


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
