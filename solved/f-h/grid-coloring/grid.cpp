#include <algorithm>
#include <cstdio>
#include <set>
using namespace std;


#define MOD  1000000000LL
#define MAXB 500


typedef long long      i64;
typedef pair<int, int> II;


int M, N, K, B;

II blocked[MAXB];

set<II> bset;


template <typename T>
T mod_pow(T _b, T e, T m) {
    T res = 1;
    for (T b=_b; e; e >>= 1, b = b*b%m) if (e & 1) res = res*b%m;
    return res;
}

int solve()
{
    // number of cells that can be painted with K colors
    i64 c0 = N;
    // number of cells that can be painted with K-1 colors
    i64 c1 = 1LL * (M - 1) * N;

    sort(blocked, blocked + B);
    for (int i = 0; i < B; ++i) {
        II &b = blocked[i];

        if (b.first == 1 ||
            bset.find(II(b.first - 1, b.second)) != bset.end())
            --c0;
        else
            --c1;

        if (b.first < M)
            ++c0, --c1;
    }

    i64 ans = mod_pow(1LL * K, c0, MOD) * mod_pow(1LL * K-1, c1, MOD) % MOD;
    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d%d%d", &M, &N, &K, &B);
        bset.clear();
        for (int i = 0; i < B; ++i) {
            int x, y;
            scanf("%d%d", &x, &y);
            blocked[i] = II(x, y);
            bset.insert(II(x, y));
        }

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
