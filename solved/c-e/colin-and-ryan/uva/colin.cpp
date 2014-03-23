#include <cmath>
#include <cstdio>
#include <vector>
using namespace std;

typedef unsigned int u32;
typedef vector<u32> UV;

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 1;
    while (T--) {
        u32 P, L;
        scanf("%u%u", &P, &L);
        printf ("Case #%d:", ncase++);

        if (P == L) {
            puts(" 0");
            continue;
        }

        u32 N = P - L;
        UV divs;
        u32 sn = sqrt(N);

        for (u32 i = 1; i <= sn; i++) {
            if (N % i != 0) continue;
            if (i > L) printf(" %u", i);
            u32 odiv = N/i;
            if (i != odiv)
                divs.push_back(odiv);
        }
        for (int i = divs.size() - 1; i >= 0; i--)
            if (divs[i] > L)
                printf(" %u", divs[i]);
        putchar('\n');
    }

    return 0;
}
