// MY SOLUTION FOR DIJKSTRA ALGORITHM

#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f / 2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    freopen("dijkstra.in", "r", stdin);
    freopen("dijkstra.out", "w", stdout);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> edges[n + 1];
    for (int i = 0; i < m; i++) {
        int u, v, w;
        std::cin >> u >> v >> w;
        edges[u].push_back({v, w});
    }

    std::vector<int> dist(n + 1, INF);
    dist[1] = 0;

    using pii = std::pair<int, int>;
    std::set<pii> q;
    q.insert({0, 1});

    while(!q.empty()) {
        auto [d, from] = *q.begin();
        q.erase(q.begin());

        if (d > dist[from]) continue;

        for (auto [to, cost] : edges[from]) {
            if (dist[to] > dist[from] + cost) {
                if (dist[to] != INF) {
                    q.erase(q.find({dist[to], to}));
                }

                dist[to] = dist[from] + cost;
                q.insert({dist[to], to});
            }
        }
    }

    for(int i = 2; i <= n; i++) {
        std::cout << (dist[i] == INF ? 0 : dist[i]) << " ";
    }

    return 0;
}

// END OF MY SOLUTION

// OFFICIAL SOLUTION FOR DIJKSTRA ALGORITHM

/*
#include <algorithm>
#include <fstream>
#include <cstring>
#include <cassert>
#include <vector>
#include <set>
using namespace std;

const int NMAX = 50005;
const int INF = 0x3f3f3f3f;

vector<pair<int, int>> G[NMAX];

int dist[NMAX];

int main() {
    ifstream fin("dijkstra.in");
    ofstream fout("dijkstra.out");

    int n, m;
    fin >> n >> m;
    assert(1 <= n && n <= 50000);
    assert(1 <= m && m <= 250000);

    for (int i = 0; i < m; ++i) {
        int from, to, cost;
        fin >> from >> to >> cost;
        assert(1 <= from && from <= n);
        assert(1 <= to && to <= n);
        assert(0 <= cost && cost <= 20000);
        G[from].push_back(make_pair(to, cost));
    }

    memset(dist, INF, sizeof dist);
    dist[1] = 0;
    set<pair<int, int>> h;
    h.insert(make_pair(0, 1));
    while (!h.empty()) {
        int node = h.begin()->second;
        int d = h.begin()->first;
        h.erase(h.begin());

        for (vector<pair<int, int>>::iterator it = G[node].begin(); it != G[node].end(); ++it) {
            int to = it->first;
            int cost = it->second;
            if (dist[to] > dist[node] + cost) {
                if (dist[to] != INF) {
                    h.erase(h.find(make_pair(dist[to], to)));
                }
                dist[to] = dist[node] + cost;
                h.insert(make_pair(dist[to], to));
            }
        }
    }

    for (int i = 2; i <= n; ++i) {
        if (dist[i] == INF) {
            dist[i] = 0;
        }
        fout << dist[i] << ' ';
    }
    fout << '\n';

    fin.close();
    fout.close();
}
*/