#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <ctime>


#define MAXT 200
#define MAXDEPTH 16
#define MAXI 100000
#define MINI -100000
#define NCRIT 10

#define Clr(m) memset(m, 0, sizeof(m))

const int RangeI = MAXI - MINI + 1;


struct Tree {
	int v, lt, rt;
};


int T;
Tree nodes[1 << (MAXDEPTH+1)];


void gen_tree(int n, int d, bool crit)
{
	Tree &t = nodes[n];

	t.v = rand() % RangeI + MINI;

	if (d == MAXDEPTH) return;
	if (crit || rand() % 2 == 0) {
		t.lt = 2*n;
		gen_tree(2*n, d+1, crit);
	}
	if (crit || rand() % 2 == 0) {
		t.rt = 2*n+1;
		gen_tree(2*n+1, d+1, crit);
	}
}

int get_sum(int n)
{
	Tree &t = nodes[n];
	int s = t.v;

	if (t.lt == 0 && t.rt == 0) return s;

	int c;
	if (t.lt == 0) c = 1;
	else if (t.rt == 0) c = 0;
	else c = rand() % 2;

	if (c == 0) s += get_sum(t.lt);
	else s += get_sum(t.rt);

	return s;
}

void print_tree(int n)
{
	Tree &t = nodes[n];

	printf("( %d ", t.v);
	if (t.lt == 0) printf("()");
	else print_tree(t.lt);

	if (t.rt == 0) printf("()");
	else print_tree(t.rt);
	printf(" )");
}

void gen(bool crit = false)
{
	Clr(nodes);
	gen_tree(1, 1, crit);

	int s = rand() % RangeI + MINI;
	if (rand() % 2 == 0)
		s = get_sum(1);

	printf("%d ", s);
	print_tree(1);
	putchar('\n');

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
