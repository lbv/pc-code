#include <cstdio>
#include <cstring>


#define Neg(m) memset(m, -1, sizeof(m))


typedef unsigned char u8;
typedef unsigned int u32;


struct Reader {
	int b; Reader() { read(); }
	void read() { b = getchar_unlocked(); }
	void skip() { while (0 <= b && b <= 32) read(); }

	u32 next_u32() {
		u32 v=0; for (skip(); 48<=b&&b<=57; read()) v = 10*v+b-48; return v; }
};


//
// Hash Map
//
typedef u32 HashT;
#define HASHB (1<<15)
#define HASHN 2000000
#define HASHT_SZ (sizeof(u32))
#define HASHT_PTR(x) (reinterpret_cast<u8*>(&( (x) )))
struct HashMap {
	HashT data[HASHN];
	int next[HASHN];
	int buckets[HASHB];
	int n;

	void init() { Neg(buckets); n = 0; }
	u32 fnv_hash(const u8 *p, int n) const {
		u32 h = 2166136261U;
		for (int i = 0; i < n; ++i) h = (h * 16777619U) ^ p[i];
		return h;
	}
	void add(HashT &h) {
		int b = fnv_hash(HASHT_PTR(h), HASHT_SZ) % HASHB;
		next[n] = buckets[b], buckets[b] = n, data[n++] = h;
	}
	bool find(HashT &h) {
		int b = fnv_hash(HASHT_PTR(h), HASHT_SZ) % HASHB;
		for (int i = buckets[b]; i >= 0; i = next[i])
			if (data[i] == h) return true;
		return false;
	}
};


int N, M;
HashMap hm;


int main()
{
	Reader rr;

	while (true) {
		N = rr.next_u32();
		M = rr.next_u32();
		if (N == 0 && M == 0) break;

		hm.init();

		while (N--) {
			u32 n = rr.next_u32();
			hm.add(n);
		}

		int ans = 0;
		while (M--) {
			u32 n = rr.next_u32();
			if (hm.find(n)) ++ans;
		}

		printf("%d\n", ans);
	}

	return 0;
}
