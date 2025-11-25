#include <bits/stdc++.h>

const int MAX_EXPONENT = 22;

int dp[1 << MAX_EXPONENT];

int main() {
    std::freopen("coins.in", "r", stdin);
    std::freopen("coins.out", "w", stdout);
    // std::freopen("input.txt", "r", stdin);
    // std::freopen("output.txt", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    for(int i = 1; i <= MAX_EXPONENT; ++i)
        dp[(1 << i) - 1] = true;
    
    // Game Theory
    for(int bitMask = 0; bitMask <= (1 << MAX_EXPONENT) - 1; ++bitMask) {
        if(!(bitMask & (bitMask + 1))) // Pozitie de castig (111...000...(2))
            continue;

        for(int i = 1; i < MAX_EXPONENT; ++i) {
            if((bitMask & (1 << i))) { // Verificam daca avem un coin pe pozitia [i]
                int j = i - 1; // Cautam primul patratel gol

                while(j >= 0 && (bitMask & (1 << j)))
                    --j;

                if(j >= 0) { // Am gasit un patratel gol
                    // Aflam pozitia anterioara 
                    // prin a schimba bitii [i] si [j]
                    int previousMask = (bitMask & ~(1 << i)) | (1 << j); 
                    dp[bitMask] |= !dp[previousMask];
                }
            }
        }
    }

    int n;
    std::cin >> n;

    int answer = 0;
    for(int i = 0; i < n; ++i) {
        int x, coins = 0, bitMask = 0;

        for(int j = 0; j < MAX_EXPONENT; ++j) {
            std::cin >> x;
            coins += x;
            bitMask |= x * (1 << j);
        }

        if(dp[bitMask] == true) {
            answer += coins;
        }
    }

    std::cout << answer;
    return 0;
}