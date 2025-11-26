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