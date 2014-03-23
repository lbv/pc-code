#include <cstdio>


int S, B;


char solve()
{
    if (B == 1) return '\\';
    if (S >= B) return '|';
    return '(';
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d%d", &B, &S);
        if (S == 0 && B == 0) break;
        printf("Case %d: :-%c\n", ++ncase, solve());
    }

    return 0;
}
