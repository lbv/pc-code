#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXN 700


typedef  unsigned char  uch;
typedef  unsigned int   u32;


//
// Hash Map
//
#define HASHB 4096
const size_t KeySz = sizeof(int) * 2;
struct HM {
    struct Key {
        int d[2];
        Key(int *D) { memcpy(d, D, KeySz); }
        bool operator==(const Key &x) const {
            return memcmp(d, x.d, KeySz) == 0; }
    };
    struct KV {
        Key k; int v;
        KV(const Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(k.d));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U) ^ p[i];
        return h;
    }
    int add(const Key &k) {
        int i = fnv_hash(k, KeySz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k)
                return ++b[i][j].v;
        b[i].push_back(KV(k, 2));
        return 2;
        return true;
    }
};


template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }


int  n;
int  pts[MAXN][2];


int solve()
{
    if (n <= 2) return n;
    int ans = 0;

    int m[2];  // slope, as a rational number

    for (int i = 0; i < n; ++i) {
        HM hm;

        for (int j = i + 1; j < n; ++j) {
            if (pts[i][0] == pts[j][0])
                m[0] = m[1] = 0;
            else {
                m[0] = pts[j][1] - pts[i][1];
                m[1] = pts[j][0] - pts[i][0];

                int g = gcd(m[0], m[1]);
                m[0] /= g;
                m[1] /= g;
            }

            int coll = hm.add(HM::Key(m));
            if (coll > ans) ans = coll;
        }
    }

    return ans;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%d", &n);

        for (int i = 0; i < n; ++i)
            scanf("%d%d", &pts[i][0], &pts[i][1]);

        printf("Case %d: %d\n", ++ncase, solve());
    }

    return 0;
}
