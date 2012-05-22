#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXH 250000

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); v++)
#define Zero(v) memset(v, 0, sizeof(v))

// dpX[i] will have the maximum height of twin towers that have a difference
// of height between them equal to i. These will be managed in two arrays to
// gradually build the answer one step at a time.
int dp1[MAXH + 1];
int dp2[MAXH + 1];

int q[MAXH + 1];
int qs;
bool flg[MAXH + 1];

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        int n;
        scanf("%d", &n);

        int *cur = dp1;
        int *nxt = dp2;
        Zero(dp1);
        Zero(dp2);
        Zero(flg);

        flg[0] = true;
        q[0] = 0;
        qs = 1;
        int totalh = 0;
        int limit;

#define ADDQ(h) if(! flg[h]) { flg[h] = true; q[qs++] = h; }

        while (n--) {
            int b;  // brick height
            scanf("%d", &b);
            totalh += b;

            limit = min(MAXH, 2*MAXH - totalh);

            int h2, maxh;
            for (int i = 0, I = qs; i < I; ++i) {
                int h = q[i];

                if (cur[h] > nxt[h]) nxt[h] = cur[h];

                h2 = h + b;
                if (h2 <= limit) {
                    maxh = cur[h] + b;
                    if (maxh > nxt[h2]) nxt[h2] = maxh;
                    ADDQ(h2);
                }

                h2 = abs(h - b);
                if (h2 <= limit) {
                    maxh = max(cur[h], cur[h] + b - h);
                    if (maxh > nxt[h2]) nxt[h2] = maxh;
                    ADDQ(h2);
                }
            }
            swap(cur, nxt);
        }

        if (cur[0] <= 0)
            printf("Case %d: impossible\n", ncase++);
        else
            printf("Case %d: %d\n", ncase++, cur[0]);
    }

    return 0;
}
