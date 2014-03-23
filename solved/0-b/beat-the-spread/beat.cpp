#include <algorithm>
#include <cstdio>
using namespace std;

int n, s, d;
int a, b;

int main()
{
    scanf("%d", &n);

    while (n--) {
        scanf("%d%d", &s, &d);

        a = (s + d) / 2;
        b = s - a;

        if ((s + d) % 2 != 0 || a < 0 || b < 0)
            puts("impossible");
        else
            printf("%d %d\n", max(a, b), min(a, b));
    }

    return 0;
}
