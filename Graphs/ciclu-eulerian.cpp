#include <bits/stdc++.h>

std::ifstream fin("ciclueuler.in");
std::ofstream fout("ciclueuler.out");

const int NMAX = 100005;
const int MMAX = 500005;

std::vector<int> graph[NMAX];
bool visited[MMAX];

int n, m;

int from[MMAX], to[MMAX];

int main() {
    fin >> n >> m;

    for(int i = 1; i <= m; ++i) {
        int x, y;
        fin >> x >> y;
        graph[x].push_back(i);
        graph[y].push_back(i);
        from[i] = x;
        to[i] = y;
    }

    for(int i = 1; i <= n; ++i) {
        if(graph[i].size() % 2 != 0) {
            fout << -1;
            return 0;
        }
    }

    std::vector<int> eulerianCycle;
    std::vector<int> st;
    st.push_back(1);

    while(!st.empty()) {
        int node = st.back();

        if(!graph[node].empty()) {
            int e = graph[node].back();
            graph[node].pop_back();

            if(!visited[e]) {
                visited[e] = true;
                int nextNode = (from[e] ^ to[e] ^ node);
                st.push_back(nextNode);
            }
        }
        else {
            eulerianCycle.push_back(node);
            st.pop_back();
        }
    }

    for(int i = 0; i < eulerianCycle.size(); ++i) {
        fout << eulerianCycle[i] << " ";
    }

    return 0;
}