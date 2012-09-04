#include <cstdio>
#include <cstring>


#define MAXM 100000
#define MAXN 100

#define Zero(v) memset((v), 0, sizeof(v))


int n, m;
int A[MAXN], C[MAXN];

// q has all quantities of money that can be made with the coins
int q[MAXM + 1];
int nq;

// r[i] is true if i money can be made with the coins
bool r[MAXM + 1];

// u[i] has the number of coins from the current denomination used to make i
int u[MAXM + 1];


void solve()
{
    nq = 1;
    q[0] = 0;

    Zero(r);
    r[0] = true;

    for (int i = 0; i < n; ++i) {
        Zero(u);

        for (int j = 0; j < nq; ++j) {
            int v = q[j] + A[i];

            if (v <= m && !r[v] && u[q[j]] < C[i]) {
                q[nq++] = v;
                r[v] = true;
                u[v] = u[q[j]] + 1;
            }
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &m);

        for (int i = 0; i < n; ++i) scanf("%d", &A[i]);
        for (int i = 0; i < n; ++i) scanf("%d", &C[i]);

        solve();
        printf("Case %d: %d\n", ++ncase, nq - 1);
    }

    return 0;
}
