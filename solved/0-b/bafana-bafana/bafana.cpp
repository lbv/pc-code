#include <cstdio>

int N, K, P;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d", &N, &K, &P);

        printf("Case %d: %d\n", ++ncase, ((K-1) + P) % N + 1);
    }

    return 0;
}
