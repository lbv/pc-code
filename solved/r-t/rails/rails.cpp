#include <cstdio>


#define MAXN 1000


int N;
int perm[MAXN];

int sk[MAXN];  // stack
int ss;        // stack size


bool solve()
{
    int nxt = 1;  // next number to take from the A direction

    ss = 0;
    for (int i = 0; i < N; ++i) {
        int n = perm[i];

        while (n >= nxt)
            sk[ss++] = nxt++;

        if (ss == 0 || sk[--ss] != n) return false;
    }
    return ss == 0;
}

int main()
{
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        while (true) {
            scanf("%d", &perm[0]);
            if (perm[0] == 0) break;

            for (int i = 1; i < N; ++i)
                scanf("%d", &perm[i]);

            if (solve())
                puts("Yes");
            else
                puts("No");
        }

        puts("");
    }

    return 0;
}
