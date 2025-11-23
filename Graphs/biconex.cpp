#include <bits/stdc++.h>

std::ifstream fin("biconex.in");
std::ofstream fout("biconex.out");

std::vector<std::vector<int>> adj;

std::vector<int> disc;
std::vector<int> low;

std::stack<std::pair<int, int>> st;

std::vector<std::vector<int>> biconexComponents;

void extractComponent(int x, int y) {
    std::vector<int> component;
    int tx, ty;
    
    do {
        tx = st.top().first;
        ty = st.top().second;
        st.pop();
        component.push_back(tx);
        component.push_back(ty);
    } while(!(tx == x && ty == y) && !st.empty());
    
    if(!component.empty()) {
        biconexComponents.push_back(component);
    }
}

void DFS(int u, int parent, int time) {
    disc[u] = low[u] = time;
    
    for(int v : adj[u]) {
        if(v == parent) {
            continue;
        }
        
        if(disc[v] == -1) {
            st.push({u, v});
            
            DFS(v, u, time + 1);
            
            low[u] = std::min(low[u], low[v]);
            
            // Condition for an articulation point
            if(low[v] >= disc[u]) {
                extractComponent(u, v);
            }
        }
        else {
            low[u] = std::min(low[u], disc[v]);
        }
    }
}

int main() {
    int n, m;
    fin >> n >> m;

    adj.resize(n + 1);
    
    disc.resize(n + 1, -1);
    low.resize(n + 1);


    for(int i = 1; i <= m; ++i) {
        int x, y;
        fin >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    DFS(1, 0, 0);

    fout << biconexComponents.size() << "\n";
    for(auto component : biconexComponents) {
        std::sort(component.begin(), component.end());
        component.erase(std::unique(component.begin(), component.end()), component.end());
        for(int v : component) {
            fout << v << " ";
        }
        fout << "\n";
    }

    
    return 0;
}

// OFFICIAL SOLUTION

/*

#include <fstream>
#include <iostream>
#include <set>
#include <stack>
#include <vector>
#include <algorithm>

using namespace std;

const char iname[] = "biconex.in";
const char oname[] = "biconex.out";

#define MAXN  100005
#define Min(a, b)  ((a) < (b) ? (a) : (b))

vector <int> adj[MAXN], dfn, low;

vector <vector <int> > C;

stack <pair <int, int> > stk;

void read_in(vector <int>* adj, int &n)
{
    ifstream in(iname);
    int cnt_edges, x, y;

    in >> n >> cnt_edges;
    for (; cnt_edges > 0; -- cnt_edges) {
        in >> x >> y;
        adj[x].push_back(y);
        adj[y].push_back(x);
    }
    in.close();
}

void cache_bc(const int x, const int y)
{
    vector <int> con; int tx, ty;
    do {
        tx = stk.top().first, ty = stk.top().second;
        stk.pop();
        con.push_back(tx), con.push_back(ty);
    }
    while (tx != x || ty != y);
    C.push_back(con);
}

void DF(const int n, const int fn, int number)
{
    vector <int>::iterator it;

    dfn[n] = low[n] = number;
    for (it = adj[n].begin(); it != adj[n].end(); ++ it) {
        if (*it == fn)   continue ;
        if (dfn[*it] == -1) {
            stk.push( make_pair(n, *it) );
            DF(*it, n, number + 1);
            low[n] = Min(low[n], low[*it]);
            if (low[*it] >= dfn[n])
                cache_bc(n, *it);
        }
        else
            low[n] = Min(low[n], dfn[*it]);
    }
}

int main(void)
{
    int n;
    read_in(adj, n);
    dfn.resize(n + 1), dfn.assign(n + 1, -1);
    low.resize(n + 1);
    DF(1, 0, 0);

    ofstream out(oname);
    out << C.size() << "\n";
    for (size_t i = 0; i < C.size(); ++ i) {
        sort(C[i].begin(), C[i].end());
        C[i].erase(unique(C[i].begin(), C[i].end()), C[i].end());
        for (size_t j = 0; j < C[i].size(); ++ j)
            out << C[i][j] << " ";
        out << "\n";
    }
    out.close();

    return 0;
}

*/