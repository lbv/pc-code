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
            for (j = i*i, J=j>>1; j <= n; j+=i+i, J+=i)
                comp[J] = 1;
    primes[0] = 2;
    nprimes = 1;
    for (i=3, I=1; i <= n; i+=2, I++)
        if (!comp[I])
            primes[nprimes++] = i;
}

int isPrime(int n) {
    if (n == 2) return 1;
    if (n%2 == 0) return 0;
    return !comp[n>>1];
}

void precalculate() {
    primeSieve(NPRIMES);
}

int solution(int n) {
    int half, ways, i;

    half = n/2;
    ways = 0;

    for (i = 0; i < nprimes; i++) {
        int prime = primes[i];
        if (prime > half) break;
        if (isPrime(n - prime)) ways++;
    }
    return ways;
}

int main(void) {
    int T, ncase;

    precalculate();

    scanf("%d", &T);

    for (ncase = 1; ncase <= T; ncase++) {
        int N;
        scanf("%d", &N);

        printf("Case %d: %d\n", ncase, solution(N));
    }
    return 0;
}
