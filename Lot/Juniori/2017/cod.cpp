#include <bits/stdc++.h>

std::ifstream fin("cod2.in");
std::ofstream fout("cod2.out");

// Subsir maximal
// folosind primele [i] cifre din primul string
// si primele [j] cifre din al doilea string,
// continand primele [k] cifre din subsirul dat

const int NMAX = 256;

typedef std::vector<int> VI;
typedef std::vector<VI> VII;
typedef std::vector<VII> VIII;

int main() {
    int l1, l2, l3;
    fin >> l1 >> l2 >> l3;

    std::vector<int> s1(l1), s2(l2), s3(l3);
    VIII dp(2, VII(l2 + 1, VI(l3 + 1, 0)));
    
    for(int i = 0; i < l1; ++i) {
        fin >> s1[i];
    }

    for(int i = 0; i < l2; ++i) {
        fin >> s2[i];
    }

    for(int i = 0; i < l3; ++i) {
        fin >> s3[i];
    }

    for(int i = 1; i <= l2; ++i) {
        for(int j = 1; j <= l3; ++j) {
            if(s2[i - 1] == s3[j - 1]) {
                dp[0][i][j] = 1 + dp[0][i - 1][j - 1];
            }
            else {
                dp[0][i][j] = std::max(
                    dp[0][i - 1][j],
                    dp[0][i][j - 1]
                );
            }
        }
    }

    int bit = 1;

    for(int k = 1; k <= l1; ++k, bit ^= 1) {
        for(int i = 1; i <= l2; ++i) {
            for(int j = 1; j <= l3; ++j) {
                if(s2[i - 1] == s3[j - 1]) {
                    if(s1[k - 1] == s2[i - 1] && k - 1 <= dp[bit ^ 1][i - 1][j - 1]) {
                        dp[bit][i][j] = 1 + dp[bit ^ 1][i - 1][j - 1];
                    }
                    else if(k <= dp[bit][i - 1][j - 1]) {
                        dp[bit][i][j] = 1 + dp[bit][i - 1][j - 1];
                    }
                }
                else {
                    dp[bit][i][j] = std::max(
                        dp[bit][i - 1][j],
                        dp[bit][i][j - 1]
                    );
                }
            }
        }

        for(int i = 1; i <= l2; ++i)
            for(int j = 1; j <= l3; ++j)
                dp[bit ^ 1][i][j] = 0;
    }

    fout << dp[l1 & 1][l2][l3];
    return 0;
}