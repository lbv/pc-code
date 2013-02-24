#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXI 1000
#define MAXJ 1000
#define EPS  (1e-9)

#define Zero(v) memset((v), 0, sizeof(v))
#define RFor(t,i,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)


typedef vector<int>  IV;
typedef IV::iterator IVi;


//
// Big Integer
//
#define BIBAS 1000
#define BIDIG 3
#define BIFMT "%03d"
struct BigInt {
    IV d; bool sgn;
    BigInt(int n=0) {
        if (n < 0) sgn = true, n = -n; else sgn = false;
        if (n < BIBAS) d.push_back(n);
        else while (n != 0) { d.push_back(n % BIBAS); n /= BIBAS; }
    }
    size_t len() const { return d.size(); }
    bool is_zero() const { return len() == 1 && d[0] == 0; }
    void flip() { sgn = !sgn; }
    BigInt neg() const { BigInt x = *this; x.flip(); return x; }
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
    bool operator==(const BigInt &b) const {
        return sgn == b.sgn && d == b.d;
    }
    bool operator<(const BigInt &b) const {
        if (sgn != b.sgn) return sgn;
        if (len() != b.len()) return sgn ^ (len() < b.len());
        for (int i = len() - 1; i >= 0; --i)
            if (d[i] != b.d[i]) return sgn ^ (d[i] < b.d[i]);
        return false;
    }
    BigInt &operator+=(const BigInt &b) {
        if (sgn != b.sgn) { (*this) -= b.neg(); return *this; }
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
    BigInt &operator-=(const BigInt &_b) {
        if (sgn != _b.sgn) { (*this) += _b.neg(); return *this; }
        bool sbk = sgn; sgn = false; BigInt b = _b.sgn ? _b.neg() : _b;
        if (*this < b) {
            b -= *this; *this = sbk ? b : b.neg(); return *this; }
        int s1 = len(), s2 = b.len(), s3 = s1;
        IV res(s3); int c = 0;
        for (int i = 0; i < s3; ++i) {
            int sum = d[i] - (i < s2 ? b.d[i] : 0) - c;
            if (sum < 0) { sum += BIBAS; c = 1; } else c = 0;
            res[i] = sum;
        }
        d = res; sgn = sbk; clean();
        return *this;
    }
    BigInt &operator*=(const BigInt &b) {
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
    BigInt &short_div(int b) {
        for (int r = 0, i = len() - 1; i >= 0; --i)
            r = r*BIBAS + d[i], d[i] = r / b, r %= b;
        clean(); return *this;
    }
    BigInt &operator/=(const BigInt &b) {
        if (b.is_zero()) { int x=0; return *this=BigInt(x/x); }
        sgn ^= b.sgn; size_t l = len(), n = b.len();
        if (n == 1) return short_div(b.d[0]);
        if (l < n || (l == n && d.back() < b.d.back()))
            return *this = BigInt(0);
        BigInt r(0); IV res(l);
        for (int i = l - 1; i >= 0; --i) {
            r.d.insert(r.d.begin(), d[i]); r.clean();
            int x = r.len() >= n ? r.d[n-1] : 0;
            if (r.len() > n) x += BIBAS * r.d[n];
            int q = x / b.d[n-1];
            BigInt g = b; g *= BigInt(q);
            while (r < g) g -= b, --q;
            res[i] = q, r -= g;
        }
        d = res; clean(); return *this;
    }
    void print(bool nl = true) {
        if (sgn) putchar('-');
        bool flg = true;
        RFor (IV, i, d) {
            if (flg) { printf("%d", *i); flg=false; }
            else printf(BIFMT, *i);
        }
        if (nl) putchar('\n');
    }
};


double p, q;
int    N;

double P[MAXI + 1][MAXJ + 1];
bool   vis[MAXI + 1][MAXJ + 1];

BigInt calls;

BigInt fact[MAXI + MAXJ + 1];


void calc_p(int i, int j)
{
    if (vis[i][j]) return;

    double &ans = P[i][j];

    if (i == 0 && j == 0)
        ans = -1;
    else if (i == 0)
        ans = 1;
    else if (j == 0)
        ans = 0;
    else {
        calc_p(i - 1, j);
        calc_p(i, j - 1);
        ans = p*P[i-1][j] + q*P[i][j-1];
    }

    vis[i][j] = true;
}

void calc_calls(int i, int j)
{
    if (i == 0 && j == 0) { calls = 0; return; }
    calls = fact[i + j];
    BigInt den = fact[i];
    den *= fact[j];
    calls /= den;
    calls *= 2;
    calls -= 2;
}

void prepare()
{
    fact[0] = 1;
    for (int i = 1, I = MAXI + MAXJ; i <= I; ++i) {
        fact[i] = i;
        fact[i] *= fact[i - 1];
    }
}

int main()
{
    prepare();

    bool first = true;
    while (true) {
        scanf("%lf %d", &p, &N);
        if (N == 0) break;

        q = 1 - p;
        if (first) first = false;
        else       putchar('\n');

        Zero(vis);
        while (N--) {
            int i, j;
            scanf("%d%d", &i, &j);
            calc_p(i, j);
            calc_calls(i, j);

            printf("%.5lf\n", P[i][j] + EPS);
            calls.print();
        }
    }

    return 0;
}
