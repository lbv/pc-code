#include <algorithm>
#include <cstdio>
using namespace std;


typedef unsigned int u32;


u32 L, H;
u32 best, len;


u32 seq(u32 n)
{
    int l = 0;
    do {
        if (n % 2 == 0) n /= 2;
        else n = 3*n + 1;

        ++l;
    } while (n != 1);

    return l;
}

void solve()
{
    len = 0;
    for (u32 i = L; i <= H; ++i) {
        u32 res = seq(i);
        if (res > len) {
            best = i;
            len = res;
        }
    }
}

int main()
{
    while (true) {
        scanf("%u%u", &L, &H);
        if (L == 0 && H == 0) break;
        if (L > H) swap(L, H);

        solve();

        printf(
"Between %u and %u, %u generates the longest sequence of %u values.\n",
L, H, best, len);
    }

    return 0;
}
