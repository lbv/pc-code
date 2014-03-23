#include <algorithm>
#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXK 30

#define Zero(v) memset((v), 0, sizeof(v))


typedef unsigned int  u32;
typedef unsigned char uch;


//
// I/O
//
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
};


struct Hurdle {
    int lane, mark;
    Hurdle(int L, int M) : lane(L), mark(M) {}
    bool operator<(const Hurdle &x) const {
        if (mark != x.mark) return mark < x.mark;
        return lane < x.lane;
    }
};
typedef vector<Hurdle> HV;


//
// Hash Map
//
#define HASHB 32768
struct HM {
    struct Datum {
        static int sz;
        int lanes[MAXK];
        int mark;
        Datum(int M) : mark(M) {}
        Datum(int *L, int M) : mark(M) { memcpy(lanes, L, sz); }
        bool operator ==(const Datum &x) const {
            return memcmp(lanes, x.lanes, sz) == 0;
        }
    };
    typedef vector<Datum> DV; DV b[HASHB];
    u32 fnv_hash(const int *k, int len) const {
        uch *p = reinterpret_cast<uch*>(const_cast<int*>(k));
        u32 h = 2166136261U;
        for (int i = 0; i < len; ++i) h = (h * 16777619U ) ^ p[i];
        return h;
    }
    bool add(const Datum &k, int &dist) {
        int i = fnv_hash(k.lanes, k.sz) % HASHB;
        for (int j = 0, J = b[i].size(); j < J; ++j)
            if (b[i][j] == k) {
                int dif = k.mark - b[i][j].mark;
                if (dif > dist)
                    dist = dif;
                return false;
            }
        b[i].push_back(k);
        if (dist < 0) dist = 0;
        return true;
    }
};
int HM::Datum::sz = 0;


HV hs;          // collection of all hurdles
int hpl[MAXK];  // hurdles per lane
int L, K;


int solve()
{
    sort(hs.begin(), hs.end());
    Zero(hpl);

    int ans = -1;

    HM::Datum d(hpl, 0);

    HM hm;
    hm.add(d, ans);

    int max_hurdles = 0;

    for (int i = 0, I = hs.size(); i < I; ++i) {
        int curr_mark = hs[i].mark;

        d.mark = curr_mark;
        hm.add(d, ans);

        for (int j = i; j < I && hs[j].mark == curr_mark; ++j) {
            i = j;
            int lane = hs[j].lane;
            ++hpl[lane];
            if (hpl[lane] > max_hurdles)
                max_hurdles = hpl[lane];
        }

        ++d.mark;
        for (int j = 0; j < K; ++j)
            d.lanes[j] = max_hurdles - hpl[j];

        hm.add(d, ans);
    }

    d.mark = L;
    hm.add(d, ans);

    return ans;
}


int main()
{
    Reader rr;

    int ncase = 0;
    while (true) {
        L = rr.next_u32();
        K = rr.next_u32();

        if (L == 0 && K == 0) break;

        HM::Datum::sz = K * sizeof(int);

        hs.clear();
        for (int i = 0; i < K; ++i) {
            int n = rr.next_u32();

            while (n--) {
                int p = rr.next_u32();
                hs.push_back(Hurdle(i, p));
            }
        }

        printf("Case #%d: %d meter(s)\n", ++ncase, solve());
    }

    return 0;
}
