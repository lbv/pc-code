#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 1000

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)


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
    bool operator==(const Bigint &b) const {
        return sgn == b.sgn && d == b.d;
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
    int sum_digits() const {
        int sum = 0;
        cFor (IV, dig, d) {
            for (int x = *dig; x; x /= 10)
                sum += x % 10;
        }
        return sum;
    }
    void clean() {
        IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
        d.erase(i+1, d.end());
        if (sgn && d.size() == 1 && d[0] == 0) sgn = false;
    }
};



int sums[MAXN + 1];
int n;


void prepare()
{
    Bigint f(1);

    sums[0] = sums[1] = 1;

    for (int i = 2; i <= MAXN; ++i) {
        Bigint x(i);

        f *= x;
        sums[i] = f.sum_digits();
    }
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%d", &n) != 1) break;
        printf("%d\n", sums[n]);
    }

    return 0;
}
