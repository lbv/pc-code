#include <cmath>
#include <cstdio>

int n, k;
int lead, trail;

int digits(double x)
{
    return floor(log10(x)) + 1;
}

void shorten(double &x)
{
    int d = digits(x);
    if (d >= 4)
        x /= pow(10, d - 3);
}

void solve()
{
    int b = n;
    int e = k;

    trail = 1;
    double head = 1;
    double accu = b;

    for (b %= 1000; e; e >>= 1, b = b*b%1000) {
        if (e & 1) {
            trail = trail*b % 1000;
            head *= accu;
            shorten(head);
        }
        accu *= accu;
        shorten(accu);
    }

    shorten(head);
    lead = head;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &k);

        solve();

        printf("Case %d: %03d %03d\n", ++ncase, lead, trail);
    }

    return 0;
}
