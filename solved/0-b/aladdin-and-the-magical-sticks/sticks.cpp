#include <cstdio>

#define MAXN 5000

double H[MAXN + 1];
int n;
int c1, c2;  // count of objects of each type
int w1, w2;  // weights of all objects from each type

void prepare()
{
    for (int i = 1; i <= MAXN; ++i)
        H[i] = H[i - 1] + (1.0 / i);
}

double solve()
{
    // average weight of all objects
    double avg = w1 + w2;
    avg /= n;

    // expected number of sticks to choose (if all were of type 2)
    double es = H[n] * n;

    // expected weight (if all sticks were of type 2)
    double ew = avg * es;

    if (c1 > 0) {
        // excess in the expected number from choosing sticks of type 1
        double ex = (es / n - 1) * c1;

        // average weight of sticks of type 1
        double a1 = w1;
        a1 /= c1;

        ew -= ex * a1;
    }

    return ew;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        c1 = c2 = w1 = w2 = 0;
        int a, b;
        for (int i = 0; i < n; ++i) {
            scanf("%d%d", &a, &b);
            if (b == 1) ++c1, w1 += a;
            else ++c2, w2 += a;
        }

        printf("Case %d: %.8lf\n", ++ncase, solve());
    }

    return 0;
}
