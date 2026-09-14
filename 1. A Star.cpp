#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <functional>


using namespace std;


const int INF = 1e9;


int main() {
    int n, m;
    int source, target;


    cout << "===== A* (A-STAR) =====\n";


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


    vector<int> g(n + 1, INF);
    vector<int> parent(n + 1, -1);


    /*
        g(n) = biaya dari source menuju n
        h(n) = estimasi biaya dari n menuju target
        f(n) = g(n) + h(n)


        Karena tidak ada koordinat vertex,
        digunakan h(n) = 0.
    */


    auto heuristic = [](int u) -> int {
        return 0;
    };


    priority_queue<
        pair<int, int>,
        vector<pair<int, int>>,
        greater<pair<int, int>>
    > openSet;


    g[source] = 0;


    openSet.push({
        g[source] + heuristic(source),
        source
    });


    cout << "\n===== PROSES A* =====\n";


    while (!openSet.empty()) {
        int f = openSet.top().first;
        int u = openSet.top().second;
        openSet.pop();


        cout << "\nMengunjungi V" << u
             << " | g(n) = " << g[u]
             << " | h(n) = " << heuristic(u)
             << " | f(n) = " << f
             << endl;


        // Jika sudah mencapai target
        if (u == target) {
            cout << "Target ditemukan!\n";
            break;
        }


        for (auto edge : adj[u]) {
            int v = edge.first;
            int w = edge.second;


            int biayaBaru = g[u] + w;


            cout << "  Periksa V" << v
                 << " | g baru = " << biayaBaru;


            if (biayaBaru < g[v]) {
                g[v] = biayaBaru;
                parent[v] = u;


                int nilaiF =
                    g[v] + heuristic(v);


                openSet.push({nilaiF, v});


                cout << " -> UPDATE"
                     << " | f(n) = " << nilaiF;
            }


            cout << endl;
        }
    }


    cout << "\n===== HASIL A* =====\n";


    if (g[target] == INF) {
        cout << "Tidak ada rute.\n";
    } else {
        cout << "Jarak minimum = " << g[target] << endl;


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
