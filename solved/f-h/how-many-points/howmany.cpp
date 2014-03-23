#include <cstdio>
#include <cstdlib>

typedef long long i64;

i64 gcd(i64 a, i64 b) { for (i64 c = a%b; c; a=b,b=c,c=a%b); return b; }

int main()
{
    int T = 0;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        i64 ax, ay, bx, by;
        scanf("%lld%lld%lld%lld", &ax, &ay, &bx, &by);

        i64 lp;  // lattice points

        if (ax == bx) lp = llabs(ay-by)+1;
        else lp = gcd(llabs(ay-by), llabs(ax-bx)) + 1;

        printf("Case %d: %lld\n", ncase++, lp);
    }

    return 0;
}
