#include <cstdio>
#include <cstring>


#define MAXM 10000

#define Zero(v) memset((v), 0, sizeof(v))


typedef long long i64;


int A, B, C, N, M;

// cmod[m]: count of occurrences when the modulo of the sequence is m
int cmod[MAXM];

i64 ans;
int m;


void process(int num)
{
    m = (m + num) % M;
    ans += cmod[m];
    ++cmod[m];
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d%d", &A, &B, &C, &M, &N);

        Zero(cmod);
        cmod[0] = 1;

        ans = 0;
        m = 0;

        int X = A;
        process(X);

        for (int i = 1; i < N; ++i) {
            X = (X*B + C) % M + 1;
            process(X);
        }

        printf("Case %d: %lld\n", ++ncase, ans);
    }

    return 0;
}
