#include <cstdio>


#define MAXM 100000


typedef unsigned int u32;


u32 P[MAXM + 1];
int M;


void prepare()
{
    for (int i = 3; i <= MAXM; ++i)
        P[i] = P[i - 1] + (i-2)*2;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &M);
        printf("Case %d: %u\n", ++ncase, P[M]);
    }

    return 0;
}
