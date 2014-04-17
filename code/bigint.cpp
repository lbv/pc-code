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
	BigInt &operator*=(const BigInt &b) {
		int s1 = len(), s2 = b.len(), s3 = s1+s2;
		IV res(s3); int c = 0;
		for (int k=0; k < s3; ++k) {
			int sum = c;
			c = 0;
			for (int i=max(0,k-s2+1), I=min(k+1, s1), j=k-i; i < I; ++i, --j) {
				sum += d[i] * b.d[j];
				if (sum >= BIBAS) c += sum / BIBAS, sum %= BIBAS;
			}
			res[k] = sum;
		}
		d = res; sgn ^= b.sgn; clean();
		return *this;
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
	int to_int() {
		int res = 0, p = 1;
		for (int i=0, I=len(); i < I; i++) { res += d[i] * p; p *= BIBAS; }
		return sgn ? -res : res;
	}
	BigInt operator+(const BigInt &x) const {
		BigInt ans = *this; ans += x; return ans; }
	BigInt operator-(const BigInt &x) const {
		BigInt ans = *this; ans -= x; return ans; }
	BigInt operator*(const BigInt &x) const {
		BigInt ans = *this; ans *= x; return ans; }
	BigInt operator/(const BigInt &x) const {
		BigInt ans = *this; ans /= x; return ans; }
	BigInt operator%(const BigInt &x) const {
		BigInt ans = *this; ans %= x; return ans; }
};

//
// 128-bit unsigned integer
//
struct U128 {
	u64 lo, hi;
	static const size_t sz	= 128;
	static const size_t hsz = 64;
	static const u64 bmax = -1;

	U128() : lo(0), hi(0) {}
	U128(int v) : lo(v), hi(0) {}

	U128 operator-() const { return ~U128(*this) + 1; }
	U128 operator~() const {
		U128 t(*this);
		t.lo = ~t.lo;
		t.hi = ~t.hi;
		return t;
	}

	U128 &operator+=(const U128 &b) {
		if (lo > bmax - b.lo) ++hi;
		lo += b.lo;
		hi += b.hi;
		return *this;
	}
	U128 &operator-=(const U128 &b) { return *this += -b; }
	U128 &operator*=(const U128 &b) {
		if (*this == 0 || b == 1) return *this;
		if (b == 0) { lo = hi = 0; return *this; }

		U128 a(*this);
		U128 t = b;

		lo = hi = 0;

		for (size_t i = 0; i < sz; ++i) {
			if((t & 1) != 0) *this += (a << i);
			t >>= 1;
		}
		return *this;
	}
	U128 &operator/=(const U128 &b) {
		U128 rem;
		divide(*this, b, *this, rem);
		return *this;
	}
	U128 &operator%=(const U128 &b) {
		U128 quo;
		divide(*this, b, quo, *this);
		return *this;
	}

	static void
	divide(const U128 &num, const U128 &den, U128 &quo, U128 &rem) {
		if(den == 0) { int a = 0; quo = U128(a/a); }
		U128 n = num, d = den, x = 1, ans = 0;

		while((n >= d) && (((d >> (sz - 1)) & 1) == 0)) {
			x <<= 1;
			d <<= 1;
		}

		while(x != 0) {
			if(n >= d) {
				n -= d;
				ans |= x;
			}

			x >>= 1;
			d >>= 1;
		}

		quo = ans, rem = n;
	}

	U128 &operator&=(const U128 &b) { hi &= b.hi; lo &= b.lo; return *this; }
	U128 &operator|=(const U128 &b) {
		hi |= b.hi;
		lo |= b.lo;
		return *this;
	}
	U128 &operator<<=(const U128& rhs) {
		size_t n = rhs.to_int();
		if (n >= sz) { lo = hi = 0; return *this; }

		if(n >= hsz) {
			n -= hsz;
			hi = lo;
			lo = 0;
		}

		if(n != 0) {
			hi <<= n;
			const u64 mask(~(u64(-1) >> n));
			hi |= (lo & mask) >> (hsz - n);
			lo <<= n;
		}

		return *this;
	}
	U128 &operator>>=(const U128& rhs) {
		size_t n = rhs.to_int();
		if (n >= sz) { lo = hi = 0; return *this; }

		if(n >= hsz) {
			n -= hsz;
			lo = hi;
			hi = 0;
		}

		if(n != 0) {
			lo >>= n;
			const u64 mask(~(u64(-1) << n));
			lo |= (hi & mask) << (hsz - n);
			hi >>= n;
		}

		return *this;
	}

	int to_int() const { return static_cast<int>(lo); }
	u64 to_u64() const { return lo; }

	bool operator==(const U128 &b) const { return hi == b.hi && lo == b.lo; }
	bool operator!=(const U128 &b) const { return !(*this == b); }
	bool operator<(const U128 &b) const {
		return (hi == b.hi) ? lo < b.lo : hi < b.hi; }
	bool operator>=(const U128 &b) const { return ! (*this < b); }
	U128 operator&(const U128 &b) const { U128 a(*this); return a &= b; }
	U128 operator<<(const U128 &b) const { U128 a(*this); return a <<= b; }
	U128 operator>>(const U128 &b) const { U128 a(*this); return a >>= b; }
	U128 operator*(const U128 &b) const { U128 a(*this); return a *= b; }
	U128 operator+(const U128 &b) const { U128 a(*this); return a += b; }
	U128 operator-(const U128 &b) const { U128 a(*this); return a -= b; }
	U128 operator%(const U128 &b) const { U128 a(*this); return a %= b; }
};
