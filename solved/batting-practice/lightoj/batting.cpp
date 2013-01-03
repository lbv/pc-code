#include <cmath>
#include <cstdio>
#include <cstring>


#define MAXK 50

#define Zero(v) memset((v), 0, sizeof(v))


long double p;
int k1, k2;

// sump[i] = p^0 + p^1 + ... + p^(i-1)
long double sump[MAXK + 1];
long double sumq[MAXK + 1];


long double solve()
{
    long double q = 1.0 - p;

    for (int i = 1; i <= k2; ++i) sump[i] = sump[i - 1] + pow(p, i - 1);
    for (int i = 1; i <= k1; ++i) sumq[i] = sumq[i - 1] + pow(q, i - 1);

    long double Es;  // expected value for (k2-1) consecutive successes
    long double Ef;  // expected value for (k1-1) consecutive failures

    long double Sp = sump[k2-1];
    long double Sq = sumq[k1-1];

    Es = (Sp + q*Sp*Sq) / (1.0 - p*q*Sp*Sq);
    Ef = (Sq + p*Sp*Sq) / (1.0 - p*q*Sp*Sq);

    return p*(Es + 1) + q*(Ef + 1);
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%Lf%d%d", &p, &k1, &k2);
        printf("Case %d: %Lf\n", ++ncase, solve());
    }

    return 0;
}
