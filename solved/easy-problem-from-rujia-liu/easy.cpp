#include <cstdio>
#include <vector>
using namespace std;


typedef unsigned char uch;
typedef unsigned int  u32;

typedef vector<int> IV;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    bool has_next() { skip(); return b > 0; }
};

//
// Hash Map
//
#define HASHB 8192
const size_t KeySz = sizeof(int);
struct HM {
    typedef int Key;
    struct KV {
        Key k; IV v;
        KV(Key &K, IV &V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(Key k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(&k));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    void add(Key k, int v) {
        int i = fnv_hash(k, KeySz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) { b[i][j].v.push_back(v); return; }
        IV val;
        val.push_back(v);
        b[i].push_back(KV(k, val));
    }
    int get(Key k, int idx) const {
        int i = fnv_hash(k, KeySz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) {
                int sz = b[i][j].v.size();
                if (sz < idx) return 0;
                return b[i][j].v[idx - 1];
            }
        return 0;
    }
};


int n, m;


int main()
{
    Reader rr;
    while (rr.has_next()) {
        n = rr.next_u32();
        m = rr.next_u32();

        HM hm;

        for (int i = 1; i <= n; ++i) {
            int v = rr.next_u32();
            hm.add(v, i);
        }
        while (m--) {
            int k = rr.next_u32();
            int v = rr.next_u32();
            printf("%d\n", hm.get(v, k));
        }
    }

    return 0;
}
