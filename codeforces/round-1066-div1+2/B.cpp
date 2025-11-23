#include <iostream>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

void solve() {
    int n;
    long long x, y;
    cin >> n >> x >> y;
    string s;
    cin >> s;

    long long c4 = 0;
    long long c8 = 0;

    // Count the operations
    for (char c : s) {
        if (c == '4') c4++;
        else c8++;
    }

    // Check the 4 geometric bounds
    bool possible = true;

    x = abs(x);
    y = abs(y);

    // 1. Horizontal and Vertical bounds
    // Max extent is simply sum of all steps (both 4 and 8 contribute 1 to width/height)
    if (x > c4 + c8) possible = false;
    if (y > c4 + c8) possible = false;

    // 2. Diagonal bounds
    // '8' contributes 2 to the diagonal sum (moves 1,1)
    // '4' contributes 1 to the diagonal sum (moves 1,0 or 0,1)
    if (x + y > c4 + 2 * c8) possible = false;

    if (possible) {
        cout << "YES" << endl;
    } else {
        cout << "NO" << endl;
    }
}

int main() {
    // Optimize I/O operations
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int t;
    cin >> t;
    while (t--) {
        solve();
    }
    return 0;
}