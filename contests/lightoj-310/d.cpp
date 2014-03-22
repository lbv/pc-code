#include <cmath>
#include <cstdio>


#define EPS (1e-9)


const double pi = acos(-1);


int r, x;


int solve()
{
    int q = x / (r*pi) + EPS;
    return q * 2 * r;
}

int main()
{
    int n;
    scanf("%d", &n);

    while (n--) {
        scanf("%d%d", &r, &x);
        printf("%d\n", solve());
    }

    return 0;
}
