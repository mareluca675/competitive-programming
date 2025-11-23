#include <bits/stdc++.h>

std::ifstream fin("conexidad.in");
std::ofstream fout("conexidad.out");

const int NMAX = 10005;

int maxExtra = 1, C = 0;
std::vector<int> graph[NMAX];
std::vector<bool> visited(NMAX, 0);
std::vector<int> components[NMAX];

void DFS(int i) {
    visited[i] = true;
    components[C].push_back(i);

    for(int neighbour : graph[i]) {
        if(!visited[neighbour]) {
            DFS(neighbour);
        }
    }
}

int main() {
    int n, m;
    fin >> n >> m;

    for(int i = 1; i <= m; ++i) {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(y);
        graph[y].push_back(x);
    }

    for(int i = 1; i <= n; ++i) {
        if(!visited[i]) {
            DFS(i);
            ++C;
        }
    }

    if(n >= 2 * (C - 1)) {
        maxExtra = 1;
    }
    else {
        maxExtra = 2;
    }

    fout << maxExtra << '\n' << C - 1 << '\n';

    if(maxExtra == 1) {
        std::vector<int> compIndex(C);

        for(int i = 0; i < C; ++i)
            compIndex[i] = i;

        // Care index sa folosim din fiecare component
        // adica index-ul curent
        std::vector<int> nodeIndex(C, 0);

        // Vom folosi intotdeauna noduri din componente conectate
        std::vector<bool> connected(C, false);
        connected[compIndex[0]] = true;

        for(int i = 1; i < C; ++i) {
            int newComp = compIndex[i];

            // Cautam o componenta cu noduri neconectate
            int connectedComp = -1;

            for(int j = 0; j < i; ++j) {
                // Luam fiecare componenta mai mare de dinainte
                int comp = compIndex[j];
                
                // Verificam daca este conectata si nu are toate nodurile folosite
                if(connected[comp] && nodeIndex[comp] < components[comp].size()) {
                    connectedComp = comp;
                    break;
                }
            }

            // Vom lua nodurile conectate respective
            // Suntem la componenta connectedComp si la nodul nodeIndex[connectedComp]
            // analog newComp
            int node1 = components[connectedComp][nodeIndex[connectedComp]];
            int node2 = components[newComp][nodeIndex[newComp]];

            // Afisare
            fout << node1 << ' ' << node2 << '\n';

            // Trecem la urmatorul nod la fiecare si marcam noul nod ca fiind conectat
            ++nodeIndex[connectedComp];
            ++nodeIndex[newComp];
            connected[newComp] = true;
        }
    } else {
        // Fiindca nu avem destule noduri
        // ca sa le acoperim pe cele izolate
        // nu mai conteaza ordinea
        // si le vom pune una dupa alta, intr-un "chain"

        for(int i = 0; i < C - 1; ++i) {
            int node1 = components[i][components[i].size() - 1];
            int node2 = components[i + 1][0];

            fout << node1 << ' ' << node2 << '\n';
        }
    }

    return 0;
}