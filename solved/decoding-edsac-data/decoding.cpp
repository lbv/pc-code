#include <cstdio>

int P, N;
char c, s;
int d;
double I;
int i, b, dig;
const char OP[] = "PQWERTYUIOJ#SZK*?F@D!HNM&LXGABCV";
char res[22];
char *r;

int locate()
{
    for (i = 0; i < 33; i++)
        if (OP[i] == c) return i;
    return -1;
}

void calculate_I(void)
{
    b = (locate() << 12) + (d << 1) + (s=='F' ? 0 : 1);
    //printf("b is %d\n", b);

    bool sgn = false;
    I = 0;
    if (b & (1<<16)) {
        b = ~b + 1;
        sgn = true;
    }
    for (i = 16; i > 0; i--, b>>=1)
        if (b&1) I += 1.0/(1<<i);

    r = res;
    if (sgn) *r++ = '-';
    *r++ = (sgn && I == 0.0 ? '1' : '0');
    *r++ = '.';

    for (i = 0; i < 16; i++) {
        I *= 10.0;
        dig = static_cast<int>(I);
        *r++ = dig + '0';
        I -= dig;
        if (I == 0.0) break;
    }

    *r = 0;
}

int main(void)
{
    scanf("%d", &P);

    while (P--) {
        scanf("%d %c %d %c\n", &N, &c, &d, &s);
        calculate_I();
        printf("%d %s\n", N, res);
    }

    return 0;
}
