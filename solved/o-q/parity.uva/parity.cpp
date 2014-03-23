#include <algorithm>
#include <cstdio>
using namespace std;

int I;
int parity;
char bin[64];

void solve()
{
    parity = 0;
    int idx = 0;
    while (I != 0) {
        if (I & 1) ++parity;
        bin[idx++] = '0' + (I % 2);
        I /= 2;
    }
    bin[idx] = 0;

    for (int i = 0, j = idx - 1; i < j; ++i, --j)
        swap(bin[i], bin[j]);
}

int main()
{
    while (true) {
        scanf("%d", &I);
        if (I == 0) break;

        solve();
        printf("The parity of %s is %d (mod 2).\n", bin, parity);
    }

    return 0;
}
