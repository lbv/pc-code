#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <set>
#include <vector>
using namespace std;

#define MAXM 12
#define MAXN 12

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef vector<char> CV;
typedef vector<int>  IV;

struct cmp_iv {
    bool operator()(const IV &a, const IV &b) const {
        if (a.size() < b.size()) return true;
        if (a.size() > b.size()) return false;
        return a < b;
    }
};
typedef set<IV, cmp_iv>  IVS;

typedef pair<IVS::iterator, bool> IVSret;

struct Node {
    IV p;  // positions
    CV m;  // moves done
};
typedef queue<Node> NQ;

int M, N;
char map[MAXM][MAXN + 1];
CV sol;

int moves[4][MAXM * MAXN];
bool vis_p[MAXM * MAXN];  // positions visited

const char moves_c[5] = "ENSW";
const int deltas[4][2] = {
    {  0,  1 }, // East
    { -1,  0 }, // North
    {  1,  0 }, // South
    {  0, -1 }  // West
};

#define Idx(i,j) ((i) * N + (j))

bool valid_pos(int r, int c) {
    return r >= 0 && r < M && c >= 0 && c < N;
}

void dfs_moves(int m, int i, int j)
{
    vis_p[Idx(i,j)] = true;

    int di = i + deltas[m][0];
    int dj = j + deltas[m][1];

    if (! valid_pos(di, dj)) {
        moves[m][Idx(i, j)] = -1;
        return;
    }

    if (map[di][dj] == '#') {
        moves[m][Idx(i, j)] = Idx(i, j);
        return;
    }

    if (! vis_p[Idx(di, dj)]) dfs_moves(m, di, dj);
    moves[m][Idx(i, j)] = moves[m][Idx(di, dj)];
}

void fill_moves()
{
    for (int m = 0; m < 4; ++m) {
        Zero(vis_p);
        for (int i = 0; i < M; ++i)
            for (int j = 0; j < N; ++j)
                if (map[i][j] == '.' && ! vis_p[Idx(i, j)])
                    dfs_moves(m, i, j);
    }
}

bool solve()
{
    fill_moves();

    Node nd;

    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (map[i][j] == '.')
                nd.p.push_back(Idx(i, j));

    NQ q;
    q.push(nd);

    IVS vis_s;  // states visited
    vis_s.insert(nd.p);

    while (! q.empty()) {
        nd = q.front();
        q.pop();

        if (nd.p.empty()) {
            sol = nd.m;
            return true;
        }

        char last = nd.m.size() > 0 ? nd.m.back() : ' ';

        for (int m = 0; m < 4; ++m) {
            if (moves_c[m] == last) continue;

            Zero(vis_p);

            Node nd2;

            cFor (IV, p, nd.p) {
                int nxt = moves[m][*p];
                if (nxt < 0 || vis_p[nxt]) continue;
                vis_p[nxt] = true;

                nd2.p.push_back(nxt);
            }

            sort(nd2.p.begin(), nd2.p.end());

            IVSret ret = vis_s.insert(nd2.p);
            if (ret.second) {
                nd2.m = nd.m;
                nd2.m.push_back(moves_c[m]);
                q.push(nd2);
            }
        }
    }

    return false;
}

void print_sol()
{
    cFor (CV, c, sol)
        putchar(*c);
    putchar('\n');
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &N);

        for (int i = 0; i < M; ++i) scanf("%s", map[i]);

        printf("Case %d: ", ++ncase);
        if (solve())
            print_sol();
        else
            puts("Impossible");
    }

    return 0;
}
