#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;


#define MAX_DEPTH 35
#define INF 1000

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned char u8;


// goal[n]: coordinates of number n in the solution configuration
const int goal[16][2] = {
    { 3, 3 }, { 0, 0 }, { 0, 1 }, { 0, 2 },
    { 0, 3 }, { 1, 0 }, { 1, 1 }, { 1, 2 },
    { 1, 3 }, { 2, 0 }, { 2, 1 }, { 2, 2 },
    { 2, 3 }, { 3, 0 }, { 3, 1 }, { 3, 2 }
};

// moves in lexicographical order
const int dd[4][2] = {
    {  1,  0 },  // D
    {  0, -1 },  // L
    {  0,  1 },  // R
    { -1,  0 }   // U
};
const char moves[] = "DLRU";

// complementary moves (moves that "undo" their complements)
const int cmoves[] = {
    3,  // D's complement is U
    2,
    1,
    0,
    -1
};


struct Game {
    int m[4][4];
    int tmd;   // total sum of manhattan distances
    int lc;    // weight of linear conflicts
    int r, c;  // row and column of blank tile
    int chl;   // index of next children state
    int last;  // last move performed

    Game() {}

    void init() {
        last = 4;

        tmd = 0;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j) {
                int n = m[i][j];
                if (n == 0) {
                    r = i, c = j;
                    continue;
                }
                tmd += abs(i - goal[n][0]) + abs(j - goal[n][1]);
            }
        lc = 0;
        for (int i = 0; i < 4; ++i) {
            if (conflict_in_row(i)) lc += 2;
            if (conflict_in_col(i)) lc += 2;
        }
    }

    bool conflict_in_row(int r) {
        int c1, c2;
        for (c1 = 3; c1 > 0; --c1)
            if (m[r][c1] > 0 && goal[m[r][c1]][0] == r) break;
        if (c1 == 0) return false;
        for (c2 = 0; c2 < c1; ++c2)
            if (m[r][c2] > 0 && goal[m[r][c2]][0] == r &&
                goal[m[r][c1]][1] < goal[m[r][c2]][1])
                return true;
        return false;
    }

    bool conflict_in_col(int c) {
        int r1, r2;
        for (r1 = 3; r1 > 0; --r1)
            if (m[r1][c] > 0 && goal[m[r1][c]][1] == c) break;
        if (r1 == 0) return false;
        for (r2 = 0; r2 < r1; ++r2)
            if (m[r2][c] > 0 && goal[m[r2][c]][1] == c &&
                goal[m[r1][c]][0] < goal[m[r2][c]][0])
                return true;
        return false;
    }
    int h() {
        return tmd + lc;
    }
    bool is_solution() {
        return tmd == 0;
    }
    void reset() {
        chl = 0;
    }
    bool next(Game &child, int &dist, char &delta) {
        int r2, c2;
        int comp_move = cmoves[last];
        for (; chl < 4; ++chl) {
            if (chl == comp_move) continue;
            r2 = r + dd[chl][0];
            c2 = c + dd[chl][1];
            if (r2 >= 0 && r2 < 4 && c2 >= 0 && c2 < 4) break;
        }
        if (chl >= 4) return false;
        child = *this;
        child.last = chl;

        int n = child.m[r2][c2];
        child.tmd += abs(r - goal[n][0]) + abs(c - goal[n][1])
            - abs(r2 - goal[n][0]) - abs(c2 - goal[n][1]);

        swap(child.m[r][c], child.m[r2][c2]);
        child.r = r2, child.c = c2;

        if (r != r2) {
            if (conflict_in_row(r)) child.lc -= 2;
            if (conflict_in_row(r2)) child.lc -= 2;
            if (child.conflict_in_row(r)) child.lc += 2;
            if (child.conflict_in_row(r2)) child.lc += 2;
        }
        if (c != c2) {
            if (conflict_in_col(c)) child.lc -= 2;
            if (conflict_in_col(c2)) child.lc -= 2;
            if (child.conflict_in_col(c)) child.lc += 2;
            if (child.conflict_in_col(c2)) child.lc += 2;
        }

        dist = 1;
        delta = moves[chl++];
        return true;
    }
    bool is_solvable() {
        int invr = 0;
        for (int i = 0; i < 16; ++i) {
            int r = i / 4, c = i % 4;
            if (m[r][c] != 0)
                for (int j = 0; j < i; ++j) {
                    int p = j / 4, q = j % 4;
                    if (m[p][q] != 0 && m[p][q] > m[r][c]) ++invr;
                }
        }
        return (invr + r) % 2 != 0;
    }
    void p() {
        for (int i = 0; i < 4; ++i) {
            for (int j = 0; j < 4; ++j)
                printf("%2d ", m[i][j]);
            puts("");
        }
    }
};

template <typename NT, typename DT>
bool ida_dls(NT &node, int depth, int g, int &nxt, stack<DT> &st)
{
    if (g == depth) return node.is_solution();

    NT child;
    int dist;
    DT delta;
    for (node.reset(); node.next(child, dist, delta);) {
        int f = g + dist + child.h();
        if (f > depth && f < nxt) nxt = f;
        if (f <= depth  && ida_dls(child, depth, g + 1, nxt, st)) {
            st.push(delta);
            return true;
        }
    }
    return false;
}

template <typename NT, typename DT>
bool ida_star(NT &root, int limit, stack<DT> &st)
{

    for (int depth = root.h(); depth <= limit;) {
        int next_depth = INF;
        if (ida_dls(root, depth, 0, next_depth, st)) return true;
        if (next_depth == INF) return false;
        depth = next_depth;
    }
    return false;
}

void print_sol(stack<char> &sol)
{
    while (! sol.empty()) {
        putchar(sol.top());
        sol.pop();
    }
    putchar('\n');
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        Game g;
        for (int i = 0; i < 4; ++i)
            for (int j = 0; j < 4; ++j)
                scanf("%d", &g.m[i][j]);
        g.init();

        printf("Case %d: ", ++ncase);

        stack<char> st;
        if (g.is_solvable() && ida_star(g, MAX_DEPTH, st))
            print_sol(st);
        else
            puts("This puzzle is not solvable.");
    }

    return 0;
}
