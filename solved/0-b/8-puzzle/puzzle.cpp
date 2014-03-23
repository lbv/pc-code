#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <stack>
#include <vector>
using namespace std;


#define INF 1000

#define Zero(v) memset((v), 0, sizeof(v))


// goal[n]: coordinates of number n in the solution configuration
const int goal[9][2] = {
    { 2, 2 },
    { 0, 0 }, { 0, 1 }, { 0, 2 },
    { 1, 0 }, { 1, 1 }, { 1, 2 },
    { 2, 0 }, { 2, 1 }
};

// moves
const int dd[4][2] = {
    {  1,  0 },  // down
    {  0, -1 },  // left
    { -1,  0 },  // up
    {  0,  1 }   // right
};


struct Game {
    int m[3][3];
    int tmd;   // total sum of manhattan distances
    int lc;    // weight of linear conflicts
    int r, c;  // row and column of blank tile
    int chl;   // index of next children state
    int last;  // last move performed

    Game() {}

    void init() {
        last = -1;

        tmd = 0;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j) {
                int n = m[i][j];
                if (n == 0) {
                    r = i, c = j;
                    continue;
                }
                tmd += abs(i - goal[n][0]) + abs(j - goal[n][1]);
            }
        lc = 0;
        for (int i = 0; i < 3; ++i) {
            if (conflict_in_row(i)) lc += 2;
            if (conflict_in_col(i)) lc += 2;
        }
    }

    bool conflict_in_row(int r) {
        int c1, c2;
        for (c1 = 2; c1 > 0; --c1)
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
        for (r1 = 2; r1 > 0; --r1)
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
    bool next(Game &child, int &dist, int &delta) {
        int r2, c2;
        int comp_move = last >= 0 ? (last + 2) % 4 : -1;
        for (; chl < 4; ++chl) {
            if (chl == comp_move) continue;
            r2 = r + dd[chl][0];
            c2 = c + dd[chl][1];
            if (r2 >= 0 && r2 < 3 && c2 >= 0 && c2 < 3) break;
        }
        if (chl >= 4) return false;
        child = *this;
        child.last = chl++;

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
        return true;
    }
    bool is_solvable() {
        int invr = 0;
        for (int i = 0; i < 9; ++i) {
            int r = i / 3, c = i % 3;
            if (m[r][c] != 0)
                for (int j = 0; j < i; ++j) {
                    int p = j / 3, q = j % 3;
                    if (m[p][q] != 0 && m[p][q] > m[r][c]) ++invr;
                }
        }
        return invr % 2 == 0;
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
            if (st.empty()) st.push(dist);
            else {
                int steps = st.top();
                st.pop();
                st.push(steps + dist);
            }
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

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        Game g;
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                scanf("%d", &g.m[i][j]);
        g.init();

        printf("Case %d: ", ++ncase);

        stack<int> st;
        if (g.is_solvable() && ida_star(g, INF, st))
            printf("%d\n", st.empty() ? 0 : st.top());
        else
            puts("impossible");
    }

    return 0;
}
