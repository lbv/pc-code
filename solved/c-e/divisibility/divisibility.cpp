#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MAXK 100


bool mod[2][MAXK];
int N, K;


#define Clear(v) memset((v), 0, sizeof(mod[0]))

int m(int n)
{
    int r = n % K;
    if (r < 0) r += K;
    return r;
}

int main()
{
    int M;
    scanf("%d", &M);

    while (M--) {
        scanf("%d%d", &N, &K);

        int s;
        scanf("%d", &s);

        bool *cur = mod[0];
        bool *nxt = mod[1];

        Clear(cur);
        cur[m(s)] = true;

        for (int i = 1; i < N; ++i) {
            scanf("%d", &s);

            Clear(nxt);
            for (int j = 0; j < K; ++j)
                if (cur[j])
                    nxt[m(j + s)] = nxt[m(j - s)] = true;

            swap(cur, nxt);
        }

        if (cur[0])
            puts("Divisible");
        else
            puts("Not divisible");
    }

    return 0;
}
