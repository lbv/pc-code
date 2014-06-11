#include <cstdio>
#include <cstring>


#define Neg(m) memset(m, -1, sizeof(m))


typedef unsigned char u8;
typedef unsigned int u32;


//
// Hash Map
//
struct HashT {
	int k, v;

	HashT() {}
	HashT(int K, int V): k(K), v(V) {}

	bool operator==(const HashT &x) const { return k == x.k; }
};
#define HASHB (1<<15)
#define HASHN 1000000
#define HASHT_SZ (sizeof(int))
#define HASHT_PTR(x) (reinterpret_cast<u8*>(&( (x).k )))
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
	HashT *add(HashT &h, bool &found) {
		int b = fnv_hash(HASHT_PTR(h), HASHT_SZ) % HASHB;
		for (int i = buckets[b]; i >= 0; i = next[i])
			if (data[i] == h) { found = true; return &data[i]; }
		found = false, next[n] = buckets[b], buckets[b] = n, data[n] = h;
		return &data[n++];
	}
};


int n, ans, last;
HashMap hm;


void init()
{
	hm.init();
	ans = 0;
	last = 0;
}

void process(int x, int i)
{
	HashT h(x, i);
	bool found;
	HashT *stored = hm.add(h, found);

	if (found) {
		if (stored->v > last) last = stored->v;
		stored->v = i;
	}
	int grp = i - last;
	if (grp > ans) ans = grp;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &n);
		init();

		for (int i = 1; i <= n; ++i) {
			int num;
			scanf("%d", &num);
			process(num, i);
		}

		printf("%d\n", ans);
	}

	return 0;
}
