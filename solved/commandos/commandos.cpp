#include <algorithm>
#include <cstdio>
using namespace std;

#define MAXN 100

#define INF 110

int g[MAXN][MAXN];
int N;

void init_graph()
{
    for (int i = 0; i < N; i++)
        for (int j = 0; j < N; j++)
            g[i][j] = i == j ? 0 : INF;
}

void floyd()
{
    for (int k = 0; k < N; k++)
        for(int i = 0; i < N; i++)
            for (int j = 0; j < N; j++) {
                int t = g[i][k] + g[k][j];
                if (t < g[i][j]) g[i][j] = t;
            }
}

int mintime(int s, int d)
{
    floyd();
    int time = 0;
    for (int i = 0; i < N; i++)
        time = max(time, g[s][i] + g[i][d]);
    return time;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int R;
        scanf("%d%d", &N, &R);

        init_graph();

        while (R--) {
            int u, v;
            scanf("%d%d", &u, &v);
            g[u][v] = 1;
            g[v][u] = 1;
        }

        int s, d;
        scanf("%d%d", &s, &d);

        printf("Case %d: %d\n", ncase++, mintime(s, d));
    }

    return 0;
}
