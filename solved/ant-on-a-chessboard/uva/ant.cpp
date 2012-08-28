#include <algorithm>
#include <cmath>
#include <cstdio>
using namespace std;

typedef long long i64;

i64 N, x, y;

void solve()
{
    i64 ring = ceil(sqrt(N));

    i64 low = (ring-1)*(ring-1);
    i64 high = ring*ring;
    i64 n = high-low;

    if (N - low <= n/2) {
        y = ring;
        x = N - low;
    }
    else {
        x = ring;
        y = high - N + 1;
    }

    if (ring & 1) swap(x, y);
}

int main()
{
    while (true) {
        scanf("%lld", &N);
        if (N == 0) break;

        solve();
        printf("%lld %lld\n", x, y);
    }

    return 0;
}
