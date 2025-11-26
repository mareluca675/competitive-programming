#include <bits/stdc++.h>

const int MOD = 1e9 + 7;
const int MAX_NUMBER = 71;
const int MAX_PRIMES = 19;

int primes[MAX_PRIMES] = {
    2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67
};

std::vector<std::vector<int>> dp;
std::vector<int> state;
std::vector<int> f;
std::vector<int> pow2;

void compute_powers_of_two(int limit) {
    pow2.resize(limit + 1);
    pow2[0] = 1;

    for(int i = 1; i <= limit; ++i)
        pow2[i] = (pow2[i - 1] << 1) % MOD;
}

void compute_states(std::vector<int> f, std::vector<int>& state) {
    for (int i = 1; i < MAX_NUMBER; ++i) {
        if (f[i]) {
            int current = i;

            for (int j = 0; j < MAX_PRIMES && primes[j] <= current; ++j) {
                while(current != 1 && current % primes[j] == 0) {
                    state[i] ^= (1 << j);
                    current /= primes[j];

                    // std::cout << i << ' ' << states[i] << '\n';
                }
            }
        }
    }
}

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    f.resize(MAX_NUMBER, 0);

    for (int i = 0; i < n; ++i) {
        int x;
        std::cin >> x;
        ++f[x];
    }

    state.resize(MAX_NUMBER, 0);
    compute_states(f, state);
    compute_powers_of_two(n);

    // Numarul de submultimi folosind valori mai mici ca [i] 
    // care au starea [bitMask]

    // Cazul 1: folosim un numar par de numere de [i],
    // astfel putem lua submultimile de dinainte, fiindca nu
    // adaugam factori primi la putere impara
    
    // Cazul 2: folosim un numar impar de numere de [i],
    // astfel putem lua doar submultimile care au si ele
    // aceiasi factori primi la putere impara, pentru ca
    // produsul final sa ii aiba la putere para
    dp.resize(MAX_NUMBER, std::vector<int>(1 << MAX_PRIMES, 0));

    dp[0][0] = 1;

    for(int i = 1; i < MAX_NUMBER; ++i) {
        for(int bitMask = 0; bitMask < (1 << MAX_PRIMES); ++bitMask) {
            if(f[i]) {
                dp[i][bitMask] = (
                    ((1LL * dp[i - 1][bitMask] % MOD * pow2[f[i] - 1] % MOD) % MOD +
                     (1LL * dp[i - 1][bitMask ^ state[i]] % MOD * pow2[f[i] - 1] % MOD) % MOD) % MOD
                );
            }
            else {
                dp[i][bitMask] = dp[i - 1][bitMask];
            }
        }
    }

    std::cout << (dp[MAX_NUMBER - 1][0] - 1 + MOD) % MOD;
    return 0;
}