#include <cstdio>
#include <cstring>

#define ALPHABET 10
#define WORDS	 10000
#define WORDLEN  10

#define Zero(v)    memset(v, 0, sizeof(v))
#define NonZero(v) (memcmp(v, _zero, sizeof(_zero)) != 0)

static const int _zero[ALPHABET] = {0};

struct Trie {
	struct Node {
		int children[ALPHABET];
		bool end;
	};
	int nxt;
	Node nodes[WORDS * WORDLEN];
	void init() { Zero(nodes); nxt = 1; }
	void insert(const char *s, bool &c) {
		int cur = 0;

		while (*s) {
			if (nodes[cur].end) { c = false; return; }

			int idx = *s - '0';
			if (! nodes[cur].children[idx])
				nodes[cur].children[idx] = nxt++;

			cur = nodes[cur].children[idx];
			++s;
		}

		if (NonZero(nodes[cur].children)) { c = false; return; }
		nodes[cur].end = true;
	}
};


Trie t;
char num[WORDLEN + 1];


int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		int n;
		scanf("%d", &n);

		t.init();
		bool consistent = true;

		while (n--) {
			scanf("%s", num);

			if (consistent)
				t.insert(num, consistent);
		}

		if (consistent) puts("YES");
		else puts("NO");
	}

	return 0;
}
