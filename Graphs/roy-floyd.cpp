#include <bits/stdc++.h>

const int INF = INT_MAX / 2;

int main() {
    freopen("roy-floyd.in", "r", stdin);
    freopen("roy-floyd.out", "w", stdout);
    
    int n, m;
    std::cin >> n >> m;
    
    std::vector<std::vector<int>> D(n + 1, std::vector<int>(n + 1, INF));
    
    while(m--) {
        int x, y, z;
        std::cin >> x >> y >> z;
        D[x][y] = z;
    }
    
    for(int k = 1; k <= n; ++k) {
        D[k][k] = 0;
        for(int i = 1; i <= n; ++i) {
            for(int j = 1; j <= n; ++j) {
                D[i][j] = std::min(D[i][j], D[i][k] + D[k][j]);
            }
        }
    }
     
    for(int i = 1; i <= n; ++i, std::cout << '\n')
        for(int j = 1; j <= n; ++j)
            std::cout << (D[i][j] == INF ? -1 : D[i][j]) << ' ';
    
    return 0;
}