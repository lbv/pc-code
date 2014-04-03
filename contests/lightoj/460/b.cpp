#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define RFor(t,i,c) for(t::reverse_iterator i=(c).rbegin(); i!=(c).rend(); ++i)


typedef vector<int> IV;
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
	BigInt(const char *s) {
		if (*s == '-') sgn = true, s++; else sgn = false;
		for (int end = strlen(s), i = max(0, end-BIDIG); true;) {
			int n = 0; for (int j=i; j != end; j++) n = n*10 + s[j] - '0';
			d.push_back(n); if (i == 0) break;
			end = i, i = max(0, i-BIDIG);
		} clean();
	}
	size_t len() const { return d.size(); }
	bool is_zero() const { return len() == 1 && d[0] == 0; }
	void flip() { sgn = !sgn; }
	BigInt neg() const { BigInt x = *this; x.flip(); return x; }
	void clean() {
		IVi i; for (i=d.end()-1; *i == 0 && i != d.begin(); i--);
		d.erase(i+1, d.end());
		if (sgn && is_zero()) sgn = false;
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


char A[64];
char B[64];

int main()
{
	int T;
	scanf("%d", &T);

	int ncase = 0;
	while (T--) {
		scanf("%s%s", A, B);
		BigInt a(A);
		BigInt b(B);
		printf("Case %d: ", ++ncase);
		a += b;
		a.print();
	}

	return 0;
}
