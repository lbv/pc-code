#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

typedef unsigned int u32;
typedef long long i64;

#define BUF 65536
class Reader {
    char buf[BUF]; char b; int bi, bz;
public:
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 nextU32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void nextRealLine(char *s) {
        for (; b != 10 && b != 13; read()) *s++ = b; *s = 0;
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

#define MAX 30

char s1[MAX+1], s2[MAX+1];  // the strings

// dp1[i][j] has the length of the shortest string that contains s1_i and
// s2_j as subsequences, where s_i means the prefix of s of length i
int dp1[MAX+2][MAX+2];

// dp2[i][j] has the number of unique shortest strings that contain s1_i and
// s2_j as subsequences
i64 dp2[MAX+2][MAX+2];

size_t l1, l2;  // lengths of s1 and s2

void run_dp()
{
    dp1[0][0] = 0;
    for (size_t i = 1; i <= l1; i++) dp1[i][0] = i;
    for (size_t j = 1; j <= l2; j++) dp1[0][j] = j;
    for (size_t i = 1; i <= l1; i++)
        for (size_t j = 1; j <= l2; j++)
            if (s1[i-1] == s2[j-1])
                dp1[i][j] = dp1[i-1][j-1] + 1;
            else
                dp1[i][j] = min(dp1[i-1][j], dp1[i][j-1]) + 1;
    dp2[0][0] = 1;
    for (size_t i = 1; i <= l1; i++) dp2[i][0] = 1;
    for (size_t j = 1; j <= l2; j++) dp2[0][j] = 1;
    for (size_t i = 1; i <= l1; i++)
        for (size_t j = 1; j <= l2; j++)
            if (s1[i-1] == s2[j-1])
                dp2[i][j] = dp2[i-1][j-1];
            else {
                if (dp1[i-1][j] < dp1[i][j-1])
                    dp2[i][j] = dp2[i-1][j];
                else if (dp1[i-1][j] > dp1[i][j-1])
                    dp2[i][j] = dp2[i][j-1];
                else
                    dp2[i][j] = dp2[i-1][j] + dp2[i][j-1];
            }
}

int main(void)
{
    Reader rr;
    int T;
    T = rr.nextU32();
    rr.nextRealLine(s1);

    int ncase = 1;
    while (T--) {
        rr.nextRealLine(s1);
        rr.nextRealLine(s2);

        l1 = strlen(s1);
        l2 = strlen(s2);

        run_dp();

        printf("Case %d: %d %lld\n", ncase++, dp1[l1][l2], dp2[l1][l2]);
    }

    return 0;
}
