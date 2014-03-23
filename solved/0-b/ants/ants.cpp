#include <algorithm>
#include <cstdio>
using namespace std;


int l, n;


int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d%d", &l, &n);
        int lo = 0, hi = 0;
        while (n--) {
            int x;
            scanf("%d", &x);

            hi = max(hi, max(x, l - x));
            lo = max(lo, min(x, l - x));
        }
        printf("%d %d\n", lo, hi);
    }

    return 0;
}
