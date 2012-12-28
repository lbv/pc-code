#include <algorithm>
#include <cstdio>
using namespace std;


int m, n;


int solve()
{
    if (m == 1) return n;
    if (m == 2) return n/4 * 4 + min(2, n % 4)*2;

    int prod = m*n;
    int res = prod/2;
    if (prod & 1) ++res;
    return res;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &m, &n);
        if (m > n) swap(m, n);
        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
