#include <bits/stdc++.h>

const std::string FILE_NAME = "";
std::ifstream fin(FILE_NAME + ".in");
std::ofstream fout(FILE_NAME + ".out");

int main() {
    std::ios_base::sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);

    int n;
    std::cin >> n;
    std::vector<int> a(n);

    for(int i = 0; i < n; ++i)
        std::cin >> a[i];
}