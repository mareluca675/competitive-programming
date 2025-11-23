#include <bits/stdc++.h>

int main() {


    int t;
    std::cin >> t;

    while(t--) {
        int n, l, r;
        std::cin >> n >> l >> r;

        // Numarul maxim de puncte pe care il pot obtine
        // daca se afla pe rank-ul i si 
        // 0 - nu accepta oferta j
        // 1 - accepta oferta j
        std::vector<std::vector<int>> dp(r + 1, std::vector<int>(2));
        dp[l][0] = 0;

        for(int i = l + 1; i <= r; ++i) {
            dp[i][0] = std::max(
                dp[i - 1][0],
                dp[i - 1][1]
            );
        }
    }
}