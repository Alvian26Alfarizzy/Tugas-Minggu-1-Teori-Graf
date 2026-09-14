# Penerapan 5 Algoritma Shortest Path

Repository ini berisi implementasi 5 algoritma **Shortest Path** menggunakan C++ berdasarkan graph berbobot tidak berarah pada tugas Teori Graf.

## Daftar Algoritma

1. [Dijkstra](#1-dijkstra)
2. [Bellman-Ford](#2-bellman-ford)
3. [Floyd-Warshall](#3-floyd-warshall)
4. [A-Star](#4-a-star-a-star)
5. [Johnson](#5-johnson)

---



### 1. Dijkstra

### Prinsip: Memilih vertex yang memiliki jarak sementara paling kecil, kemudian memperbarui jarak vertex tetangganya.

code:

```
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

            cout << "  Periksa V" << v
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
```

### 2. Bellman-Ford

Prinsip: Melakukan relaksasi seluruh edge berulang kali sebanyak V−1V-1 iterasi. Pada graph ini terdapat 11 vertex, sehingga dilakukan maksimal: V−1=11−1=10 iterasi 
code:

```
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
                cout << "  Update V" << v
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
```

### 3. Floyd-Warshall

Prinsip: Menghitung jarak terpendek antara semua pasangan vertex menggunakan pendekatan *dynamic programming*.
Untuk mencari V1 menuju V11, algoritma ini membandingkan kemungkinan jalur melalui vertex perantara.
code:

```
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
                    cout << "  Update V" << i
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
```

**4. A\* (A-Star) **
Prinsip: Menggunakan fungsi evaluasi: f(n)=g(n)+h(n)
Keterangan:

- g(n) = biaya dari V1 menuju vertex nn.
- h(n) = estimasi biaya dari nn menuju V11.
- f(n) = perkiraan total biaya.

Karena graph pada soal tidak menyediakan koordinat atau informasi heuristik, digunakan: h(n)=0 Dengan demikian, A\* bekerja seperti Dijkstra
Dengan implementasi A* pada graph ini, jalur yang diperoleh dapat dibandingkan dengan hasil Dijkstra.  V1→V2→V5→V8→V11
code:

```
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

            cout << "  Periksa V" << v
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
```

### 5. Johnson

### Johnson cocok ditambahkan karena merupakan algoritma All-Pairs Shortest Path, yaitu mencari jarak terpendek antara semua pasangan vertex. Algoritma ini menggunakan Bellman-Ford untuk menghitung bobot potensial, kemudian Dijkstra dari setiap vertex.

### Cara kerja Johnson

1. Tambahkan vertex baru V0V\_0 yang terhubung ke semua vertex dengan bobot 0.
2. Jalankan Bellman-Ford untuk mendapatkan nilai potensial h(v)h(v).
3. Ubah bobot setiap edge menggunakan: w′(u,v)=w(u,v)+h(u)−h(v)

4) Jalankan Dijkstra dari setiap vertex menggunakan bobot baru.
5) Kembalikan jarak ke bobot asli: d(u,v)=d′(u,v)−h(u)+h(v)

```
code:
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
```

---

## Cara Menjalankan

Setiap algoritma disimpan dalam file C++ terpisah:

```text
01_dijkstra.cpp
02_bellman_ford.cpp
03_floyd_warshall.cpp
04_a_star.cpp
05_johnson.cpp
```

Compile salah satu program dengan `g++`, contoh:

```bash
g++ 01_dijkstra.cpp -o dijkstra
./dijkstra
```

Program akan meminta:

```text
Masukkan jumlah vertex dan edge:
Masukkan edge (u v bobot):
Masukkan source dan target:
```

Untuk graph pada tugas, masukkan data edge sesuai graph yang diberikan dosen. Contoh source dan target:

```text
1 11
```

artinya mencari shortest path dari **V1 menuju V11**.

## Catatan A*

Graph pada tugas tidak menyediakan koordinat atau informasi heuristik. Oleh karena itu digunakan:

```text
h(n) = 0
```

sehingga fungsi:

```text
f(n) = g(n) + h(n)
```

menjadi:

```text
f(n) = g(n)
```

Dengan kondisi tersebut, A* berperilaku seperti Dijkstra untuk graph ini.

## Struktur Repository

```text
Tugas-Minggu-1-Teori-Graf/
├── 01_dijkstra.cpp
├── 02_bellman_ford.cpp
├── 03_floyd_warshall.cpp
├── 04_a_star.cpp
├── 05_johnson.cpp
├── graph_edges.txt
└── README.md
```

## Ringkasan

| No. | Algoritma | Fungsi utama |
|---|---|---|
| 1 | Dijkstra | Shortest path dari satu source |
| 2 | Bellman-Ford | Shortest path dan deteksi negative cycle |
| 3 | Floyd-Warshall | Shortest path semua pasangan vertex |
| 4 | A* | Shortest path menggunakan fungsi evaluasi `f(n)=g(n)+h(n)` |
| 5 | Johnson | Shortest path semua pasangan dengan Bellman-Ford + Dijkstra |

---
