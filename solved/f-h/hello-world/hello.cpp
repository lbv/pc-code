#include <cmath>
#include <cstdio>

#define Sc(t,v) static_cast<t>(v)

int N;

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &N);
        if (N < 0) break;

        printf("Case %d: %d\n", ++ncase, Sc(int, ceil(log2(N))));
    }

    return 0;
}
