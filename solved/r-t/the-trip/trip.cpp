#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

#define MAXN 1000
#define EPS  (1e-6)

#define Sc(t,v) static_cast<t>(v)

int money[MAXN];
int n;

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        double sum = 0;
        for (int i = 0; i < n; ++i) {
            double x;
            scanf("%lf", &x);
            x *= 100.0;
            x += EPS;    // ugly, but...
            money[i] = Sc(int, x);
            sum += money[i];
        }

        int avg = Sc(int, round(sum/n));
        int below = 0;  // sum of money from people below avg
        int above = 0;  // same, but for people above avg

        for (int i = 0; i < n; ++i) {
            if (money[i] < avg)
                below += avg - money[i];
            else if (money[i] > avg)
                above += money[i] - avg;
        }

        double ans = 1.0*min(above, below) / 100.0 + EPS;

        printf("$%.2lf\n", ans);
    }

    return 0;
}
