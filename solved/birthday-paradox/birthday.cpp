#include <cstdio>

#define Sc(t,v) static_cast<t>(v)

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int n;
        scanf("%d", &n);

        double p = 1.0;
        int people = 0;

        while (p > 0.5) {
            ++people;
            p *= 1.0 - Sc(double, people) / n;
        }

        printf("Case %d: %d\n", ++ncase, people);
    }

    return 0;
}
