#include <cstdio>
#include <cstring>
#include <string>
#include <vector>
using namespace std;


#define MAXRWIDTH 6

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
    string to_string() {
        char buf[BIDIG+1]; string str;
        if (sgn) str.push_back('-');
        bool flg = true;
        RFor (IV, i, d) {
            if (flg) { sprintf(buf, "%d", *i); flg=false; }
            else sprintf(buf, BIFMT, *i);
            str.append(buf);
        }
        return str;
    }
};


template<typename TB, typename TE>
TB sq_pow(TB b, TE e) {
    TB res = 1; for (; e; e >>= 1, b *= b) if (e & 1) res *= b;
    return res;
}


char r_str[MAXRWIDTH + 1];
int  n;
int  pow10[MAXRWIDTH + 1];  // pow10[i] = 10^i


void solve()
{
    char *end = strchr(r_str, '\0');
    char *dot = strchr(r_str, '.');

    // R = x * 10^(-e)
    int x, e;

    if (dot == NULL || dot == end - 1) {
        sscanf(r_str, "%d", &x);
        e = 0;
    }
    else {
        int y;
        sscanf(r_str, "%d.%d", &x, &y);
        e = end - dot - 1;
        x = x * pow10[e] + y;
    }

    Bigint x_e = sq_pow(Bigint(x), n);
    string s = x_e.to_string();

    e *= n;

    int len = s.size();
    int a = 0, b = len - 1;

    for (; len > e; --len, ++a)
        putchar(s[a]);

    putchar('.');

    for (; e > len; --e) putchar('0');

    for (; len > 0 && s[b] == '0'; --b, --len) ;
    for (; a <= b; ++a) putchar(s[a]);

    putchar('\n');
}

void prepare()
{
    pow10[0] = 1;
    for (int i = 1; i <= MAXRWIDTH; ++i)
        pow10[i] = pow10[i - 1] * 10;
}

int main()
{
    prepare();

    while (true) {
        if (scanf("%s%d", r_str, &n) != 2) break;
        solve();
    }

    return 0;
}
