#include <bits/stdc++.h>

const int INF = INT_MAX / 2;

std::set<std::tuple<int, int, int>> q;

std::vector<std::vector<int>> dist;
std::vector<std::vector<std::pair<int, int>>> graph;
std::vector<int> drag;

int main() {
    std::freopen("dragoni.in", "r", stdin);
    std::freopen("dragoni.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    int n, m;
    std::cin >> n >> m;

    drag.resize(n + 1);
    for(int i = 1; i <= n; ++i) {
        std::cin >> drag[i];
    }

    graph.resize(n + 1); 

    for(int i = 1; i <= m; ++i) {
        int from, to, distance;
        std::cin >> from >> to >> distance;
        graph[from].push_back(std::make_pair(to, distance));
        graph[to].push_back(std::make_pair(from, distance));
    }

    if(t == 1) {
        std::queue<int> q;
        q.push(1);

        int maximum = drag[1];
       
        std::vector<bool> visited(n + 1);
        visited[1] = true;

        while(!q.empty()) {
            int node = q.front();
            q.pop();

            for(auto [to, distance] : graph[node]) {
                if(distance <= drag[1] && !visited[to]) {
                    q.push(to);
                    maximum = std::max(maximum, drag[to]);
                    visited[to] = true;
                }
            }
        }

        std::cout << maximum;
    }
    else if(t == 2) {
        q.insert(std::make_tuple(0, 1, 1));
        
        dist.resize(n + 1, std::vector<int>(n + 1, INF));
        dist[1][1] = 0;

        while(!q.empty()) {
            auto [d, from, current] = *q.begin();
            q.erase(q.begin());

            if(from == n) {
                std::cout <<  d;
                return 0;
            }

            if(d > dist[from][current]) continue;

            // Am ajuns cu un alt dragon intr-un timp mai bun?
            if(dist[from][from] > dist[from][current]) {

                // Stergem distanta veche
                if(dist[from][from] != INF) {
                    q.erase(q.find(std::make_tuple(dist[from][from], from, from)));
                }

                // O adaptam, dar pastram dragonul diferit
                dist[from][from] = dist[from][current];
                q.insert(std::make_tuple(dist[from][from], from, from));
            } 

            for(auto [to, cost] : graph[from]) {
                if(dist[from][current] + cost < dist[to][current] && drag[current] >= cost) {
                    if(dist[to][current] != INF) {
                        q.erase(q.find(std::make_tuple(dist[to][current], to, current)));
                    }

                    dist[to][current] = dist[from][current] + cost;
                    q.insert(std::make_tuple(dist[to][current], to, current));
                }
            }
        }
    }

    return 0;
}