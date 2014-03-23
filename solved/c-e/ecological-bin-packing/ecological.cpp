#include <cstdio>

typedef long long i64;

const char bins[4] = "BGC";
const int choices[6][3] = {
    { 0, 2, 1 },  // BCG
    { 0, 1, 2 },  // BGC
    { 2, 0, 1 },  // CBG
    { 2, 1, 0 },  // CGB
    { 1, 0, 2 },  // GBC
    { 1, 2, 0 }   // GCB
};

int main()
{
    int x[3];
    int y[3];
    int z[3];

    while (true) {
        if (scanf("%d%d%d%d%d%d%d%d%d",
                  &x[0], &x[1], &x[2],
                  &y[0], &y[1], &y[2],
                  &z[0], &z[1], &z[2]) != 9) break;

        i64 min_moves = 1LL << 32;
        int min_idx = -1;

        for (int i = 0; i < 6; ++i) {
            int moves = 0;

            for (int j = 0; j < 3; ++j) {
                if (j != choices[i][0])
                    moves += x[j];
                if (j != choices[i][1])
                    moves += y[j];
                if (j != choices[i][2])
                    moves += z[j];
            }

            if (moves < min_moves) min_moves = moves, min_idx = i;
        }

        printf("%c%c%c %lld\n",
               bins[choices[min_idx][0]],
               bins[choices[min_idx][1]],
               bins[choices[min_idx][2]], min_moves);
    }

    return 0;
}
