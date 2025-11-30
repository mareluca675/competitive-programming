#include <bits/stdc++.h>

const int INF = INT_MAX / 2;

typedef std::vector<std::vector<std::vector<int>>> VVVI;
typedef std::vector<std::vector<int>> VVI;
typedef std::vector<int> VI;    

struct Ateleport {
    int dist;
    int from;
    int k;
    int l;

    bool operator>(const Ateleport& other) const {
        return dist > other.dist;
    }
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    std::freopen("ateleport.in", "r", stdin);
    std::freopen("ateleport.out", "w", stdout);

    int n, m, p, l_max, k_max;
    std::cin >> n >> m >> p >> l_max >> k_max;

    std::vector<std::pair<int, int>> graph[n + 1];

    for(int i = 1; i <= m; ++i) {
        int x, y, c;
        std::cin >> x >> y >> c;
        graph[x].push_back(std::make_pair(y, c));
        graph[y].push_back(std::make_pair(x, c));
    }

    // Distanta minima pana la [i]
    // daca am folosit [j] teleportari
    // si suntem in al [k]-lea canal de transport
    VVVI dist(n + 1,
    VVI      (k_max + 1,
    VI       (l_max + 1, INF)));

    dist[1][0][0] = 0;

    std::priority_queue<Ateleport, std::vector<Ateleport>, std::greater<Ateleport>> pq;
    pq.push({0, 1, 0, 0});

    // La fiecare pas avem 2 optini:
    // 1. Mergem normal
    // 2. Ne teleportam

    while(!pq.empty()) {
        int d = pq.top().dist;
        int from = pq.top().from;
        int l = pq.top().l;
        int k = pq.top().k;
        pq.pop();

        if(d > dist[from][k][l]) continue;
        
        for(auto [to, cost] : graph[from]) {
            // 1. Mergem normal
            if(dist[to][k][0] > d + cost) {
                dist[to][k][0] = d + cost;
                pq.push({dist[to][k][0], to, k, 0});
            }

            // 2. Ne teleportam
            
            // a) Continuam teleportarea curenta
            if(l < l_max && l > 0) {
                if(dist[to][k][l + 1] > d) {
                    dist[to][k][l + 1] = d;
                    pq.push({dist[to][k][l + 1], to, k, l + 1});
                }
            }

            // b) Cream alta teleportare
            if(k < k_max) {
                if(dist[to][k + 1][1] > d + p) {
                    dist[to][k + 1][1] = d + p;
                    pq.push({dist[to][k + 1][1], to, k + 1, 1});
                }
            }
        }
    }

    int answer = INF;
    for(int i = 0; i <= k_max; ++i)
        for(int j = 0; j <= l_max; ++j)
            answer = std::min(answer, dist[n][i][j]);
    
    std::cout << answer;
    return 0;
}