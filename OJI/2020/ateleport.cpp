#include <bits/stdc++.h>

const int INF = INT_MAX / 2;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::freopen("ateleport.in", "r", stdin);
    std::freopen("ateleport.out", "w", stdout);

    int n, m, p, l, k;
    std::cin >> n >> m >> p >> l >> k;

    std::vector<std::pair<int, int>> graph[n + 1];

    for(int i = 1; i <= m; ++i) {
        int x, y, c;
        std::cin >> x >> y >> c;
        graph[x].push_back(std::make_pair(y, c));
        graph[y].push_back(std::make_pair(x, c));
    }

    std::vector<int> dist(n + 1, INF);
    std::set<std::pair<int, int>> q;
    dist[1] = 0;
    q.insert({0, 1});

    while(!q.empty()) {
        auto[d, from] = *q.begin();
        q.erase(q.begin());

        if(d > dist[from]) continue;

        for(auto [to, cost] : graph[from]) {
            if(dist[to] > dist[from] + cost) {
                if(dist[to] != INF) {
                    q.erase(q.find({dist[to], to}));
                }

                dist[to] = dist[from] + cost;
                q.insert({dist[to], to});
            }
        }
    }

    std::cout << dist[n];
    return 0;
}