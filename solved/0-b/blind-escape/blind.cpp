#include <algorithm>
#include <cstdio>
#include <cstring>
#include <queue>
#include <vector>
using namespace std;

#define MAXM 12
#define MAXN 12

#define Zero(v) memset(v, 0, sizeof(v))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned int       u32;
typedef unsigned long long u64;
typedef unsigned char      uch;

typedef vector<int>  IV;

//
// Hash Map
//
#define HASHB 4096
struct HM {
    typedef IV Datum; typedef vector<Datum> DV; DV b[HASHB];
    u32 fnv_hash(const Datum &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(&k[0]));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    bool add(const Datum &k, u64 &id) {
        int i = fnv_hash(k, k.size() * sizeof(int)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j] == k) { id = i; id <<= 32; id |= j; return false; }
        b[i].push_back(k);
        id = i; id <<= 32; id |= (b[i].size() - 1);
        return true;
    }
    Datum get(u64 id) const { return b[id>>32][id&0xFFFFFFFF]; }
};

struct Trail {
    struct Node {
        char c; int p;
        Node(char C, int P) : c(C), p(P) {}
    };
    vector<Node> t; int cnt;
    Trail() : cnt(0) {}
    int add(char c, int p) {
        t.push_back(Node(c, p));
        return cnt++;
    }
    char get_last(int i) {
        if (i < 0) return ' ';
        return t[i].c;
    }
    void print(int i) {
        vector<char> str;
        while (i >= 0) {
            str.push_back(t[i].c);
            i = t[i].p;
        }
        for (int j = str.size() - 1; j >= 0; --j)
            putchar(str[j]);
        putchar('\n');
    }
};

struct Node {
    u64 p;  // hash ID of positions
    int t;  // trail of moves index
};
typedef queue<Node> NQ;

int M, N;
char maze[MAXM][MAXN + 1];
Trail trail;
int sol;

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

    if (maze[di][dj] == '#') {
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
                if (maze[i][j] == '.' && ! vis_p[Idx(i, j)])
                    dfs_moves(m, i, j);
    }
}

bool solve()
{
    fill_moves();

    IV pos;
    for (int i = 0; i < M; ++i)
        for (int j = 0; j < N; ++j)
            if (maze[i][j] == '.')
                pos.push_back(Idx(i, j));

    u64 id;
    HM hm;
    hm.add(pos, id);

    Node nd;
    nd.p = id;
    nd.t = -1;
    trail = Trail();

    NQ q;
    q.push(nd);

    while (! q.empty()) {
        nd = q.front();
        q.pop();

        pos = hm.get(nd.p);
        if (pos.empty()) {
            sol = nd.t;
            return true;
        }

        char last = trail.get_last(nd.t);

        for (int m = 0; m < 4; ++m) {
            if (moves_c[m] == last) continue;

            Zero(vis_p);
            IV pos2;

            cFor (IV, p, pos) {
                int nxt = moves[m][*p];
                if (nxt < 0 || vis_p[nxt]) continue;
                vis_p[nxt] = true;

                pos2.push_back(nxt);
            }

            sort(pos2.begin(), pos2.end());

            if (hm.add(pos2, id)) {
                Node nd2;
                nd2.p = id;
                nd2.t = trail.add(moves_c[m], nd.t);
                q.push(nd2);
            }
        }
    }

    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &M, &N);

        for (int i = 0; i < M; ++i) scanf("%s", maze[i]);

        printf("Case %d: ", ++ncase);
        if (solve())
            trail.print(sol);
        else
            puts("Impossible");
    }

    return 0;
}
