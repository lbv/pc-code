#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

#define MAXLEN 260

#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); ++v)

typedef vector<int> IV;
typedef IV::iterator IVi;

// I/O
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    bool has_next() { skip(); return b > 0; }
    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
};

// Big Integer
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct Bigint {
    IV d; bool sgn;
    Bigint(const char *s) {
        if (*s == '-') sgn = true, s++; else sgn = false;
        for (int end = strlen(s), i = max(0, end-BIDIG); true;) {
            int n = 0; for (int j=i; j != end; j++) n = n*10 + s[j] - '0';
            d.push_back(n); if (i == 0) break;
            end = i, i = max(0, i-BIDIG);
        } clean();
    }
    size_t len() const { return d.size(); }
    Bigint &operator*=(const Bigint &b) {
        int s1 = len(), s2 = b.len(), s3 = s1+s2;
        IV res(s3); int c = 0;
        for (int k=0; k < s3; k++) {
            int sum = c;
            for (int i=max(0,k-s2+1), I=min(k+1, s1), j=k-i; i < I; i++, j--)
                sum += d[i] * b.d[j];
            if (sum >= BIBAS) { c = sum / BIBAS; sum %= BIBAS; } else c = 0;
            res[k] = sum;
        }
        d = res; sgn ^= b.sgn; clean();
        return *this;
    }
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
    void println() {
        if (sgn) putchar('-');
        bool flg = true;
        crFor (IV, i, d) {
            if (flg) { printf("%d", *i); flg=false; }
            else printf(BIFMT, *i);
        } putchar('\n');
    }
};

char n1[MAXLEN + 1];
char n2[MAXLEN + 1];

int main()
{
    Reader rr;

    while (rr.has_next()) {
        rr.next(n1);
        rr.next(n2);

        Bigint a(n1);
        Bigint b(n2);

        a *= b;

        a.println();
    }

    return 0;
}
