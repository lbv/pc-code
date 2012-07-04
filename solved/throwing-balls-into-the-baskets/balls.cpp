#include <cstdio>

int N, K;
double P;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%*d%d%lf", &N, &K, &P);

        printf("Case %d: %.8lf\n", ++ncase, P*K*N);
    }

    return 0;
}
