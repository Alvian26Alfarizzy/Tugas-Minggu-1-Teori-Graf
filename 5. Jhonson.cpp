#include <iostream>
#include <vector>
#include <queue>
#include <iomanip>
#include <functional>
#include <string>


using namespace std;


const long long INF = 1e18;


struct Edge {
    int u, v;
    long long w;
};


int main() {
    int n, m;
    int source, target;


    cout << "===== JOHNSON'S ALGORITHM =====\n";


    cout << "Masukkan jumlah vertex dan edge: ";
    cin >> n >> m;


    vector<Edge> edges;


    cout << "Masukkan edge (u v bobot):\n";


    for (int i = 0; i < m; i++) {
        int u, v;
        long long w;


        cin >> u >> v >> w;


        // Graph tidak berarah
        edges.push_back({u, v, w});
        edges.push_back({v, u, w});
    }


    cout << "Masukkan source dan target: ";
    cin >> source >> target;


    int superSource = n + 1;


    // ==================================================
    // LANGKAH 1: TAMBAHKAN SUPER SOURCE
    // ==================================================


    vector<Edge> extendedEdges = edges;


    for (int v = 1; v <= n; v++) {
        extendedEdges.push_back({
            superSource,
            v,
            0
        });
    }


    cout << "\n===== LANGKAH 1 =====\n";
    cout << "Super source = V" << superSource << endl;


    // ==================================================
    // LANGKAH 2: BELLMAN-FORD
    // ==================================================


    vector<long long> h(n + 2, INF);


    h[superSource] = 0;


    cout << "\n===== LANGKAH 2 =====\n";
    cout << "Bellman-Ford mencari h(v)\n";


    for (int i = 1; i <= n; i++) {
        bool berubah = false;


        for (auto edge : extendedEdges) {
            int u = edge.u;
            int v = edge.v;
            long long w = edge.w;


            if (h[u] != INF &&
                h[v] > h[u] + w) {


                h[v] = h[u] + w;
                berubah = true;
            }
        }


        if (!berubah) {
            break;
        }
    }


    // Cek negative cycle
    for (auto edge : extendedEdges) {
        int u = edge.u;
        int v = edge.v;
        long long w = edge.w;


        if (h[u] != INF &&
            h[v] > h[u] + w) {


            cout << "Graph memiliki negative cycle.\n";
            cout << "Johnson tidak dapat digunakan.\n";


            return 0;
        }
    }


    cout << "\nNilai h(v):\n";


    for (int v = 1; v <= n; v++) {
        cout << "h(V" << v << ") = "
             << h[v] << endl;
    }


    // ==================================================
    // LANGKAH 3: REWEIGHTING
    // ==================================================


    cout << "\n===== LANGKAH 3 =====\n";
    cout << "Reweighting: w'(u,v) = w(u,v) + h(u) - h(v)\n";


    vector<vector<pair<int, long long>>> newAdj(n + 1);


    for (auto edge : edges) {
        int u = edge.u;
        int v = edge.v;
        long long w = edge.w;


        long long newWeight =
            w + h[u] - h[v];


        newAdj[u].push_back({
            v,
            newWeight
        });


        cout << "V" << u << " -> V" << v
             << " : " << w
             << " menjadi " << newWeight
             << endl;
    }


    // ==================================================
    // LANGKAH 4: DIJKSTRA DARI SETIAP VERTEX
    // ==================================================


    cout << "\n===== LANGKAH 4 =====\n";
    cout << "Dijkstra dari setiap vertex\n";


    vector<vector<long long>> allDist(
        n + 1,
        vector<long long>(n + 1, INF)
    );


    for (int start = 1; start <= n; start++) {
        vector<long long> dist(n + 1, INF);


        priority_queue<
            pair<long long, int>,
            vector<pair<long long, int>>,
            greater<pair<long long, int>>
        > pq;


        dist[start] = 0;
        pq.push({0, start});


        while (!pq.empty()) {
            long long d = pq.top().first;
            int u = pq.top().second;
            pq.pop();


            if (d != dist[u]) {
                continue;
            }


            for (auto edge : newAdj[u]) {
                int v = edge.first;
                long long w = edge.second;


                if (dist[v] > dist[u] + w) {
                    dist[v] = dist[u] + w;
                    pq.push({dist[v], v});
                }
            }
        }


        // Kembalikan ke jarak asli
        for (int v = 1; v <= n; v++) {
            if (dist[v] != INF) {
                allDist[start][v] =
                    dist[v] - h[start] + h[v];
            }
        }


        cout << "Dijkstra dari V" << start
             << " selesai.\n";
    }


    // ==================================================
    // LANGKAH 5: MATRIKS JARAK
    // ==================================================


    cout << "\n===== LANGKAH 5 =====\n";
    cout << "Matriks jarak akhir Johnson\n\n";


    cout << setw(5) << " ";


    for (int j = 1; j <= n; j++) {
        cout << setw(6) << ("V" + to_string(j));
    }


    cout << endl;


    for (int i = 1; i <= n; i++) {
        cout << setw(5) << ("V" + to_string(i));


        for (int j = 1; j <= n; j++) {
            if (allDist[i][j] == INF) {
                cout << setw(6) << "-";
            } else {
                cout << setw(6) << allDist[i][j];
            }
        }


        cout << endl;
    }


    // ==================================================
    // HASIL SOURCE -> TARGET
    // ==================================================


    cout << "\n===== HASIL JOHNSON =====\n";


    if (allDist[source][target] == INF) {
        cout << "Tidak ada rute.\n";
    } else {
        cout << "Jarak minimum dari V" << source
             << " ke V" << target
             << " = " << allDist[source][target]
             << endl;
    }


    return 0;
}
