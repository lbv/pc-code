#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <queue>
#include <stack>
using namespace std;


#if 0
#define MAXT 10
#define MAXN 1000
#define MAXX 100
#define NCRIT 2
#endif

#if 1
#define MAXT 20
#define MAXN 12
#define MAXX 100
#define NCRIT 2
#define NL 1
#endif


struct Data {
	stack<int> s;
	queue<int> q;
	priority_queue<int> pq;
	int t;

	Data(int T): t(T) {}

	void push(int x) {
		if (t == 0)
			s.push(x);
		else if (t == 1)
			q.push(x);
		else pq.push(x);
	}

	int pop() {
		int x;
		if (t == 0) { x = s.top(); s.pop(); }
		else if (t == 1) { x = q.front(); q.pop(); }
		else { x = pq.top(); pq.pop(); }
		return x;
	}

	bool is_empty() const {
		if (t == 0)
			return s.empty();
		if (t == 1)
			return q.empty();
		return pq.empty();
	}
};


int T;


void gen_rand(int n)
{
	while (n--) {
		int op = rand() % 2 + 1;
		int x = rand() % MAXX + 1;
		printf("%d %d\n", op, x);
	}
}

void gen(bool crit = false)
{
#if NL
	puts("");
#endif
	int n = crit ? MAXN : rand() % MAXN + 1;
	printf("%d\n", n);

	int t = rand() % 4;
	if (t == 3) { gen_rand(n); --T; return; }

	Data data(t);

	while (n--) {
		if (! data.is_empty() && rand() % 2 == 0) {
			int x = data.pop();
			printf("2 %d\n", x);
		}
		else {
			int x = rand() % MAXX + 1;
			printf("1 %d\n", x);
			data.push(x);
		}
	}

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
