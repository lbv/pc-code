#include <cstdio>
#include <vector>
using namespace std;


typedef vector<int> IV;


int N;
int inc, dec;
IV hs, ws;


void solve()
{
    if (N == 0) {
        inc = dec = 0;
        return;
    }

    IV is(N);
    IV ds(N);

    inc = dec = ds[0] = is[0] = ws[0];

    for (int i = 1; i < N; ++i) {
        int best_inc = 0;
        int best_dec = 0;

        for (int j = 0; j < i; ++j) {
            if (hs[i] > hs[j] && is[j] > best_inc) best_inc = is[j];
            if (hs[i] < hs[j] && ds[j] > best_dec) best_dec = ds[j];
        }

        is[i] = best_inc + ws[i];
        ds[i] = best_dec + ws[i];

        if (is[i] > inc) inc = is[i];
        if (ds[i] > dec) dec = ds[i];
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &N);

        hs = IV(N);
        ws = IV(N);
        for (int i = 0; i < N; ++i) scanf("%d", &hs[i]);
        for (int i = 0; i < N; ++i) scanf("%d", &ws[i]);

        solve();

        printf("Case %d. ", ++ncase);

        if (inc >= dec)
            printf("Increasing (%d). Decreasing (%d).\n", inc, dec);
        else
            printf("Decreasing (%d). Increasing (%d).\n", dec, inc);
    }

    return 0;
}
