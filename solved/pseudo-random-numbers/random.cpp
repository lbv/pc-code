#include <cstdio>
#include <cstring>


#define MAXM 10000

#define Neg(v)  memset((v), -1, sizeof(v))


int Z, I, M, L;
int last[MAXM];


int solve()
{
    Neg(last);
    for (int i = 0; true; ++i) {
        if (last[L] != -1)
            return i - last[L];
        last[L] = i;
        L = Z*L + I;
        L %= M;
    }
    return -1;
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d%d%d%d", &Z, &I, &M, &L);
        if (Z == 0 && I == 0 && M == 0 && L == 0) break;
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
