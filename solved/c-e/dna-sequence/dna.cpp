#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
using namespace std;


#define MAXN   15
#define MAXLEN 100

const int INF = MAXN * MAXLEN + 10;

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))
static const int m37pos[] = {
    32,  0,  1, 26,  2, 23, 27,  0,  3,
    16, 24, 30, 28, 11,  0, 13,  4,  7,
    17,  0, 25, 22, 31, 15, 29, 10, 12,
     6,  0, 21, 14,  9,  5, 20,  8, 19, 18
};
#define Ctz(x) (m37pos[(x) % 37])


typedef unsigned int u32;


struct Node {
    int s;  // index of the string for the current node
    int l;  // length of the prefix of ss[s] to use
    int t;  // total length of string formed, until the end
    int n;  // next node
};

Node pool[(1 << MAXN) * MAXN + 10];
int np;
#define ClearAll() (np = 0)
#define Data(i)    (pool[i])
int node_new(int s=0, int l=0, int t=0, int n=-1)
{
    int idx = np++;
    pool[idx].s = s;
    pool[idx].l = l;
    pool[idx].t = t;
    pool[idx].n = n;
    return idx;
}
int node_copy(int nd)
{
    int idx = np++;
    pool[idx] = pool[nd];
    return idx;
}


int n;
string input[MAXN];
char str[MAXLEN + 1];

string ss[MAXN];  // strings (after those that are substrings of another)
int N;            // real number of strings

// over[i][j]: length of overlap between the suffix of string i and the
// prefix of string j
int over[MAXN][MAXN];

// dp[i][b]: index of the node that describes the lexicographically lowest,
// shortest string the contains all strings in the bitmask b as substrings,
// starting with string i
int dp[MAXN][1 << MAXN];


void print_string(int p)
{
    int x = 0;
    for (int i = 0, I = Data(p).t; i < I; ++i) {
        if (x >= Data(p).l) { p = Data(p).n; x = 0; }
        putchar(ss[Data(p).s][x]);
        ++x;
    }
}

// true if the string formed starting at node a is lower than the string from
// node b
bool string_less(int a, int b)
{
    int x = 0;
    int y = 0;
    int delta, cmp;
    int left = Data(a).t;

    while (left > 0) {
        if (x >= Data(a).l) { a = Data(a).n; x = 0; }
        if (y >= Data(b).l) { b = Data(b).n; y = 0; }

        if (x == 0)
            delta = min(left, min(Data(a).l, Data(b).l - y));
        else
            delta = min(left, min(Data(b).l, Data(a).l - x));

        cmp = ss[Data(a).s].compare(x, delta, ss[Data(b).s], y, delta);

        if (cmp < 0) return true;
        if (cmp > 0) return false;

        x += delta;
        y += delta;
        left -= delta;
    }

    return false;
}

void solve()
{
    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j) {
            if (i == j) continue;

            int len = min(ss[i].size(), ss[j].size());
            over[i][j] = 0;

            for (int k = 1, p = ss[i].size() - 1; k <= len; ++k, --p)
                if (ss[i].compare(p, k, ss[j], 0, k) == 0)
                    over[i][j] = k;
        }

    ClearAll();
    int best = node_new();
    int aux  = node_new();

    u32 all = (1 << N) - 1;
    for (u32 b = 1; b <= all; ++b) {
        for (u32 x = b; x; ClrFS(x)) {
            u32 c = GetFS(x);
            int i = Ctz(c);

            u32 r = b & ~c;
            if (r == 0) {
                dp[i][b] = node_new(i, ss[i].size(), ss[i].size());
                continue;
            }

            Data(best).t = INF;

            for (u32 y = r; y; ClrFS(y)) {
                int j = Ctz(GetFS(y));

                Data(aux).s = i;
                Data(aux).l = ss[i].size() - over[i][j];
                Data(aux).t = Data(aux).l + Data(dp[j][r]).t;
                Data(aux).n = dp[j][r];

                if (Data(aux).t < Data(best).t
                    || (Data(aux).t == Data(best).t
                        && string_less(aux, best)))
                    Data(best) = Data(aux);
            }

            dp[i][b] = node_copy(best);
        }
    }

    Data(best).t = INF;
    for (u32 x = all; x; ClrFS(x)) {
        int i = Ctz(GetFS(x));


        int tmp = dp[i][all];
        if (Data(tmp).t < Data(best).t
            || (Data(tmp).t == Data(best).t
                && string_less(tmp, best)))
            Data(best) = Data(tmp);
    }

    print_string(best);
    putchar('\n');
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i) {
            scanf("%s", str);
            input[i] = string(str);
        }

        N = 0;
        for (int i = 0; i < n; ++i) {
            bool ignore = false;

            for (int j = 0; j < n; ++j) {
                if (i == j) continue;

                if (input[i].size() < input[j].size()
                    && input[j].find(input[i]) != string::npos) {
                    ignore = true;
                    break;
                }

                if (input[i] == input[j] && i > j) {
                    ignore = true;
                    break;
                }
            }

            if (ignore) continue;
            ss[N++] = input[i];
        }

        printf("Case %d: ", ++ncase);
        solve();
    }

    return 0;
}
