#include <bits/stdc++.h>

const std::string FILE_NAME = "blis";
const int NMAX = 1e5 + 5;
const int INF = INT_MAX / 2;

std::ifstream fin(FILE_NAME + ".in");
std::ofstream fout(FILE_NAME + ".out");

int main() {
    std::ios_base::sync_with_stdio(false);
    fin.tie(nullptr);
    fout.tie(nullptr);

    int k;
    fin >> k;
    
    std::vector<int> bits;
    
    {
        std::string bits_str;
        fin >> bits_str;

        for(int i = 0; i < bits_str.length(); ++i)
            bits.push_back(bits_str[i] == '1');
    }

    // Prima cerinta - O(n)

    {
        int curent = 0;
        for(int i = 0; i < k; ++i)
            curent = (curent << 1) + bits[i]; 

        int max_curent = curent;

        for(int i = k; i < bits.size(); ++i) {
            curent = ((curent & ((1 << (k - 1)) - 1)) << 1) + bits[i];
            max_curent = std::max(max_curent, curent);
        }

        fout << max_curent << '\n';
    }

    // A doua cerinta

    {
        // best[i] - capatul minim pentru care se formeaza un sir crescator de lungime [i]
        int n = bits.size();
        std::vector<int> best(n + 2, INF);
        best[0] = -INF;

        // Vector de pq pentru a stoca update-urile in ordine descrescatoare
        // dar accesate cu top in ordine crescatoare

        using pii = std::pair<int, int>;

        std::vector<std::vector<pii>> updates(n + 2);

        for(int P = 1; P <= n + 1; ++P) {
            // Verificam daca avem update-uri
            for (std::pair<int, int> update : updates[P]) {
                best[update.first] = std::min(
                    best[update.first],
                    update.second
                );
            }

            int nrj = 0;
            int start = P - 1;

            // Formam fiecare numar folosind maxim k biti
            // pornind de la bitul current (start + j - 1)
            for(int j = 1; j <= k && P + j <= n + 1; ++j) {
                nrj = (nrj << 1) + bits[start + j - 1];
                
                // Cautam pozitia pentru care
                // best[L] < nrj si best[L + 1] > nrj
                // astfel nrj poate fi un candidat pentru
                // capatul minim al unui sir de lungime L + 1
                int pos = std::upper_bound(best.begin(), best.end(), nrj) - best.begin();
                
                // Folosim update-uri viiotare (delayed)
                // pentru ca daca am face update-ul cum gasim numarul
                // ar fi riscul de a folosi aceiasi biti pentru
                // a forma al doilea numar
                if(pos - 1 >= 0 && pos <= n + 1 && best[pos - 1] < nrj) {
                    updates[start + j + 1].push_back( { pos, nrj } );
                }
            }
        }

        int result_index = n;
        while(best[result_index] == INF && result_index > 0) {
            //fout << result_index << ' ' << best[result_index] << '\n';
            --result_index;
        }
            
        fout << result_index;
    }

    return 0;
}