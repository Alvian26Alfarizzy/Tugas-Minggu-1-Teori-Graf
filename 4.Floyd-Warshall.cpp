#include <iostream>
#include <vector>
#include <iomanip>
#include <string>


using namespace std;


const int INF = 1e9;


int main() {
    int n, m;
    int source, target;


    cout << "===== FLOYD-WARSHALL =====\n";


    cout << "Masukkan jumlah vertex dan edge: ";
    cin >> n >> m;


    vector<vector<int>> dist(
        n + 1,
        vector<int>(n + 1, INF)
    );


    vector<vector<int>> nextVertex(
        n + 1,
        vector<int>(n + 1, -1)
    );


    // Inisialisasi jarak ke diri sendiri
    for (int i = 1; i <= n; i++) {
        dist[i][i] = 0;
        nextVertex[i][i] = i;
    }


    cout << "Masukkan edge (u v bobot):\n";


    for (int i = 0; i < m; i++) {
        int u, v, w;
        cin >> u >> v >> w;


        // Graph tidak berarah
        if (w < dist[u][v]) {
            dist[u][v] = w;
            dist[v][u] = w;


            nextVertex[u][v] = v;
            nextVertex[v][u] = u;
        }
    }


    cout << "Masukkan source dan target: ";
    cin >> source >> target;


    cout << "\n===== MATRIKS AWAL D(0) =====\n";


    cout << setw(5) << " ";


    for (int j = 1; j <= n; j++) {
        cout << setw(5) << ("V" + to_string(j));
    }


    cout << endl;


    for (int i = 1; i <= n; i++) {
        cout << setw(5) << ("V" + to_string(i));


        for (int j = 1; j <= n; j++) {
            if (dist[i][j] == INF) {
                cout << setw(5) << "-";
            } else {
                cout << setw(5) << dist[i][j];
            }
        }


        cout << endl;
    }


    cout << "\n===== PROSES FLOYD-WARSHALL =====\n";


    // k = vertex perantara
    for (int k = 1; k <= n; k++) {
        cout << "\nMenggunakan V" << k
             << " sebagai vertex perantara:\n";


        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= n; j++) {


                if (dist[i][k] == INF ||
                    dist[k][j] == INF) {
                    continue;
                }


                int jarakBaru =
                    dist[i][k] + dist[k][j];


                if (jarakBaru < dist[i][j]) {
                    cout << "  Update V" << i
                         << " -> V" << j
                         << " : " << dist[i][j]
                         << " -> " << jarakBaru
                         << " melalui V" << k
                         << endl;


                    dist[i][j] = jarakBaru;


                    nextVertex[i][j] =
                        nextVertex[i][k];
                }
            }
        }
    }


    cout << "\n===== HASIL FLOYD-WARSHALL =====\n";


    if (dist[source][target] == INF) {
        cout << "Tidak ada rute.\n";
    } else {
        cout << "Jarak minimum = "
             << dist[source][target]
             << endl;


        cout << "Rute = V" << source;


        int current = source;


        while (current != target) {
            current = nextVertex[current][target];
            cout << " -> V" << current;
        }


        cout << endl;
    }


    return 0;
}

