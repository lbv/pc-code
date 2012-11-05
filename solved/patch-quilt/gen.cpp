#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;


#if 1
#define MAXT 200
#define MAXR 30
#define MAXC 30
#define MAXN 20
#define MAX_NAME 15
#endif

#if 0
#define MAXT 30
#define MAXR 8
#define MAXC 8
#define MAXN 5
#define MAX_NAME 12
#endif


#define Zero(v) memset(v, 0, sizeof(v))

struct Pos
{
    int r, c;
    Pos(int R, int C) : r(R), c(C) {}
    Pos() { r = c = 0; }
};
typedef vector<Pos> PV;


int R, C;
int nlen;

char quilt[MAXR][MAXC + 1];
char name[MAX_NAME + 1];

int nsol;
Pos trail[MAX_NAME];
PV sol;


void test_case1()
{
    printf(
"2 2\n"
"AB\n"
"CD\n"
"5\n"
"AB\n"
"ABC\n"
"ABCD\n"
"ABCDA\n"
"XYZHSJDH\n"
);
}

void test_case2()
{
    printf(
"5 7\n"
"ABCDEFG\n"
"HIJKLMN\n"
"OPQRSTU\n"
"VWXYZAB\n"
"CDEFGHI\n"
"4\n"
"RLKQYSMEDJPXFGA\n"
"AHOVCDWPIB\n"
"STUBIHGZS\n"
"ZZZZZZZZZZZZZZA\n"
);
}

void test_case3()
{
    printf(
"21 21\n"
"ZZZZZZZZZZZZZZZZZZZZZ\n"
"ZJJJJJJJJJJJJJJJJJJJZ\n"
"ZJIIIIIIIIIIIIIIIIIJZ\n"
"ZJIHHHHHHHHHHHHHHHIJZ\n"
"ZJIHGGGGGGGGGGGGGHIJZ\n"
"ZJIHGFFFFFFFFFFFGHIJZ\n"
"ZJIHGFEEEEEEEEEFGHIJZ\n"
"ZJIHGFEDDDDDDDEFGHIJZ\n"
"ZJIHGFEDCCCCCDEFGHIJZ\n"
"ZJIHGFEDCBBBCDEFGHIJZ\n"
"ZJIHGFEDCBABCDEFGHIJZ\n"
"ZJIHGFEDCBBBCDEFGHIJZ\n"
"ZJIHGFEDCCCCCDEFGHIJZ\n"
"ZJIHGFEDDDDDDDEFGHIJZ\n"
"ZJIHGFEEEEEEEEEFGHIJZ\n"
"ZJIHGFFFFFFFFFFFGHIJZ\n"
"ZJIHGGGGGGGGGGGGGHIJZ\n"
"ZJIHHHHHHHHHHHHHHHIJZ\n"
"ZJIIIIIIIIIIIIIIIIIJZ\n"
"ZJJJJJJJJJJJJJJJJJJJZ\n"
"ZZZZZZZZZZZZZZZZZZZZK\n"
"4\n"
"ABCDEFGHIJK\n"
"KJIHGFEDCBA\n"
"ABCDEFGHIJM\n"
"KJK\n"
);
}

void test_case4()
{
    printf(
"30 30\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n"
"14\n"
"AB\n"
"AAB\n"
"AAAB\n"
"AAAAB\n"
"AAAAAB\n"
"AAAAAAB\n"
"AAAAAAAB\n"
"AAAAAAAAB\n"
"AAAAAAAAAB\n"
"AAAAAAAAAAB\n"
"AAAAAAAAAAAB\n"
"AAAAAAAAAAAAB\n"
"AAAAAAAAAAAAAB\n"
"AAAAAAAAAAAAAAB\n"
);
}

void test_case5()
{
    printf(
"1 1\n"
"P\n"
"3\n"
"AA\n"
"PP\n"
"PQ\n"
);
}

bool valid_pos(Pos p)
{
    return p.r >= 0 && p.r < R && p.c >= 0 && p.c < C;
}

void choose_name_random()
{
    nlen = rand() % (MAX_NAME - 1) + 2;
    for (int i = 0; i < nlen; ++i)
        name[i] = 'A' + (rand() % 26);
    name[nlen] = '\0';
}

void choose_name_from_quilt()
{
    nlen = rand() % (MAX_NAME - 1) + 2;

    int n = 0;
    Pos nextpos(rand() % R, rand() % C);

    Pos alt[9];

    while (n < nlen) {
        name[n++] = quilt[nextpos.r][nextpos.c];

        int nalt = 0;
        for (int i = -1; i <= 1; ++i)
            for (int j = -1; j <= 1; ++j) {
                Pos p2(nextpos.r + i, nextpos.c + j);
                if (valid_pos(p2))
                    alt[nalt++] = p2;
            }

        int i = rand() % nalt;
        nextpos = alt[i];
    }

    name[n] = '\0';
}

void dfs(int r, int c, int n)
{
    if (quilt[r][c] != name[n]) return;

    trail[n++] = Pos(r, c);

    if (n == nlen) {
        ++nsol;
        for (int i = 0; i < nlen; ++i)
            sol.push_back(trail[i]);
        return;
    }

    for (int i = -1; i <= 1; ++i)
        for (int j = -1; j <= 1; ++j) {
            Pos p(r + i, c + j);
            if (! valid_pos(p)) continue;

            dfs(p.r, p.c, n);
        }
}

bool name_is_valid()
{
    nsol = 0;

    sol.clear();
    for (int i = 0; i < R; ++i)
        for (int j = 0; j < C; ++j)
            dfs(i, j, 0);

    return nsol < 2;
}

void test_case_random()
{
    do {
        R = rand() % MAXR + 1;
        C = rand() % MAXC + 1;
    } while (R == 1 && C == 1);

    printf("%d %d\n", R, C);

    for (int i = 0; i < R; ++i) {
        for (int j = 0; j < C; ++j)
            quilt[i][j] = 'A' + (rand() % 26);
        quilt[i][C] = '\0';
        printf("%s\n", quilt[i]);
    }

    int N = rand() % MAXN + 1;
    printf("%d\n", N);

    while (N) {
        if (rand() % 5 == 0)
            choose_name_random();
        else
            choose_name_from_quilt();

        if (name_is_valid()) {
            printf("%s\n", name);
            --N;
        }
    }
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    test_case1(); T--;
    test_case2(); T--;
    test_case3(); T--;
    test_case4(); T--;
    test_case5(); T--;

    while (T--)
        test_case_random();

    return 0;
}
