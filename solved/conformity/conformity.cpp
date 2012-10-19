#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


typedef unsigned int  u32;
typedef unsigned char uch;


struct Reader {
    char b; Reader() { read(); }
    void read() { int r = fgetc_unlocked(stdin); b = r == EOF ? 0 : r; }
    void skip() { while (b > 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};

//
// Hash Map
//
#define HASHB 4096
const size_t KeySz = sizeof(int) * 5;
struct HM {
    struct Key {
        int n[5];
        Key(int *N) { memcpy(n, N, KeySz); sort(n, n + 5); }
        bool operator==(const Key &x) const {
            return memcmp(n, x.n, KeySz) == 0; }
    };
    struct KV {
        Key k; int v;
        KV(Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(k.n));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    int add(Key &k) {
        int i = fnv_hash(k, KeySz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) { return ++b[i][j].v; }
        b[i].push_back(KV(k, 1));
        return 1;
    }
};


int n;
int ns[5];


int main()
{
    Reader rr;
    while (true) {
        n = rr.next_u32();
        if (n == 0) break;

        HM hm;
        int pop = 0;
        int ans = 0;
        while (n--) {
            for (int i = 0; i < 5; ++i)
                ns[i] = rr.next_u32();

            HM::Key k(ns);
            int p = hm.add(k);
            if (p > pop)
                ans = pop = p;
            else if (p == pop)
                ans += p;
        }
        printf("%d\n", ans);
    }

    return 0;
}
