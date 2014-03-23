#include <cctype>
#include <cstdio>
#include <cstring>
#include <set>
#include <vector>
using namespace std;


#define MAXLINE   160
#define MAXWORD   150
#define MAXNWORDS 100010

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned char uch;
typedef unsigned int  u32;

typedef pair<int, int> II;


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = 10*v+b-48; return v; }
    void skip_line() {
        for (; b != 10 && b != 13 && b >= 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b >= 0; read()) { *s++ = b; ++l; }
        *s = 0;
        while (b == 10 || b == 13) read(); }
};

//
// Hash Map
//
#define HASHB 4096
struct HM {
    struct Key {
        char w[MAXWORD + 1];
        Key(char *W) { strcpy(w, W); }
        bool operator==(const Key &x) const { return strcmp(w, x.w) == 0; }
    };
    struct KV {
        Key k; int v;
        KV(const Key &K, int V) : k(K), v(V) {}
    };
    typedef vector<KV> KVV; KVV b[HASHB];
    u32 fnv_hash(const Key &k) const {
        uch *p = reinterpret_cast<uch*>(const_cast<char*>(k.w));
        u32 h = 2166136261U;
        for (int i = 0; p[i] != 0; ++i) h = (h * 16777619U) ^ p[i];
        return h;
    }
    int add(const Key &k, int v) {
        int i = fnv_hash(k) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j].k == k) return b[i][j].v;
        b[i].push_back(KV(k, v));
        return v;
    }
};

//
// Simple list
//
struct Node {
    int d;  // data
    int n;  // next
};
Node pool[MAXNWORDS];
int nnodes;

struct List {
    int h, t;

    void append(int d) {
        int nd = ++nnodes;
        pool[nd].d = d, pool[nd].n = 0;
        if (h == 0) h = nd;
        else pool[t].n = nd;
        t = nd;
    }
    int get() { return pool[h].d; }
    void next() { h = pool[h].n; }
    bool empty() { return h == 0; }
};


Reader rr;
int p, q;
char line[MAXLINE + 1];
int len;
int nwords;  // total number of words
int uwords;  // number of unique words

List loc[MAXNWORDS];  // locations of every unique word in the text


void read_text()
{
    HM hm;

    Zero(loc);
    nnodes = 0;
    nwords = uwords = 0;

    while (true) {
        rr.next_line(line, len);
        if (strcmp("END", line) == 0) break;

        int i = 0;
        while (true) {
            while (i < len && ! islower(line[i])) ++i;
            if (i >= len) break;

            char *tok = &line[i];
            while (islower(line[i])) ++i;
            line[i] = 0;

            int id = hm.add(HM::Key(tok), uwords);
            if (id == uwords) ++uwords;
            ++nwords;

            loc[id].append(nwords);
        }
    }
}

void solve()
{
    multiset<II> s;

    p = 1;
    q = nwords;

    for (int i = 0; i < uwords; ++i) {
        s.insert(II(loc[i].get(), i));
        loc[i].next();
    }

    while (true) {
        II a = *(s.begin());
        II b = *(s.rbegin());

        if (b.first - a.first < q - p) p = a.first, q = b.first;

        if (loc[a.second].empty()) break;

        s.erase(s.begin());
        s.insert(II(loc[a.second].get(), a.second));
        loc[a.second].next();
    }
}

int main()
{
    int T = rr.next_u32();
    rr.skip_line();

    int ncase = 0;
    while (T--) {
        read_text();
        solve();
        printf("Document %d: %d %d\n", ++ncase, p, q);
    }

    return 0;
}
