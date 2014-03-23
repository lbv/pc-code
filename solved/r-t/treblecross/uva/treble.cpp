#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

#define MAXLEN 200

#define Zero(v) memset(v, 0, sizeof(v))

bool aux[MAXLEN + 1];
int gnum[MAXLEN + 1];  // grundy numbers

char b[MAXLEN + 1];  // board
int len;
int nim;

// from[i] and to[i] are indices that indicate that position i is part of a
// gap of spaces int the range [ from[i], to[i] - 1 ]
int from[MAXLEN + 1];
int to[MAXLEN + 1];

// array and size of "hot" positions: positions from which a trivial win is
// possible in the first turn
int hot[MAXLEN + 1];
int  hs;

#define Lo(i) (max(0, i))

void prepare()
{
    // calculate grundy numbers for different board sizes
    for (int i = 1; i <= MAXLEN; ++i) {
        Zero(aux);

        for (int j = 0, k = i - 1; j <= k; ++j, --k)
            aux[gnum[Lo(j - 2)] ^ gnum[Lo(k - 2)]] = true;

        int idx;
        for (idx = 0; aux[idx]; ++idx) ;
        gnum[i] = idx;
    }
}

#define O(i) (b[i] == '.')
#define X(i) (b[i] == 'X')

void analyze()
{
    // first see if there are any hot positions
    hs = 0;
    for (int i = 0; i < len; ++i) {
        if (i - 2 >= 0 && O(i) && X(i - 2) && X(i - 1)) {
            hot[hs++] = i;
            continue;
        }

        if (i - 1 >= 0 && i + 1 < len && O(i) && X(i - 1) && X(i + 1)) {
            hot[hs++] = i;
            continue;
        }

        if (i + 2 < len && O(i) && X(i + 1) && X(i + 2))
            hot[hs++] = i;
    }
    if (hs > 0) return;

    // now identify all gaps for all open positions
    int f = -2;
    for (int i = 0; i < len; ++i) {
        if (X(i)) {
            for (int j = i - 1, J = Lo(f); j >= J; --j)
                to[j] = i;
            f = i + 1;
        }
        from[i] = f;
    }
    for (int j = len - 1, J = Lo(f); j >= J; --j)
        to[j] = len + 2;

    // finally, calculate the total nimber of the board
    nim = 0;
    for (int i = 0; i < len; ++i)
        if (O(i)) {
            nim ^= gnum[Lo(to[i] - from[i] - 4)];
            i = to[i];
        }
}

int main()
{
    prepare();

    int T;
    scanf("%d", &T);

    while (T--) {
        scanf("%s", b);
        len = strlen(b);

        analyze();

        if (hs > 0) {
            puts("WINNING");
            for (int i = 0; i < hs; ++i)
                printf("%s%d", i == 0 ? "" : " ", hot[i] + 1);
            putchar('\n');
            continue;
        }

        if (nim == 0) {
            puts("LOSING\n");
            continue;
        }

        puts("WINNING");
        bool first = true;
        for (int i = 0; i < len; ++i) {
            if (! O(i)) continue;

            if (i - from[i] < 2 || to[i] - (i + 1) < 2) continue;

            int n = nim ^ gnum[Lo(to[i] - from[i] - 4)];
            n ^= gnum[Lo(i - from[i] - 4)];
            n ^= gnum[Lo(to[i] - (i + 1) - 4)];

            if (n == 0) {
                if (first) first = false;
                else putchar(' ');

                printf("%d", i + 1);
            }
        }
        putchar('\n');
    }

    return 0;
}
