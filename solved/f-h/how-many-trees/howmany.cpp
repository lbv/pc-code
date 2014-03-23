#include <cstdio>
#include <vector>
using namespace std;

#define MAXCAT 1000

#define crFor(t,v,c) \
    for(t::const_reverse_iterator v=c.rbegin(); v != c.rend(); ++v)


typedef vector<int> IV;
typedef IV::iterator IVi;


int i;

//
// Big Integer
//
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct Bigint {
    IV d; bool sgn;
    Bigint(int n=0) {
        if (n < 0) sgn = true, n = -n; else sgn = false;
        if (n < BIBAS) d.push_back(n);
        else while (n != 0) { d.push_back(n % BIBAS); n /= BIBAS; }
    }
    size_t len() const { return d.size(); }
    bool is_zero() const { return len() == 1 && d[0] == 0; }
    void flip() { sgn = !sgn; }
    Bigint neg() const { Bigint x = *this; x.flip(); return x; }
    bool operator<(const Bigint &b) const {
        if (sgn != b.sgn) return sgn;
        if (len() != b.len()) return sgn ^ (len() < b.len());
        for (int i = len() - 1; i >= 0; --i)
            if (d[i] != b.d[i]) return sgn ^ (d[i] < b.d[i]);
        return false;
    }
    Bigint &operator*=(const Bigint &b) {
        int s1 = len(), s2 = b.len(), s3 = s1+s2;
        IV res(s3); int c = 0;
        for (int k=0; k < s3; ++k) {
            int sum = c;
            for (int i=max(0,k-s2+1), I=min(k+1, s1), j=k-i; i < I; ++i, --j)
                sum += d[i] * b.d[j];
            if (sum >= BIBAS) { c = sum / BIBAS; sum %= BIBAS; } else c = 0;
            res[k] = sum;
        }
        d = res; sgn ^= b.sgn; clean();
        return *this;
    }
    Bigint &short_div(int b) {
        for (int r = 0, i = len() - 1; i >= 0; --i)
            r = r*BIBAS + d[i], d[i] = r / b, r %= b;
        clean(); return *this;
    }
    Bigint &operator/=(const Bigint &b) {
        if (b.is_zero()) { int x=0; return *this=Bigint(x/x); }
        sgn ^= b.sgn; size_t l = len(), n = b.len();
        if (n == 1) return short_div(b.d[0]);
        if (l < n || (l == n && d.back() < b.d.back()))
            return *this = Bigint(0);
        Bigint r(0); IV res(l);
        for (int i = l - 1; i >= 0; --i) {
            r.d.insert(r.d.begin(), d[i]); r.clean();
            int x = r.len() >= n ? r.d[n-1] : 0;
            if (r.len() > n) x += BIBAS * r.d[n];
            int q = x / b.d[n-1];
            Bigint g = b; g *= Bigint(q);
            while (r < g) g -= b, --q;
            res[i] = q, r -= g;
        }
        d = res; clean(); return *this;
    }
    Bigint &operator+=(const Bigint &b) {
        int s1 = len(), s2 = b.len(), s3 = max(s1, s2) + 1;
        IV res(s3); int c = 0;
        for (int i = 0; i < s3; ++i) {
            int sum = c;
            sum += i < s1 ? d[i] : 0;
            sum += i < s2 ? b.d[i] : 0;
            if (sum >= BIBAS) { c = sum / BIBAS; sum %= BIBAS; } else c = 0;
            res[i] = sum;
        }
        d = res; clean();
        return *this;
    }
    Bigint &operator-=(const Bigint &b) {
        if (sgn != b.sgn) { (*this) += b.neg(); return *this; }
        if (*this < b) { Bigint x = b; x -= *this; return *this = x.neg(); }
        int s1 = len(), s2 = b.len(), s3 = s1;
        IV res(s3); int c = 0;
        for (int i = 0; i < s3; ++i) {
            int sum = d[i] - (i < s2 ? b.d[i] : 0) - c;
            if (sum < 0) { sum += BIBAS; c = 1; } else c = 0;
            res[i] = sum;
        }
        d = res; clean();
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

Bigint catalan[MAXCAT + 1];
void find_catalan()
{
    catalan[0] = 1;
    for (int i = 1; i <= MAXCAT; ++i) {
        catalan[i] = catalan[i - 1];
        catalan[i] *= Bigint(4*i - 2);
        catalan[i] /= Bigint(i + 1);
    }
}

int main()
{
    find_catalan();

    while (true) {
        if (scanf("%d", &i) != 1) break;

        catalan[i].println();
    }

    return 0;
}
