#include <cmath>
#include <cstdio>


#define MAXPSOL 50


#define IsComp(n)  (_c[n>>6]&(1<<((n>>1)&31)))
#define SetComp(n) _c[n>>6]|=(1<<((n>>1)&31))
const int MAXP   = 10000000;  // 10^7
const int SQRP   =     3163;  // sqrt(MAX)
const int MAX_NP =   781731;  // 1.26 * MAXP/log(MAXP)
int _c[(MAXP>>6)+1];
int  primes[MAX_NP];
int  nprimes;
bool is_p4[MAX_NP];   // is_p4[i]: true iff primes[i] is 4k+3 for some k
int  p4s[MAX_NP];
int  np4s;

void prime_sieve() {
    for (int i = 3; i <= SQRP; i += 2)
        if (!IsComp(i)) for (int j = i*i; j <= MAXP; j+=i+i) SetComp(j);
    primes[nprimes++] = 2;
    for (int i=3; i <= MAXP; i+=2)
        if (!IsComp(i)) {
            if ((i - 3) % 4 == 0) {
                is_p4[nprimes] = true;
                p4s[np4s++] = i;
            }
            primes[nprimes++] = i;
        }
}

// Calculates the highest exponent of prime p that divides n!
int pow_div_fact(int n, int p) {
    int sd = 0; for (int N=n; N; N /= p) sd += N % p; return (n-sd)/(p-1);
}


int  N;
bool is_fact;

int psol[MAXPSOL];
int npsol;


bool solve_n()
{
    npsol = 0;
    int sn = sqrt(N);
    for (int i = 0; i < nprimes; ++i) {
        int &p = primes[i];
        if (p > sn) break;
        if (N % p != 0) continue;

        int e = 0;
        while (N % p == 0) ++e, N /= p;

        if (is_p4[i] && e % 2 != 0) return false;
        sn = sqrt(N);
    }
    if (N > 1 && (N - 3) % 4 == 0) return false;
    return true;
}

bool solve_fact()
{
    npsol = 0;
    for (int i = 0; i < np4s; ++i) {
        int &p = p4s[i];
        if (p > N) break;
        int e = pow_div_fact(N, p);

        if (e % 2 == 0) continue;
        psol[npsol++] = p;
        if (npsol == MAXPSOL) return false;
    }
    return npsol == 0;
}

bool solve()
{
    if (is_fact) return solve_fact();
    return solve_n();
}

int main()
{
    prime_sieve();

    bool first = true;
    while (true) {
        char c;
        if (scanf("%d%c", &N, &c) != 2) break;
        is_fact = c == '!';

        if (first) first = false;
        else       putchar('\n');

        if (solve())
            puts("He might be honest.");
        else {
            puts("He is a liar.");
            if (npsol > 0) {
                printf("%d", psol[0]);
                for (int i = 1; i < npsol; ++i)
                    printf(" %d", psol[i]);
                putchar('\n');
            }
        }
    }

    return 0;
}
