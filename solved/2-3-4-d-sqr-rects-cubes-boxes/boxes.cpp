#include <cstdio>


#define MAXN 100


typedef unsigned long long u64;


u64 R[5][MAXN + 1];
u64 S[5][MAXN + 1];

// A[d][i] will have the number of subdivisions of a shape of dimension d,
// with a maximum side i
u64 A[5][MAXN + 1];

int N;


u64 upow(u64 b, int e)
{
    u64 res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}

void prepare()
{
    for (int d = 2; d <= 4; ++d)
        for (int i = 1; i <= MAXN; ++i)
            S[d][i] = S[d][i - 1] + upow(i, d);

    for (int i = 1; i <= MAXN; ++i)
        A[1][i] = A[1][i - 1] + i;

    for (int d = 2; d <= 4; ++d)
        for (int i = 1; i <= MAXN; ++i) {
            A[d][i] = A[d - 1][i] * A[1][i];
            R[d][i] = A[d][i] - S[d][i];
        }
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &N) != 1) break;

        printf("%llu %llu %llu %llu %llu %llu\n", S[2][N], R[2][N],
               S[3][N], R[3][N], S[4][N], R[4][N]);
    }

    return 0;
}
