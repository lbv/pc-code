#include <cstdio>
#include <vector>
using namespace std;


#define MAXN 366

#define RFor(t,v,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)


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
    void get_freq(IV &f) {
        f = IV(10);

        bool first = true;
        RFor (IV, i, d) {
            int seg = *i;
            if (first) {
                while (seg != 0) {
                    ++f[seg % 10];
                    seg /= 10;
                }
                first = false;
            }
            else
                for (int j = 0; j < BIDIG; ++j) {
                    ++f[seg % 10];
                    seg /= 10;
                }
        }
    }
};


int n;
IV freq[MAXN + 1];


void prepare()
{
    Bigint fac(1);
    for (int i = 1; i <= MAXN; ++i) {
        Bigint bi(i);
        fac *= bi;

        fac.get_freq(freq[i]);
    }
}

int main()
{
    prepare();

    while (true) {
        scanf("%d", &n);
        if (n == 0) break;

        printf("%d! --\n", n);
        for (int i = 0; i <= 4; ++i) {
            if (i > 0) putchar(' ');
            printf("   (%d)%5d", i, freq[n][i]);
        }
        putchar('\n');
        for (int i = 5; i <= 9; ++i) {
            if (i > 5) putchar(' ');
            printf("   (%d)%5d", i, freq[n][i]);
        }
        putchar('\n');
    }

    return 0;
}
