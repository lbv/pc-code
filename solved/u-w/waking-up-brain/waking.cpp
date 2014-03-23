#include <cstdio>
#include <cstring>
#include <list>
#include <vector>
using namespace std;


#define Zero(v) memset((v), 0, sizeof(v))

#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


typedef list<int> IL;
typedef IL::iterator ILi;


// Adjacency lists
struct Graph {
    struct Edge { int v; Edge(int V) : v(V) {} };
    typedef list<Edge> EL;
    typedef vector<EL> ELV;
    ELV adj; int n;
    Graph(int N) : n(N) { adj.resize(n); }
    void add(int u, int v) { adj[u].push_back(Edge(v)); }
};

typedef Graph::EL::iterator GELi;


int N, M;
int still;  // count of how many nodes are still sleeping

// conn[i]: number of direct connections of node i to awake nodes
int conn[26];
bool sleeping[26];
char first[4];
int ans;


bool solve(Graph &g)
{
    IL asleep;
    for (int i = 0; i < 26; ++i)
        if (sleeping[i])
            asleep.push_back(i);

    ans = 0;

    Zero(conn);
    while (still > 0) {
        int before = still;

        For (IL, sp, asleep) {
            int s = *sp;

            for (GELi it = g.adj[s].begin(); it != g.adj[s].end(); ) {
                if (! sleeping[it->v]) {
                    ++conn[s];
                    it = g.adj[s].erase(it);
                }
                else
                    ++it;
            }
        }

        for (IL::iterator sp = asleep.begin(); sp != asleep.end(); ) {
            int s = *sp;
            if (conn[s] >= 3) {
                sleeping[s] = false;
                --still;
                sp = asleep.erase(sp);
            }
            else
                ++sp;
        }

        if (still == before) return false;
        ++ans;
    }

    return true;
}

int main()
{
    while (true) {
        if (scanf("%d%d", &N, &M) != 2) break;

        Zero(sleeping);
        still = 0;

        Graph g(26);

        scanf("%s", first);

        for (int i = 0; i < 3; ++i) {
            int idx = first[i] - 'A';
            if (! sleeping[idx]) {
                sleeping[idx] = true;
                ++still;
            }
        }
        while (M--) {
            char a, b;
            scanf(" %c%c", &a, &b);
            int u = a - 'A';
            int v = b - 'A';
            g.add(u, v);
            g.add(v, u);

            if (! sleeping[u]) {
                sleeping[u] = true;
                ++still;
            }
            if (! sleeping[v]) {
                sleeping[v] = true;
                ++still;
            }
        }

        if (still < N) {
            puts("THIS BRAIN NEVER WAKES UP");
            continue;
        }

        for (int i = 0; i < 3; ++i) {
            int idx = first[i] - 'A';
            if (sleeping[idx]) {
                sleeping[idx] = false;
                --still;
            }
        }

        if (solve(g))
            printf("WAKE UP IN, %d, YEARS\n", ans);
        else
            puts("THIS BRAIN NEVER WAKES UP");
    }

    return 0;
}
