#include <algorithm>
#include <cstdio>
using namespace std;

int M, N;

int solve()
{
    if (M > N) swap(M, N);

    if (M == 1) return N;
    if (M == 2) return 2*min(N % 4, 2) + (N/4) * 4;
    return (M*N + 1) / 2;
}

int main()
{
    while (true) {
        scanf("%d%d", &M, &N);
        if (M == 0 && N == 0) break;

        printf("%d knights may be placed on a %d row %d column board.\n",
               solve(), M, N);
    }

    return 0;
}
