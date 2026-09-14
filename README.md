# Tugas Teori Graf — Shortest Path

Implementasi 5 algoritma dari tugas:
1. Dijkstra
2. Bellman-Ford
3. Floyd-Warshall
4. A* (A-Star)
5. Johnson

Graph pada soal adalah weighted graph tidak berarah dengan V1–V11.
Data edge disimpan di `graph_edges.txt` dan juga digunakan di masing-masing program.

## Menjalankan
Contoh:
```bash
g++ 01_dijkstra.cpp -o dijkstra
./dijkstra
```
Masukkan:
```text
1 11
```
untuk mencari rute V1 menuju V11.

Untuk A*, materi tidak menyediakan koordinat/heuristik, sehingga `h(n)=0`; akibatnya A* bekerja seperti Dijkstra.
