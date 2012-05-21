#include <cstdio>

#define MAX 25

int P;
int N, R;
char S[MAX + 1];
char T[MAX*8 + 1];
char *s, *t;
int i;

void solve()
{
    for (s=S, t=T; *s; s++)
        for (i = 0; i < R; i++, t++)
            *t = *s;
    *t = 0;
}

int main(void)
{
    scanf("%d", &P);
    while (P--) {
        scanf("%d%d%s", &N, &R, S);
        solve();
        printf("%d %s\n", N, T);
    }
    return 0;
}
