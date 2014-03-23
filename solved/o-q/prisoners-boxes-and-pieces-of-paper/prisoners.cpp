#include <cstdio>


#define MAXN 1000


double H[MAXN + 1];

int n;

double p;  // probability
double e;  // expected number of games


void prepare()
{
    for (int i = 1; i <= MAXN; ++i)
        H[i] = H[i - 1] + 1.0/i;
}

void solve()
{
    p = 1 - H[n] + H[n/2];
    e = 1 / p;
}

int main()
{
    prepare();

    int N;
    scanf("%d", &N);

    int ncase = 0;
    while (N--) {
        scanf("%d", &n);
        solve();
        printf("Case #%d: %.8lf %.8lf\n", ++ncase, p, e);
    }

    return 0;
}
