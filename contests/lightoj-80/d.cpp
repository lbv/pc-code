#include <cmath>
#include <cstdio>

typedef unsigned long long u64;

#define Sc(t,v) static_cast<t>(v)
#define MAXN 1000000

double logs[MAXN + 1];

void prepare()
{
    logs[0] = 0;
    for (int i = 1; i <= MAXN; ++i)
        logs[i] = logs[i-1] + log10(i);
}

// Calculates the highest exponent of prime p that divides n!
int powDivFact(int n, int p) {
    int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int N;
        scanf("%d", &N);

        printf("Case %d: %d %d\n", ++ncase, Sc(int, logs[N]) + 1, powDivFact(N, 5));
    }

    return 0;
}
