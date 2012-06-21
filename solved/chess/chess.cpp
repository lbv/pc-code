#include <algorithm>
#include <cstdio>
using namespace std;

int m, n;
char piece;

int solve()
{
    if (piece == 'r' || piece == 'Q')
        return min(m, n);
    if (piece == 'K')
        return ((m + 1) / 2) * ((n + 1) / 2);

    // A knight, the trickier of the pieces
    if (m > n) swap(m, n);

    if (m == 1) return n;
    if (m == 2)
        return max(2, n % 4) * 2 + (n / 4) * 4;
    return (m*n + 1) / 2;
}

int main()
{
    int T;
    scanf("%d", &T);

    while (T--) {
        scanf(" %c%d%d", &piece, &m, &n);

        printf("%d\n", solve());
    }

    return 0;
}
