#include <bits/stdc++.h>

int main() {
    int t;
    std::cin >> t;

    while(t--) {
        int n;
        std::cin >> n;

        if(n == 1) {
            std::cout << 1 << '\n';
        }
        else if(n == 2) {
            std::cout << 9 << '\n';
        }
        else if(n == 3) {
            std::cout << 29 << '\n';
        }
        else if(n == 4) {
            std::cout << 56 << '\n';
        }
        else {
            std::cout << 5 * n * n - 5 * n - 5 << '\n';
        }
    }
}