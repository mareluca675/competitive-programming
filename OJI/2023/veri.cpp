#include <bits/stdc++.h>

std::ifstream fin("veri.in");
std::ofstream fout("veri.out");

const int NMAX = 5005;
std::vector<bool> visited(NMAX, 0);
std::vector<int> graph[NMAX];

int DFS(int start) {
    visited[start] = true;
    for(int neighbour : graph[start]) {
        if(!visited[neighbour]) {
            DFS(neighbour);
        }
    }
}

int main() {
    int c;
    fin >> c;

    int n, m;
    fin >> n >> m;

    int s, a, b;
    fin >> s >> a >> b;

    for(int i = 1; i <= m; ++i) {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(y);
    }

    // Primul subtask - 30 puncte
    // Muchiile sunt de forma { i, (i % n) + 1}
    // Asta inseamna de fapt ({ 1, 2 }; { 2, 3 }; ...; { n, 1 })
    // adica formeaza deja un ciclu
    // Distantele se pot calcula matematic
    // Pt A, distanta = (A - S + L) % L, unde L este lungimea ciclului
    // Analog pentru B

    if(c == 1) {
        int drum_minim = INT_MAX;
        for(int i = 1; i <= n; ++i) {
            drum_minim = std::min(
                i + (a - s + i) % n,
                i + (b - s + i) % n
            );
        }

        fout << drum_minim;
    }

    return 0;
}