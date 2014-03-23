#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXX 10000
#define MAXZ 100

#define RFor(t,i,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)


typedef vector<int>  IV;
typedef IV::iterator IVi;


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
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
    bool operator<(const Bigint &b) const {
        if (sgn != b.sgn) return sgn;
        if (len() != b.len()) return sgn ^ (len() < b.len());
        for (int i = len() - 1; i >= 0; --i)
            if (d[i] != b.d[i]) return sgn ^ (d[i] < b.d[i]);
        return false;
    }
    Bigint &operator+=(const Bigint &b) {
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
    void println() {
        if (sgn) putchar('-');
        bool flg = true;
        RFor (IV, i, d) {
            if (flg) { printf("%d", *i); flg=false; }
            else printf(BIFMT, *i);
        } putchar('\n');
    }
};
typedef vector<Bigint> BIV;


int N;
char X[MAXX + 1];
char Z[MAXZ + 1];
int lx, lz;


void solve()
{
    // dp[i]: Number of subsequences (Z1, Z2, ..., Zi)
    BIV dp(lz + 1);
    dp[0] = Bigint(1);

    for (int i = 0; i < lx; ++i)
        for (int j = lz - 1; j >= 0; --j)
            if (X[i] == Z[j])
                dp[j + 1] += dp[j];

    dp[lz].println();
}

int main()
{
    scanf("%d ", &N);
    while (N--) {
        gets(X);
        gets(Z);
        lx = strlen(X);
        lz = strlen(Z);
        solve();
    }

    return 0;
}
