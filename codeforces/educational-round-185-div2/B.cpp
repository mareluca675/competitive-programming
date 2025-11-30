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
        int sum = 0, pos = 0;

        for(int i = 0; i < n; ++i) {
            int num;
            std::cin >> num;
            sum += num;
            if(num > 0) {
                ++pos;
            }
        }

        sum = sum - n + 1;
        std::cout << std::min(sum, pos) << '\n';
    }

    return 0;
}