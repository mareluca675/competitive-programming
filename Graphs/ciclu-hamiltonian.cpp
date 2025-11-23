#include <bits/stdc++.h>

std::ifstream fin("hamilton.in");
std::ofstream fout("hamilton.out");

const int NMAX = 20;
const int INF = INT_MAX / 2;

// dp[mask][i] = costul minim de drum care se termina in nodul i
// vizitand toate nodurile marcate cu 1 in bitmask
int dp[1 << NMAX][NMAX];
int cost[NMAX][NMAX];

int n, m;


int main() {
    fin >> n >> m;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= n; ++j) {
            cost[i][j] = INF;
        }
    }

    for(int mask = 0; mask < (1 << n); ++mask) {
        for(int i = 1; i <= n; ++i) {
            dp[mask][i] = INF;
        }
    }
    
    for(int i = 1; i <= m; ++i) {
        int x, y, c;
        fin >> x >> y >> c;
        cost[x + 1][y + 1] = std::min(cost[x + 1][y + 1], c);
    }

    dp[1][1] = 0;

    for(int mask = 1; mask < (1 << n); ++mask) {
        if((mask & 1) == 0) {
            continue;
        }

        for(int i = 1; i <= n; ++i) {
            if(mask & (1 << (i - 1))) {
                int prevMask = mask ^ (1 << (i - 1));
                if(prevMask == 0) continue;

                for(int j = 1; j <= n; ++j) {
                    if(prevMask & (1 << (j - 1))) {
                        dp[mask][i] = std::min(dp[mask][i], dp[prevMask][j] + cost[j][i]);
                    }
                }
            }
        }
    }

    int ans = INF;
    for(int i = 2; i <= n; ++i) {
        ans = std::min(ans, dp[(1 << n) - 1][i] + cost[i][1]);
    }

    if (ans == INF) {
        fout << "Nu exista solutie";
    } else {
        fout << ans;
    }

    return 0;
}