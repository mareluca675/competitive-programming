#include <bits/stdc++.h>

std::ifstream fin("birocratie.in");
std::ofstream fout("birocratie.out");

const int INF = INT_MAX / 2;

int main() {
    int n;
    fin >> n;

    std::vector<std::vector<int>> b(n, std::vector<int>(n));

    for(int i = 0; i < n; ++i)
        for(int j = 0; j < n; ++j)
            fin >> b[i][j];
    
    std::vector<std::vector<int>> dp(n, std::vector<int>(n, -INF));
    dp[0][0] = b[0][0];

    for(int s = 1; s <= (n - 1) * 2; ++s) {
        int i_min = std::max(0, s - (n - 1));
        int i_max = std::min(n - 1, s);

        std::vector<int> tip1(n, -INF), tip2(n, -INF), tip3(n, -INF);

        for(int i = i_min; i <= i_max; ++i) {
            int j = s - i;

            if(i > 0) {
                tip1[i] = std::max(
                    tip1[i],
                    dp[i - 1][j] + b[i][j]
                );
            }

            if(j > 0) {
                tip1[i] = std::max(
                    tip1[i],
                    dp[i][j - 1] + b[i][j]
                );
            }
        }

        tip2[i_min] = tip1[i_min];
        for(int i = i_min + 1; i <= i_max; ++i) {
            int j = s - i;

            tip2[i] = std::max(
                tip1[i],
                tip2[i - 1] + b[i][j]
            );
        }

        tip3[i_max] = tip1[i_max];
        for(int i = i_max - 1; i >= i_min; --i) {
            int j = s - i;

            tip3[i] = std::max(
                tip1[i],
                tip3[i + 1] + b[i][j]
            );
        }

        for (int i = i_min; i <= i_max; ++i) {
            int j = s - i;

            dp[i][j] = std::max({
                tip1[i], 
                tip2[i], 
                tip3[i]
            });
        }
    }

    fout << dp[n - 1][n - 1];
    return 0;
}