#include <cstdio>
#include <list>
#include <set>
using namespace std;

typedef list<int>          IL;
typedef IL::const_iterator ILci;

typedef unsigned int u32;

#define MAXN 150
#define MAXM 50

int N, M;

int   sr[MAXN];  // student regions
int   ss[MAXN];  // student scores
IL    sp[MAXN];  // student priorities
ILci  si[MAXN];  // iterators over student priorities

int fr[MAXM];  // FDU regions
u32 fc[MAXM];  // FDU capacities

struct studentcmp {
    bool operator() (const int &a, const int &b) const {
        int reg = fr[*si[a]];
        if ((sr[a] != reg && sr[b] != reg) || (sr[a] == sr[b]))
            return ss[a] == ss[b] ? a < b : ss[a] > ss[b];
        if (sr[a] == reg)
            return ss[a]*10 > ss[b]*7;
        return ss[a]*7 >= ss[b]*10;
    }
};
typedef set<int, studentcmp> I_S;
typedef I_S::iterator        I_Si;

I_S fq[MAXM];  // FDU queues of students

void match(int s)
{
    if (si[s] == sp[s].end()) return;
    int fdu = *si[s];

    fq[fdu].insert(s);

    if (fq[fdu].size() > fc[fdu]) {
        I_Si i = fq[fdu].end();
        --i;
        int last = *i;
        fq[fdu].erase(i);
        ++si[last];
        match(last);
    }
}

void solve()
{
    for (int i = 0; i < N; ++i)
        match(i);
}

int main()
{
    int t;
    scanf("%d", &t);

    while (t--) {
        scanf("%d%d", &N, &M);

        for (int i = 0; i < N; ++i) {
            int K;
            scanf("%d%d%d", &sr[i], &ss[i], &K);

            sp[i].clear();
            while (K--) {
                int F;
                scanf("%d", &F);
                sp[i].push_back(F-1);
            }
            si[i] = sp[i].begin();
        }

        for (int i = 0; i < M; ++i) {
            scanf("%d%u", &fr[i], &fc[i]);
            fq[i].clear();
        }

        solve();

        for (int i = 0; i < N; ++i) {
            if (si[i] == sp[i].end())
                printf("not accepted\n");
            else
                printf("%d\n", *si[i] + 1);
        }
        putchar('\n');
    }

    return 0;
}
