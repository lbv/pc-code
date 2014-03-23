#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 18

#define Back(b)    ((b) & -(b))
#define PopBack(b) (b &= ~Back(b))
#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


typedef unsigned int  u32;
typedef unsigned char uch;

typedef vector<int> IV;


//
// Hash Map
//
#define HASHB 2048
struct HM {
    typedef int Datum; typedef vector<Datum> DV; DV b[HASHB];
    u32 fnv_hash(int *k, int len) const {
        uch *p = reinterpret_cast<uch*>(k);
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    void add(Datum k) {
        int i = fnv_hash(&k, sizeof(int)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j] == k) return;
        b[i].push_back(k);
    }
    bool get(Datum k) {
        int i = fnv_hash(&k, sizeof(int)) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j] == k) return true;
        return false;
    }
};


int n, K;
int A[MAXN];

IV group1;
IV group2;
HM hm;


bool solve()
{
    int sz1 = n/2;

    group1 = IV();
    group1.push_back(0);

    for (int i = 0; i < sz1; ++i) {
        IV aux;

        cFor (IV, v, group1) {
            aux.push_back(*v);
            aux.push_back(*v + A[i]);
            aux.push_back(*v + A[i] + A[i]);
        }

        group1 = aux;
    }

    group2 = IV();
    group2.push_back(0);

    for (int i = sz1; i < n; ++i) {
        IV aux;

        cFor (IV, v, group2) {
            aux.push_back(*v);
            aux.push_back(*v + A[i]);
            aux.push_back(*v + A[i] + A[i]);
        }

        group2 = aux;
    }

    hm = HM();

    cFor (IV, v, group2)
        hm.add(*v);

    cFor (IV, v, group1) {
        if (*v > K) continue;
        int dif = K - *v;

        if (hm.get(dif)) return true;
    }

    return false;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d%d", &n, &K);
        for (int i = 0; i < n; ++i) scanf("%d", &A[i]);

        printf("Case %d: ", ++ncase);
        if (solve())
            puts("Yes");
        else
            puts("No");
    }

    return 0;
}
