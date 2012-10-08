#include <algorithm>
#include <cstdio>
using namespace std;


#define MAXF 50000


int F;
int xs[MAXF];
int ys[MAXF];
int X, Y;


void solve()
{
    sort(xs, xs + F);
    sort(ys, ys + F);

    int idx = (F - 1) / 2;
    X = xs[idx];
    Y = ys[idx];
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%*d%*d%d", &F);
        for (int i = 0; i < F; ++i)
            scanf("%d%d", &xs[i], &ys[i]);

        solve();
        printf("(Street: %d, Avenue: %d)\n", X, Y);
    }

    return 0;
}
