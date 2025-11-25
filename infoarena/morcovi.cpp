#include <bits/stdc++.h>

// Suma maxima daca sunt pe pozitia [i]
// si am executat toate salturile 
// marcate cu 1 din bitmask-ul [j]
std::vector<std::vector<int>> dp;
std::vector<int> e;
std::vector<int> l;

int n, p;

int main() {
    std::freopen("morcovi.in", "r", stdin);
    std::freopen("morcovi.out", "w", stdout);
    // std::freopen("input.txt", "r", stdin);
    // std::freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> n;

    e.resize(n);
    for(int i = 0; i < n; ++i) {
        std::cin >> e[i];
    }

    std::cin >> p;

    l.resize(p);
    for(int i = 0; i < p; ++i) {
        std::cin >> l[i];
    }

    dp.resize((1 << p), std::vector<int>(n, -1));
    for(int i = 0; i < n; ++i) {
        dp[0][i] = e[i];
    }

    for(int bitMask = 1; bitMask < (1 << p); ++bitMask) {
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < p; ++j) {
                if(bitMask & (1 << j)) { // Inseamna ca am realizat saltul [j]
                    if(i >= l[j] && dp[bitMask ^ (1 << j)][i - l[j]] != -1) {
                        dp[bitMask][i] = std::max(
                            dp[bitMask ^ (1 << j)][i - l[j]] + e[i],
                            dp[bitMask][i]
                        );
                    }

                    if(i + l[j] < n && dp[bitMask ^ (1 << j)][i + l[j]] != -1) {
                        dp[bitMask][i] = std::max(
                            dp[bitMask ^ (1 << j)][i + l[j]] + e[i],
                            dp[bitMask][i]
                        );
                    }
                }
            }
        }
    }

    int answer = dp[(1 << p) - 1][0];
    for(int i = 1; i < n; ++i)
        answer = std::max(answer, dp[(1 << p) - 1][i]);
    
    std::cout << answer;
    return 0;
}
