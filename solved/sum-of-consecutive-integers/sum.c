#include <math.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

#define NPRIMES 10000001
#define COMPSIZE ((NPRIMES+1)/2)

int primes[1000000];
int nprimes;
int comp[COMPSIZE];

void primeSieve(int n) {
    int sqrn;
    int i, I, j, J, idx;

    sqrn = (int) sqrt(n);
    memset(comp, 0, COMPSIZE);

    for (i=3, I=1; i <= sqrn; i+=2, I++)
        if (!comp[I])
            for (j = i*i, J=(j-1)/2; j <= n; j+=i+i, J+=i)
                comp[J] = 1;
    primes[0] = 2;
    nprimes = 1;
    for (i=3, I=1; i <= n; i+=2, I++)
        if (!comp[I])
            primes[nprimes++] = i;
}

void precalculate() {
    primeSieve(NPRIMES);
}

int solution(int64_t n) {
    int ways, sqrn, i;

    ways = 1;
    while (n % 2 == 0) n /= 2;
    sqrn = (int) sqrt(n);
    for (i = 1; i < nprimes; i++) {
        int prime = primes[i];
        if (prime > sqrn) break;
        if (n % prime != 0) continue;
        int exp = 0;
        while (n % prime == 0) { n /= prime; exp++; }
        ways *= 1 + exp;
    }
    if (n > 1) ways *= 2;
    return ways - 1;
}

int main(void) {
    int T, ncase;

    precalculate();

    scanf("%d", &T);

    for (ncase = 1; ncase <= T; ncase++) {
        int64_t N;
        scanf("%lld", &N);

        printf("Case %d: %d\n", ncase, solution(N));
    }
    return 0;
}
