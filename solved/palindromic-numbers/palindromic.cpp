#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define MAXD 18  // Max number of digits for a number
typedef long long i64;

i64 I, J;

// npals0[i] is the number of palindromic numbers with exactly i digits,
// including numbers that start with a 0
i64 npals0[MAXD + 1];

// anpals[i] is the accumulated number of palindromic numbers with up to
// i digits
i64 anpals[MAXD + 1];

#define NPALS0(i) ((i) >= 0 ? npals0[i] : 1)
#define ANPALS(i) ((i) >= 0 ? anpals[i] : 0)

void numberToArray(i64 n, int d[MAXD], int &nd)
{
    if (n == 0) {
        nd = 1;
        d[0] = 0;
        return;
    }
    nd = static_cast<int>(log10(n)) + 1;
    for (int i = nd - 1; i >= 0; i--) {
        d[i] = n % 10;
        n /= 10;
    }
}

i64 npalindromes(int d[], int nd, bool z)
{
    if (nd == 0) return 1;
    if (nd == 1) return d[0] + 1;

    int n = z ? d[0] : d[0] - 1;
    i64 res = n * NPALS0(nd-2);
    if (d[nd-1] < d[0]) {
        int i;
        for (i = nd - 2; i >= 1; i--) {
            if (d[i] > 0) break;
            else d[i] = 9;
        }
        if (i < 1) return res;
        d[i]--;
    }
    res += npalindromes(d + 1, nd - 2, true);
    return res;
}

i64 npalindromes(i64 n)
{
    int d[MAXD];
    int nd;
    numberToArray(n, d, nd);

    return ANPALS(nd - 1) + npalindromes(d, nd, false);
}

void prepare()
{
    npals0[0] = 1;
    npals0[1] = 10;
    anpals[0] = 0;
    anpals[1] = 10;

    for (int i = 2; i <= MAXD; i++) {
        npals0[i] = 10 * npals0[i-2];
        anpals[i] = anpals[i-1] + 9 * npals0[i-2];
    }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        scanf("%lld%lld", &I, &J);
        if (I > J) swap(I, J);

        i64 pal;
        if (I == 0)
            pal = npalindromes(J);
        else
            pal = npalindromes(J) - npalindromes(I-1);
        printf("Case %d: %lld\n", ncase++, pal);
    }

    return 0;
}
