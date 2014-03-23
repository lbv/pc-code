#include <cstdio>
#include <cstring>
#include <string>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))


struct State {
    string path;
    bool vis[5][5];
    State() { Zero(vis); }
};

int g[5][5] = {
    { 0, 1, 1, 0, 1 },
    { 1, 0, 1, 0, 1 },
    { 1, 1, 0, 1, 1 },
    { 0, 0, 1, 0, 1 },
    { 1, 1, 1, 1, 1 }
};


void dfs(int u, int v, State s)
{
    s.vis[u][v] = s.vis[v][u] = true;
    s.path.push_back('1' + v);

    if (s.path.size() == 9)
        printf("%s\n", s.path.c_str());

    for (int i = 0; i < 5; ++i) {
        if (i == v || !g[v][i] || s.vis[v][i]) continue;

        dfs(v, i, s);
    }
}

int main()
{
    dfs(0, 0, State());

    return 0;
}
