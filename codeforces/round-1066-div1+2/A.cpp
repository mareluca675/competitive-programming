#include <bits/stdc++.h>

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int t;
    std::cin >> t;

    while(t--) {
        int n;
        std::cin >> n;
        std::vector<int> f(n + 1, 0);

        for(int i = 0; i < n; ++i) {
            int num;
            std::cin >> num;
            ++f[num];
        }

        int d = f[0];
        for(int i = 1; i <= n; ++i) {
            if(f[i] < i) {
                d += f[i];
            }
            else if(f[i] > i) {
                d += (f[i] - i);
            }
        }

        std::cout << d << '\n';
    }

    return 0;
}