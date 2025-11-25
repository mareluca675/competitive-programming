#include <bits/stdc++.h>

const int MOD = 1e9 + 7;
const int MAX_VALUE = 70;

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n;
    std::cin >> n;

    std::vector<int> f(MAX_VALUE, 0);
    for(int i = 1; i <= n; ++i) {
        int x;
        std::cin >> x;
        ++f[x];
    }

    
}