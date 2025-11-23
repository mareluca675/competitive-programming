#include <bits/stdc++.h>

const int INF = 0x3f3f3f3f / 2;

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    freopen("bellmanford.in", "r", stdin);
    freopen("bellmanford.out", "w", stdout);

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

    std::vector<int> frec(n + 1, 0);
    
    std::bitset<50005> in_queue;

    std::queue<int> q;
    q.push(1);

    while(!q.empty()) { 
        int from = q.front();
        q.pop();
        in_queue[from] = false;

        for (auto [to, cost] : edges[from]) {
            if (dist[to] > dist[from] + cost) {
                dist[to] = dist[from] + cost;

                if (!in_queue[to]) {
                    if (frec[to] > n) {
                        std::cout << "Ciclu negativ!" << std::endl;
                        return 0;
                    }
                    else {
                        q.push(to);
                        frec[to]++;
                    }
                }
            }
        }
    }

    for(int i = 2; i <= n; i++) {
        std::cout << dist[i] << " ";
    }

    return 0;
}
