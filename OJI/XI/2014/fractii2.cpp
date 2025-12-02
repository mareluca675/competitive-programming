#include <bits/stdc++.h>

const int MOD = 100003;
const int NMAX = 2005;

// Pt. cerinta 2
// Numarul de modalitati de a scrie 1
// ca suma de primele [i] fractii
// in care cea mai mica fractie
// apare de maxim 2 * [j] ori
int dp[NMAX][NMAX / 2];

int main() {
    std::freopen("fractii2.in", "r", stdin);
    std::freopen("fractii2.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int c;
    std::cin >> c;

    int n;
    std::cin >> n;

    if(c == 1) {
        std::deque<int> dq;
        int k = 1;
        dq.push_back(0);

        while(k < n) {
            dq.push_front(1 + dq.back());
            dq.push_front(1 + dq.back());
            dq.pop_back();
            ++k;
        }

        while(!dq.empty()) {
            std::cout << dq.back() << ' ';
            dq.pop_back();
        }
    }
    else {
        dp[2][1] = 1;

        for(int i = 3; i <= n; ++i) {
            for(int j = 1; j <= i / 2; ++j) {
                // Voi lua toate cazurile posibile
                // si voi scadea cele invalide

                // Grupa parinte din care vine
                // Daca grupa are [i] elemente
                // si elementul minim apare de 2 * [j] ori
                // inseamna ca a provenit dintr-o 
                // grupa parinte in care minimul
                // apare de [j] ori
                // Practic, a dat split la cele [j] elemente
                // astfel s-au format [j] elemente in plus
                int parent = (i - j);

                // Numarul maxim de perechi
                // pe care il are o multime de M
                // elemente este egal cu M / 2
                int parentMaxPairs = (i - j) / 2;
                
                // Cele invalide sunt cele in care
                // nu am destule elemente pentru split
                // Daca in solutia curenta am 2 * [j]
                // elemente minime, asta inseamna
                // ca grupa parine trebuie
                // sa aiba minim [j] elemente minime
                // Astfel, limita inferioara
                // este k = (j + 1) / 2 - 1,
                // adica grupa trebuie sa aiba minim
                // k + 1 elemente minime, altfel
                // nu se poate realiza split-ul
                int invalidPairs = (j + 1) / 2 - 1;

                dp[i][j] = ((dp[i][j - 1] % MOD
                           + dp[parent][parentMaxPairs]) % MOD
                           - dp[parent][invalidPairs] + MOD) % MOD;
            }
        }

        // Din moment ce am adunat toate solutiile,
        // solutia finala este in ultima componenta
        // a matricii
        std::cout << dp[n][n / 2];
        return 0;
    }
}