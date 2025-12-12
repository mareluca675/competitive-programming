#include <bits/stdc++.h>

const std::string FILE_NAME = "joc";
std::ifstream fin(FILE_NAME + ".in");
std::ofstream fout(FILE_NAME + ".out");

int n, k_lim;
int joc[2][5005];
int dp[2][5005][15];

int main() {
    std::ios_base::sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);

    fin >> n >> k_lim;
    for(int i = 0; i < 2; ++i)
        for(int j = 0; j < n; ++j)
            fin >> joc[i][j];

    for(int k = 0; k < k_lim; ++k) {
        dp[0][0][k] = joc[0][0];
        dp[1][0][k] = joc[0][0] + joc[1][0];
    }

    for(int j = 1; j < n; ++j) {
        for(int i = 0; i < 2; ++i) {
            for(int k = 0; k < k_lim; ++k) {
                if(k == 0) {
                    dp[i][j][k] = dp[1 - i][j - 1][k_lim - 2] + joc[i][j] + joc[1 - i][j];
                }
                else {
                    dp[i][j][k] = std::max(
                        dp[i][j - 1][k - 1] + joc[i][j],
                        dp[1 - i][j - 1][k_lim - 2] + joc[i][j] + joc[1 - i][j]
                    );
                }
            }
        }
    }

    fout << dp[1][n - 1][k_lim - 1];
    return 0;
}