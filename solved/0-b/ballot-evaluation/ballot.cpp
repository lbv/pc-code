#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXLEN 20
#define EPS    (1e-6)


typedef unsigned int  u32;
typedef unsigned char uch;


//
// Hash Map
//
#define HASHB 64
struct HM {
    struct Key {
        char n[MAXLEN + 1];
        int l;
        Key(char *N) { strcpy(n, N); l = strlen(n); }
        bool operator==(const Key &x) const {
            return l == x.l && strncmp(n, x.n, l) == 0; }
    };
    struct KV {
        Key k; int v;
        KV(const Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<char*>(k.n));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    void add(const Key &k, int v) {
        int i = fnv_hash(k, k.l) % HASHB;
        b[i].push_back(KV(k, v));
    }
    int get(const Key &k) const {
        int i = fnv_hash(k, k.l) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) return b[i][j].v;
        return -1;
    }
};
int p, g;
char str[MAXLEN + 1];


int main()
{
    while (true) {
        if (scanf("%d%d", &p, &g) != 2) break;

        HM hm;

        while (p--) {
            double v;
            scanf("%s%lf", str, &v);
            int vp = v * 10 + EPS;

            hm.add(HM::Key(str), vp);
        }
        for (int i = 1; i <= g; ++i) {
            int sum = 0;
            while (true) {
                scanf("%s", str);
                sum += hm.get(HM::Key(str));

                scanf("%s", str);
                if (str[0] != '+') break;
            }

            int guess;
            scanf("%d", &guess);
            guess *= 10;

            bool res;
            if (strcmp("<", str) == 0)
                res = sum < guess;
            else if (strcmp("<=", str) == 0)
                res = sum <= guess;
            else if (strcmp(">", str) == 0)
                res = sum > guess;
            else if (strcmp(">=", str) == 0)
                res = sum >= guess;
            else
                res = sum == guess;

            printf("Guess #%d was ", i);
            if (res)
                puts("correct.");
            else
                puts("incorrect.");
        }
    }

    return 0;
}
