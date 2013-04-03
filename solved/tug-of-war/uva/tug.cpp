#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAXN 100
#define MAXW 450

#define Zero(v) memset(v, 0, sizeof(v))

typedef vector<int> IV;

// dp[i][j] will be true iff it's possible to form a team with i people and
// total weight j
bool dp[MAXN / 2 + 1][MAXW*MAXN + 1];

int p[MAXN];
int n;
int W;
int lo, hi;

void run_dp() {
    int half_w = W/2;
    int team_size = n/2;

    Zero(dp);

    dp[0][0] = true;

    // auxiliary vectors to skip some cycles
    IV top(team_size + 1, -1);
    IV bot(team_size + 1, W + 1);

    top[0] = bot[0] = 0;

    sort(p, p + n);

    for (int i = 0; i < n; i++) {
        int k_from = i+1 > team_size ? team_size : i+1;

        for (int k = k_from; k >= 1; k--) {
            int j_from = bot[k-1] + p[i];
            int j_to   = top[k-1] + p[i];

            for (int j = j_from, j2 = j-p[i]; j <= j_to; ++j, ++j2)
                if (! dp[k][j] && dp[k-1][j2])
                    dp[k][j] = true;

            if (j_from < bot[k]) bot[k] = j_from;
            top[k] = j_to;
        }
    }

    int best_w = 0;

    for (int j = 0; true; ++j) {
        if (dp[team_size][half_w + j]) {
            best_w = half_w + j;
            break;
        }
        if (dp[team_size][half_w - j]) {
            best_w = half_w - j;
            break;
        }
    }

    lo = min(best_w, W - best_w);
    hi = max(best_w, W - best_w);
}

int main()
{
    int T;
    scanf("%d", &T);

    bool first = true;
    while (T--) {
        scanf("%d", &n);

        W = 0;
        for (int i = 0; i < n; ++i) {
            scanf("%d", &p[i]);
            W += p[i];
        }

        run_dp();

        if (first) first = false;
        else putchar('\n');

        printf("%d %d\n", lo, hi);
    }

    return 0;
}
