#include <algorithm>
#include <cstdio>
#include <cstdlib>
using namespace std;

#define MAXR 500

int ss[MAXR];
int r;

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%d", &r);

        for (int i = 0; i < r; ++i)
            scanf("%d", &ss[i]);
        sort(ss, ss + r);

        int median = ss[r/2];

        int ans = 0;
        for (int i = 0; i < r; ++i)
            ans += abs(ss[i] - median);

        printf("%d\n", ans);
    }

    return 0;
}
