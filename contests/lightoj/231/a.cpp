#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


typedef vector<double> DV;


int N;
bool vis[MAXN];
DV memo[MAXN];

const double P = 1.0/12.0;


DV get_simplified(int idx)
{
    if (vis[idx]) return memo[idx];

    DV v(N);
    for (int i = 1; i <= 6; ++i) {
        if (idx + i == N)
            v[0] += P;
        else if (idx + i < N)
            v[idx + i] += P, v[0] += P;
        else
            v[idx] += P, v[0] += P;

        if (idx - i == N)
            v[0] += P;
        else if (idx - i > 0)
            v[idx - i] += P, v[0] += P;
        else
            v[idx] += P, v[0] += P;
    }

    for (int i = N - 1; i > idx; --i) {
        if (v[i] == 0.0) continue;
        DV x = get_simplified(i);

        for (int j = 0; j < N; ++j)
            v[j] += v[i]*x[j];
    }

    double f = 1.0 / (1.0 - v[idx]);
    v[idx] = 0.0;
    for (int i = 0; i < idx; ++i)
        v[i] *= f;

    vis[idx] = true;
    return memo[idx] = v;
}

double solve()
{
    if (N == 1) return 0.0;

    Zero(vis);
    DV val = get_simplified(1);
    return val[0];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);
        printf("Case %d: %.5lf\n", ++ncase, solve());
    }

    return 0;
}
