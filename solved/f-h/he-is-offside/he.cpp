#include <algorithm>
#include <cstdio>
using namespace std;

#define INF  (10000 + 10)
#define MAXP 11

// defending players
int p[MAXP];

int main()
{
    while (true) {
        int A, D;
        scanf("%d%d", &A, &D);
        if (A == 0 && D == 0) break;

        int at = INF;  // attacker closest to goal
        while (A--) {
            int B; scanf("%d", &B);
            if (B < at) at = B;
        }

        for (int i = 0; i < D; i++)
            scanf("%d", &p[i]);

        sort(p, p + D);

        if (at < p[1])
            printf("Y\n");
        else
            printf("N\n");
    }
    return 0;
}
