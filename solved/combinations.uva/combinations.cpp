#include <cstdio>

typedef long long i64;

// Binomial coefficients
#define BCSIZE 100
i64 bc[BCSIZE + 1][BCSIZE + 1];
void choose_table() {
    for (int n = 1; n <= BCSIZE; n++) { bc[n][n] = 1; bc[n][1] = n; }
    for (int n = 3; n <= BCSIZE; n++)
        for (int k = 2; k < n; k++)
            bc[n][k] = (bc[n-1][k-1] + bc[n-1][k]);
}

int N, M;

int main()
{
    choose_table();

    while (true) {
        scanf("%d%d", &N, &M);
        if (N == 0 && M == 0) break;

        printf("%d things taken %d at a time is %lld exactly.\n",
               N, M, bc[N][M]);
    }

    return 0;
}
