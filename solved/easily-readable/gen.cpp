#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>
#include <set>
#include <string>
using namespace std;


#define MAXT   20
#define MAXN   10000
#define MAXM   10000
#define MAXLEN 100
#define MAXDIC 100000
#define MAXSEN 10000
#define MAXALL 100000


char dict[MAXN][MAXLEN + 1];
int lens[MAXN];

const char alpha[] =
"abcdefghijklmnopqrstuvwxyz"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
int nalpha;


void gen_word(char *w, int l)
{
    for (int i = 0; i < l; ++i)
        w[i] = alpha[rand() % nalpha];
    w[l] = 0;
}

bool gen_word_from_others(char *w, int n)
{
    int idx;
    bool found = false;
    for (int i = 0; i < 10; ++i) {
        idx = rand() % n;
        if (lens[idx] <= lens[n]) {
            found = true;
            break;
        }
    }
    if (! found) return false;

    strcpy(w, dict[idx]);
    int len = strlen(w);
    if (len > 3)
        random_shuffle(w + 1, w + len - 1);
    return true;
}

void test_case(bool crit = false)
{
    int n = crit ? MAXN : rand() % (MAXN + 1);
    printf("%d\n", n);

    int left = MAXDIC;

    for (int i = 0; i < n; ++i) {
        int top = left / (n - i);
        lens[i] = rand() % top + 1;
        if (lens[i] < 3) lens[i] = 3;
        if (lens[i] > MAXLEN) lens[i] = MAXLEN;
        if (crit && i == 0) lens[i] = MAXLEN;
        left -= lens[i];
    }
    random_shuffle(lens, lens + n);

    gen_word(dict[0], lens[0]);

    set<string> ss;
    ss.insert(string(dict[0]));

    for (int i = 1; i < n; ++i) {
        bool succ;
        do {
            succ = true;
            if (rand() % 3 == 0)
                succ = gen_word_from_others(dict[i], i);
            else
                gen_word(dict[i], lens[i]);
        } while (!succ || ss.find(string(dict[i])) != ss.end());
        ss.insert(string(dict[i]));
    }

    for (int i = 0; i < n; ++i)
        printf("%s\n", dict[i]);

    int m = crit ? MAXM : rand() % (MAXM + 1);
    printf("%d\n", m);

    left = MAXALL;
    for (int i = 0; i < m; ++i) {
        int top = left / (m - i);
        int line = rand() % (top + 1);
        if (crit && i == 0) line = MAXSEN;

        left -= line;

        while (line > 0) {
            int w = rand() % n;
            if (lens[w] + 1 <= line) {
                printf("%s ", dict[w]);
                line -= lens[w];
            }
            else {
                putchar(' ');
                --line;
            }
        }
        putchar('\n');
    }
}

int main()
{
    srand(time(NULL));

    nalpha = strlen(alpha);

    int T = MAXT;
    printf("%d\n", T);

    test_case(true); --T;
    while (T--) test_case();

    return 0;
}
