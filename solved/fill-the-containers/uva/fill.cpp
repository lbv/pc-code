#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

#define MAXN 1000
#define INF  1000000000

typedef vector<int>  IV;
typedef IV::iterator IVi;

// Accumulated capacities
IV acap;
int n, m;

// Returns the number of containers required to move all the milk, with at
// most "c" in each container
int f(int c)
{
    int ret = 0;
    IVi it = acap.begin();

    int lim = c;
    while (true) {
        if (*it > lim) return INF;
        it = upper_bound(it, acap.end(), lim);
        ++ret;
        if (it == acap.end()) return ret;
        lim = *(it - 1) + c;
    }
    return -1;
}

int solve()
{
    int min = acap[n] / m;
    int max = acap[n];

    while (true) {
        int cap = (max + min) / 2;

        int containers = f(cap);
        if (containers <= m && f(cap - 1) > m)
            return cap;

        if (containers <= m) max = cap - 1;
        else min = cap + 1;
    }
}

int main()
{
    while (true) {
        if (scanf("%d%d", &n, &m) != 2) break;

        acap = IV(n + 1);
        for (int i = 1; i <= n; ++i) {
            int c;
            scanf("%d", &c);
            acap[i] = acap[i - 1] + c;
        }

        printf("%d\n", solve());
    }

    return 0;
}
