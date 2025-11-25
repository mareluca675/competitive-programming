#include <bits/stdc++.h>

const int NMAX = 30005;
const int MAX_EXPONENT = 7;

int multime[MAX_EXPONENT] = { 2, 3, 7, 11, 19, 23, 37 };

int bit_mask(int x) {
    int bitMask = 0;
    for(int i = 0; i < 7; ++i)
        bitMask |= ((x % multime[i] == 0) ? (1 << i) : 0);
    return bitMask;
}

int dp[NMAX][(1 << MAX_EXPONENT)];

int main() {
    std::freopen("poly.in", "r", stdin);
    std::freopen("poly.out", "w", stdout);
    // std::freopen("input.txt", "r", stdin);
    // std::freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;

        int bitMask = bit_mask(x);

        for(int s = 0; s <= (1 << 7) - 1; ++s) {
            dp[i][s] = std::max(
                dp[i - 1][s],
                dp[i][s]
            );

            if((bitMask & s) == 0) {
                dp[i][bitMask] = std::max(
                    dp[i][bitMask],
                    dp[i - 1][s] + 1
                );
            }
        }
    }

    int answer = dp[n][0];
    for(int s = 1; s <= (1 << 7) - 1; ++s)
        answer = std::max(dp[n][s], answer);

    std::cout << answer;
    return 0;
}