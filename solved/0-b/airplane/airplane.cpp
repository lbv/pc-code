#include <cstdio>

int n;
int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;
        puts("1/2");  // Seriously???
    }

    return 0;
}

#if 0
int gcd(int a, int b) { for (int c = a%b; c; a=b,b=c,c=a%b); return b; }

// Fraction
struct Fraction {
    int p, q;

    Fraction(int P, int Q) : p(P), q(Q) { simplify(); }
    Fraction(int P) : p(P), q(1) {}
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
    Fraction operator%(int m) const {
        return Fraction(p % (m*q), q);
    }
};

int n;

int main()
{
    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        Fraction f(1, n);
        Fraction s(1, n);

        for (int i = 2, d = n - 1; i <= n; ++i, --d) {
            f = s * Fraction(1, d);
            s = s + f;
        }

        printf("%d/%d\n", f.p, f.q);
    }

    return 0;
}
#endif
