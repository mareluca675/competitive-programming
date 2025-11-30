#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);
    int n, m;
    std::cin >> n >> m;

    std::vector<std::pair<int, int>> graph[n + 1];

    for(int i = 1; i <= n; ++i) {
        int x, y, c;
        std::cin >> x >> y >> c;
        graph[x].push_back({y, c});
        graph[y].push_back({x, c});
    }
}
