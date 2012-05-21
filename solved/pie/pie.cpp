#include <algorithm>
#include <cmath>
#include <cstdio>
#include <functional>
using namespace std;

#define MAXN 10000

const double PI = 2 * acos(0.0);
const double E = 0.0005;

int N, F, P;
double vol[MAXN];

// Number of people that can be fed with pieces of volume v
int npeople(double v)
{
    int n = 0;
    for (int i = 0; i < N; i++) {
        if (vol[i] < v) break;
        n += floor(vol[i]/v);
    }
    return n;
}

double solve()
{
    double min = vol[N-1] / P;
    double max = vol[0];

    while (max - min > E) {
        double mid = (max+min)/2;
        int x = npeople(mid);

        if (x >= P) min = mid;
        else max = mid;
    }
    return min;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &N, &F);
        P = F + 1;

        for (int i = 0; i < N; i++) {
            int r; scanf("%d", &r);
            vol[i] = PI * r * r;
        }

        sort(vol, vol + N, greater<double>());

        printf("%.5lf\n", solve());
    }

    return 0;
}
