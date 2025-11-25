#include <bits/stdc++.h>

inline bool inmat(int a, int b, int n, int m) {
    return (a >= 1 && b >= 1 && a <= n && b <= m);
};

int nr_biti_unu(int x) {
    int nr = 0;
    while(x != 0) {
        x = x & (x - 1);
        ++nr;
    }

    return nr;
}

int main() {
    std::freopen("escapelight.in", "r", stdin);
    std::freopen("escapelight.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int n, m;
    std::cin >> n >> m;

    std::vector<std::vector<int>> tip(n + 1, std::vector<int>(m + 1));

    int intrerupatoare = 0;

    for(int i = 1; i <= n; ++i) {
        for(int j = 1; j <= m; ++j) {
            std::cin >> tip[i][j];
            if(tip[i][j] == 3) {
                tip[i][j] = 10 + (intrerupatoare++);
            }
        }
    }

    int iStart, jStart, iStop, jStop;
    std::cin >> iStart >> jStart >> iStop >> jStop;

    int k, p;
    std::cin >> k >> p;

    std::vector<std::vector<int>> legaturi(n + 1, std::vector<int>(m + 1, 0));

    for(int l = 1; l <= k; ++l) {
        int iSwitch, jSwitch, iLight, jLight;
        std::cin >> iSwitch >> jSwitch >> iLight >> jLight;

        int index = tip[iSwitch][jSwitch] - 10;

        legaturi[iLight][jLight] |= (1 << index);
    }

    // (i, j, stare) -> distanta
    std::vector<std::vector<std::vector<short>>> dist(1 << p, std::vector<std::vector<short>>(n + 1 , std::vector<short>(m + 1, -1)));
    std::queue<std::tuple<int, int, int>> q;

    dist[0][iStart][jStart] = 0;
    q.push(std::make_tuple(iStart, jStart, 0));

    const int di[] = {0, 0, -1, 1};
    const int dj[] = {1, -1, 0, 0};

    while(!q.empty()) {
        auto current = q.front();
        q.pop();

        int i = std::get<0>(current);
        int j = std::get<1>(current);
        int stare = std::get<2>(current);
        int d = dist[stare][i][j];

        for(int k = 0; k < 4; ++k) {
            int iv = i + di[k], jv = j + dj[k];

            bool sePoate = false;

            if(inmat(iv, jv, n, m)) {
                int flips = stare & legaturi[iv][jv];

                if(tip[iv][jv] >= 10) {
                    sePoate = true;
                }
                else if(tip[iv][jv] == 0 && nr_biti_unu(flips) % 2 == 1) {
                    sePoate = true;
                }
                else if(tip[iv][jv] == 1 && nr_biti_unu(flips) % 2 == 0){
                    sePoate = true;
                }
            }

            if(sePoate) {
                int dActuala = dist[stare][iv][jv];
                if(dActuala == -1 || dActuala > d + 1) {
                    if(iv == iStop && jv == jStop) {
                        std::cout << d + 2;
                        return 0;
                    }

                    dist[stare][iv][jv] = d + 1;
                    q.push(std::make_tuple(iv, jv, stare));
                }
            }
        }

        if(tip[i][j] >= 10) {
            int stareNoua = stare ^ (1 << (tip[i][j] - 10)); // <----- THIS LINE

            for(int k = 0; k < 4; ++k) {
                int iv = i + di[k], jv = j + dj[k];

                bool sePoate = false;

                if(inmat(iv, jv, n, m)) {
                    int flips = stareNoua & legaturi[iv][jv];

                    if(tip[iv][jv] >= 10) {
                        sePoate = true;
                    }
                    else if(tip[iv][jv] == 0 && nr_biti_unu(flips) % 2 == 1) {
                        sePoate = true;
                    }
                    else if(tip[iv][jv] == 1 && nr_biti_unu(flips) % 2 == 0){
                        sePoate = true;
                    }
                }

                if(sePoate) {
                    int dActuala = dist[stareNoua][iv][jv];
                    if(dActuala == -1 || dActuala > d + 1) {
                        if(iv == iStop && jv == jStop) {
                            std::cout << d + 2;
                            return 0;
                        }

                        dist[stareNoua][iv][jv] = d + 1;
                        q.push(std::make_tuple(iv, jv, stareNoua));
                    }
                }
            }
        }
    }

    std::cout << -1;
    return 0;
}