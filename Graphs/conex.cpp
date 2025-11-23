#include <bits/stdc++.h>

std::ifstream fin("ctc.in");
std::ofstream fout("ctc.out");

std::vector<std::vector<int>> adj;
std::vector<int> disc, low;
std::stack<int> st;
std::vector<bool> onStack;
std::vector<std::vector<int>> sccs;

void DFS(int start) {
    static int time = 0;
    disc[start] = low[start] = ++time;
    st.push(start);
    onStack[start] = true;

    for(int neighbour : adj[start]) {
        if(disc[neighbour] == -1) {
            DFS(neighbour);

            low[start] = std::min(low[start], low[neighbour]);
        }
        else if(onStack[neighbour]) {
            low[start] = std::min(low[start], low[neighbour]);
        }
    }

    if(low[start] == disc[start]) {
        std::vector<int> scc;
        int top;

        do {
            top = st.top();
            st.pop();
            onStack[top] = false;
            scc.push_back(top);
        } while(top != start);

        sccs.push_back(scc);
    }
}

int main() {
    int n, m;
    fin >> n >> m;

    adj.resize(n + 1);
    disc.resize(n + 1, -1);
    low.resize(n + 1, -1);
    onStack.resize(n + 1);

    for(int i = 1; i <= m; ++i) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
    }

    for(int i = 1; i <= n; ++i) {
        if(disc[i] == -1) {
            DFS(i);
        }
    }

    fout << sccs.size() << '\n';
    for(std::vector<int> i : sccs) {
        for(int j : i) {
            fout << j << ' ';
        }
        fout << '\n';
    }

    return 0;
}