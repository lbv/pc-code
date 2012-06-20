#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;

typedef long long i64;

typedef vector<int>  IV;
typedef IV::iterator IVi;

#define MAXLEN 105

#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); ++v)

// Big Integer
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct Bigint {
    IV d; bool sgn;
    Bigint(i64 n=0) {
        if (n < 0) sgn = true, n = -n; else sgn = false;
        if (n < BIBAS) d.push_back(n);
        else while (n != 0) { d.push_back(n % BIBAS); n /= BIBAS; }
    }
    Bigint(const char *s) {
        if (*s == '-') sgn = true, s++; else sgn = false;
        for (int end = strlen(s), i = max(0, end-BIDIG); true;) {
            int n = 0; for (int j=i; j != end; j++) n = n*10 + s[j] - '0';
            d.push_back(n); if (i == 0) break;
            end = i, i = max(0, i-BIDIG);
        } clean();
    }
    size_t len() const { return d.size(); }
    bool operator==(const Bigint &b) const {
        return sgn == b.sgn && d == b.d;
    }
    bool operator<(const Bigint &b) const {
        if (sgn && !b.sgn) return true;
        if ((!sgn) && b.sgn) return false;
        if (d.size() < b.d.size()) return true;
        if (d.size() > b.d.size()) return false;
        for (int i = d.size() - 1; i >= 0; --i) {
            if (d[i] < b.d[i]) return true;
            else if (d[i] > b.d[i]) return false;
        }
        return false;
    }
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
    Bigint pow(int e) {
        if (e == 0) return Bigint(1);
        if (e == 1) return *this;
        if (e % 2 == 0) {
            Bigint tmp = this->pow(e/2);
            tmp *= tmp;
            return tmp;
        }
        Bigint tmp = this->pow(e-1);
        tmp *= *this;
        return tmp;
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

int n;
char p_str[MAXLEN + 1];

void solve()
{
    Bigint p(p_str);

    int lo = 1;
    int hi = 1000000000;

    while (true) {
        int mid = (hi + lo) / 2;

        Bigint k(mid);

        Bigint e = k.pow(n);

        if (e == p) {
            k.println();
            return;
        }

        if (e < p)
            lo = mid == lo ? mid + 1 : mid;
        else
            hi = mid == hi ? mid - 1 : mid;
    }
}

int main()
{
    while (true) {
        if (scanf("%d%s", &n, p_str) != 2) break;

        solve();
    }

    return 0;
}
