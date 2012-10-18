#include <cstdio>
#include <cmath>


int n;
int sum;


int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }


int numlen(int x)
{
    if (x == 0) return 0;
    return 1 + log10(x);
}

void pchar(int t, char c)
{
    for (int i = 0; i < t; ++i)
        putchar(c);
}

void solve()
{
    bool neg = false;
    if (sum < 0) {
        neg = true;
        sum = -sum;
    }

    int g = gcd(sum, n);
    int p = sum / g;
    int q = n / g;

    if (q == 1) {
        if (neg)
            printf("- ");
        printf("%d\n", p);
        return;
    }

    int a, b, c;
    if (p > q) {
        a = p/q;
        b = p%q;
        c = q;
    }
    else {
        a = 0;
        b = p;
        c = q;
    }
    int la = numlen(a);
    int lb = numlen(b);
    int lc = numlen(c);

    int ib = (neg ? 2 : 0) + la;
    int ic = (neg ? 2 : 0) + la;
    if (lc > lb) ib += lc - lb;

    // first line
    pchar(ib, ' ');
    printf("%d\n", b);

    // second line
    if (neg)
        printf("- ");
    if (a != 0)
        printf("%d", a);
    pchar(lc, '-');
    putchar('\n');

    // third line
    pchar(ic, ' ');
    printf("%d\n", c);
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        sum = 0;
        for (int i = 0; i < n; ++i) {
            int num;
            scanf("%d", &num);
            sum += num;
        }
        printf("Case %d:\n", ++ncase);
        solve();
    }

    return 0;
}
