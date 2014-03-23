#include <cstdio>
#include <cstring>


#define MAXLEN 30


typedef unsigned long long u64;


char s[MAXLEN + 1];
int  len;
u64  idx;

u64 pow4[MAXLEN*2 + 1];


int dna_code(char c)
{
    if (c == 'A') return 0;
    if (c == 'C') return 1;
    if (c == 'G') return 2;
    return 3;
}

void solve()
{
    len = strlen(s);
    idx = 0;
    for (int i = len - 1, j = 0; i >= 0; --i, ++j)
        idx += pow4[j] * dna_code(s[i]);
}

void prepare()
{
    pow4[0] = 1;
    for (int i = 1; i <= 2*MAXLEN; ++i)
        pow4[i] = pow4[i - 1] * 4;
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s", s);
        solve();
        printf("Case %d: (%d:%llu)\n", ++ncase, len, idx);
    }

    return 0;
}
