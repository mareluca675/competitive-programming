#include <bits/stdc++.h>

int main() {
    std::freopen("aventura.in", "r", stdin);
    std::freopen("aventura.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int n;
        std::cin >> n;

        std::vector<int> remainingDependents(n + 1);

        // Ce nivel trebuie sa completez ca sa ajung la nivelul [j]
        std::vector<std::vector<int>> dependents(n + 1);
        std::queue<int> q;
        
        for(int i = 1; i <= n; ++i) {
            int m;
            std::cin >> m;

            if(m == 0)
                q.push(i);

            for(int j = 1; j <= m; ++j) {
                int k;
                std::cin >> k;

                ++remainingDependents[i];
                dependents[k].push_back(i);
            }
        }

        int completed = 0;

        while(!q.empty()) {
            int level = q.front();
            q.pop();
            ++completed;

            for(int dependent : dependents[level]) {
                --remainingDependents[dependent];

                if(remainingDependents[dependent] == 0) {
                    q.push(dependent);
                }
            }
        }

        std::cout << completed << '\n';
    }

    return 0;
}