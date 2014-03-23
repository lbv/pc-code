#include <cmath>
#include <cstdio>


int x, y;


int solve(int s)
{
    if (s == 0) return 0;

    int sr = sqrt(s);
    if (sr*sr >= s) return 2*sr - 1;
    if (sr*(sr + 1) >= s) return 2*sr;
    return 2*sr + 1;
}

int main()
{
    int n;
    scanf("%d", &n);

    while (n--) {
        scanf("%d%d", &x, &y);
        printf("%d\n", solve(y - x));
    }

    return 0;
}
