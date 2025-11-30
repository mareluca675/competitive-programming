#include <bits/stdc++.h>

// BFS in fiecare din fiecare nod
// si calculam 
// 1. Lungimea minima din ciclu care ne duce inapoi
// 2. Distanta pana la A
// 3. Distanta pana la B
// + BFS din S

struct distante {
    int ciclu = INT_MAX;
    int distA = -1;
    int distB = -1;
    int ultim = -1;
};

int s, a, b, c, n, m;

const int NMAX = 5005;
std::vector<distante> veri;
std::vector<int> graph[NMAX];
std::vector<int> graphInvers[NMAX];

void BFS_D(int start) {
    std::queue<int> q;
    std::vector<int> dist(n + 1, -1);

    q.push(start);
    dist[start] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int neighbour : graph[node]) {
            if(dist[neighbour] == -1) {
                dist[neighbour] = dist[node] + 1;

                if(neighbour == a) {
                    veri[start].distA = dist[neighbour];
                }
                else if(neighbour == b) {
                    veri[start].distB = dist[neighbour];
                }

                q.push(neighbour);
            }
            else if(neighbour == start) {
                veri[start].ultim = node;
                veri[start].ciclu = std::min(dist[node] + 1, veri[start].ciclu);
            }
        }
    }
}

std::vector<int> BFS(int start) {
    std::queue<int> q;
    q.push(start);

    std::vector<int> dist(n + 1, -1);
    dist[start] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int neighbour : graph[node]) {
            if(dist[neighbour] == -1) {
                dist[neighbour] = dist[node] + 1;
                q.push(neighbour);
            }
        }
    }

    return dist;
}

std::vector<int> BFS_Invers(int start) {
    std::queue<int> q;
    q.push(start);

    std::vector<int> dist(n + 1, -1);
    dist[start] = 0;

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int neighbour : graphInvers[node]) {
            if(dist[neighbour] == -1) {
                dist[neighbour] = dist[node] + 1;
                q.push(neighbour);
            }
        }
    }

    return dist;
}

void reconstruire(int start, int end, std::vector<int>& dist1, std::vector<int>& dist2) {
    std::vector<int> v;
    std::queue<int> q;
    v.push_back(start);
    q.push(start);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int neighbour : graph[node]) {
            if(neighbour == end) {
                break;
            }
            else if(dist1[neighbour] + dist2[neighbour] == dist1[end]) {
                v.push_back(neighbour);
                q.push(neighbour);
                break;
            }
        }
    }

    for(auto num : v)
        std::cout << num << ' ';
}

void reconstruire_ciclu(int start, std::vector<int>& dist1, std::vector<int>& dist2) {
    std::vector<int> v;
    std::queue<int> q;
    v.push_back(start);
    q.push(start);

    while(!q.empty()) {
        int node = q.front();
        q.pop();

        for(int neighbour : graph[node]) {
            if(neighbour == start) {
                for(auto num : v) {
                    std::cout << num << ' ';
                }
                return;
            }

            if(veri[neighbour].ciclu != INT_MAX) {
                v.push_back(neighbour);
                q.push(neighbour);
                break;
            }
        }
    }
}

int main() {
    std::freopen("veri.in", "r", stdin);
    std::freopen("veri.out", "w", stdout);
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    std::cin >> c;
    std::cin >> n >> m;
    std::cin >> s >> a >> b;

    for(int i = 1; i <= m; ++i) {
        int x, y;
        std::cin >> x >> y;
        graph[x].push_back(y);
        graphInvers[y].push_back(x);
    }

    veri.resize(n + 1);

    if(c == 1) {
        int t = INT_MAX;
        std::vector<int> distS = BFS(s);

        for(int i = 1; i <= n; ++i) {
            BFS_D(i);
            
            if(i == a) {
                veri[i].distA = 0;
            }
            else if (i == b) {
                veri[i].distB = 0;
            }

            if(distS[i] != -1 && veri[i].ciclu != INT_MAX && veri[i].distA != -1 && veri[i].distB != -1) {
                t = std::min( {
                        std::max(
                            distS[i] + veri[i].ciclu + veri[i].distA,
                            distS[i] + veri[i].ciclu + veri[i].distB
                        ),
                    t
                } );
            }
        }

        std::cout << t;
    }
    else {
        int t = INT_MAX, nodCiclu;
        std::vector<int> distS = BFS(s);

        for(int i = 1; i <= n; ++i) {
            BFS_D(i);

            if(i == a) {
                veri[i].distA = 0;
            }
            else if (i == b) {
                veri[i].distB = 0;
            }
            
            if(distS[i] != -1 && veri[i].ciclu != INT_MAX && veri[i].distA != -1 && veri[i].distB != -1) {
                int tt = std::max(distS[i] + veri[i].ciclu + veri[i].distA, distS[i] + veri[i].ciclu + veri[i].distB);
                if(t >= tt) {
                    t = tt;
                    nodCiclu = i;
                }
            }
        }

        std::cout << distS[nodCiclu] + veri[nodCiclu].ciclu << '\n';

        std::vector<int> distA = BFS_Invers(a);
        std::vector<int> distB = BFS_Invers(b);
        std::vector<int> distCI = BFS_Invers(nodCiclu);
        std::vector<int> distC = BFS(nodCiclu);

        if(s != nodCiclu)
            reconstruire(s, nodCiclu, distS, distCI);
        reconstruire_ciclu(nodCiclu, distC, distCI);
        std::cout << nodCiclu;

        std::cout << '\n';

        std::cout << veri[nodCiclu].distA << '\n';

        if(a != nodCiclu)
            reconstruire(nodCiclu, a, distC, distA);
        std::cout << a;

        std::cout << '\n';

        
        std::cout << veri[nodCiclu].distB << '\n';

        if(b != nodCiclu)
            reconstruire(nodCiclu, b, distC, distB);
        std::cout << b;
    }

    return 0;
}