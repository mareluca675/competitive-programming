#include <bits/stdc++.h>

const int NMAX = 500005;

std::unordered_map<int, std::vector<int>> map;
int valX[NMAX],valY[NMAX],valZ[NMAX];
int n, a, b;

int BFS(int start) {
    std::vector<bool> visited(n, false);
    std::vector<int> distance(n, 0);
    std::queue<int> q;

    q.push(start);
    distance[start] = 0;
    visited[start] = true;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        if(node == b) {
            return distance[b];
        }

        int valXYZ[3] = {
            valX[node],
            valY[node],
            valZ[node]
        };

        for(int val : valXYZ) {
            for(int neighbour : map[val]) {
                if(!visited[neighbour]) {
                    visited[neighbour] = true;
                    q.push(neighbour);
                    distance[neighbour] = distance[node] + 1;
                }
            }

            map[val].clear();
        }
    }

    return -1;
}

int main() {
    std::freopen("nestemate.in", "r", stdin);
    std::freopen("nestemate.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        std::cin >> n >> a >> b;
        --a, --b;
        
        map.clear();

        for(int i = 0; i < n; ++i) {
            int x, y, z;
            std::cin >> x >> y >> z;
            valX[i] = x;
            valY[i] = y;
            valZ[i] = z;

            map[x].push_back(i);
            map[y].push_back(i);
            map[z].push_back(i);
        }

        std::cout << BFS(a) << '\n';
    }

    return 0;
}