#include <algorithm>
#include <cstdio>
#include <string>
#include <vector>
using namespace std;

#define cFor(t,v,c)  for(t::const_iterator v=c.begin(); v != c.end(); ++v)

#define MAXT 500

int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

// Fraction
struct Fraction {
    int p, q;

    Fraction(int P, int Q) : p(P), q(Q) { simplify(); }
    Fraction(int P) : p(P), q(1) {}
    Fraction() {}
    void simplify() {
        int g = gcd(p, q);
        p /= g;
        q /= g;
    }
    Fraction operator+(const Fraction &f) const {
        return Fraction(p * f.q + q * f.p, q * f.q);
    }
    Fraction operator-(const Fraction &f) const {
        return Fraction(p * f.q - q * f.p, q * f.q);
    }
    Fraction operator*(const Fraction &f) const {
        return Fraction(p * f.p, q * f.q);
    }
    Fraction operator/(const Fraction &f) const {
        return Fraction(p * f.q, q * f.p);
    }
    Fraction operator*(int n) const {
        return Fraction(p * n, q);
    }
    Fraction operator%(int m) const {
        return Fraction(p % (m*q), q);
    }
    bool operator<(const Fraction &f) const { return p*f.q < f.p*q; }
    bool operator==(int n) const { return p == n*q; }
    bool operator<=(int n) const { return p <= n*q; }
    bool operator>=(int n) const { return p >= n*q; }
};

typedef vector<Fraction> FV;

int read_time()
{
    int h, m, s;
    scanf("%d:%d:%d", &h, &m, &s);

    return h*3600 + m*60 + s;
}

void print_time(const Fraction &t)
{
    printf("%02d:%02d:%02d", t.p / (3600*t.q), t.p / (60*t.q) % 60,
           t.p/t.q % 60);

    Fraction sec(t.p % t.q, t.q);
    if (sec.p != 0)
        printf(" %d/%d", sec.p, sec.q);
    puts("");
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        int sym = read_time();
        int str = read_time();
        int end = read_time();

        FV sol;
        Fraction x;

        Fraction f1(360, 43200);
        Fraction f2(360, 3600);

        for (int i = 0; i < 13; ++i) {
            x = (f1 * 2 * sym + f2 * 3600 * i) / (f1 + f2) % 43200;
            if (x >= str && x <= end)
                sol.push_back(x);
        }

        printf("Case %d: %d\n", ++ncase, sol.size());

        sort(sol.begin(), sol.end());
        cFor (FV, t, sol)
            print_time(*t);
    }

    return 0;
}
