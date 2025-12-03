#include <bits/stdc++.h>

const std::string FILE_NAME = "recyclebin";
std::ifstream fin(FILE_NAME + ".in");
std::ofstream fout(FILE_NAME + ".out");

const int NMAX = 1024;
const int VAL_MAX = 10;

int n;
std::vector<std::vector<int>> dp(NMAX, std::vector<int>(1 << VAL_MAX, 0));
std::vector<int> a;

int main() {
    std::ios_base::sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);

    fin >> n;
    a.resize(n);

    for(int i = 0; i < n; ++i) {
        fin >> a[i];
    }

    // Vom nota in dp suma maxima
    // pe care o putem realiza
    // folosind primele [i] elemente
    // si stergand numarul de elemente
    // marcat cu unu in [bitmask]

    int answer = 0;

    for(int i = 0; i < n; ++i) {
        for(int mask = 0; mask < (1 << VAL_MAX); ++mask) {
            if(i == 0)
                dp[i][mask] = std::max(a[i], 0);
            else
                dp[i][mask] = std::max(dp[i - 1][mask] + a[i], 0);

            for(int k = 0; (1 << k) <= i; ++k) {
                if(mask & (1 << k)) {
                    dp[i][mask] = std::max(
                        dp[i][mask],
                        dp[i - (1 << k)][mask - (1 << k)]
                    );
                }
            }

            answer = std::max(answer, dp[i][mask]);
        }
    }

    fout << answer;
    return 0;
}