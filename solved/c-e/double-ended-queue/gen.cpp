#include <cstdio>
#include <cstdlib>
#include <ctime>


#if 0
#define MAXT 20
#define MAXN 10
#define MAXM 100
#define MINX -100
#define MAXX 100
#define NL   0
#endif

#if 1
#define MAXT 20
#define MAXN 10
#define MAXM 8
#define MINX -100
#define MAXX 100
#define NL   1
#endif


const int XRange = MAXX - MINX + 1;
const char cmds[4][20] = {
    "pushLeft",
    "pushRight",
    "popLeft",
    "popRight"
};


void test_case(bool crit = false)
{
#if NL
    puts("");
#endif

    int n = crit ? MAXN : rand() % MAXN + 1;
    int m = crit ? MAXM : rand() % MAXM + 1;
    printf("%d %d\n", n, m);

    while (m--) {
        int cmd = rand() % 4;
        printf("%s", cmds[cmd]);
        if (cmd <= 1) {
            int x = rand() % XRange + MINX;
            printf(" %d", x);
        }
        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}
