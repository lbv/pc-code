#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
using namespace std;


#if 0
#define MAXT 100
#define MAXNODES 50
#define NCRIT 8
#endif

#if 1
#define MAXT 20
#define MAXNODES 10
#define NCRIT 2
#endif


enum Token {
	OP_AND,
	OP_OR,
	OP_NOT,
	PAREN,
	VAR
};

struct Node {
	Token t;
	char var;

	int lt, rt;
};
Node nodes[MAXNODES];
int nnodes;


int T;


int gen_exp(int n)
{
	int t = -1;
	while (t < 0) {
		t = rand() % 5;

		if (t <= 1 && n < 3) t = -1;
		else if (t <= 3 && n < 2) t = -1;
	}

	int idx = nnodes++;
	Node &cur = nodes[idx];

	int x, y;
	switch (t) {
	case 0:
		cur.t = OP_AND;
		x = rand() % (n - 2) + 1;
		y = n - x - 1;
		cur.lt = gen_exp(x);
		cur.rt = gen_exp(y);
		break;

	case 1:
		cur.t = OP_OR;
		x = rand() % (n - 2) + 1;
		y = n - x - 1;
		cur.lt = gen_exp(x);
		cur.rt = gen_exp(y);
		break;

	case 2:
		cur.t = OP_NOT;
		cur.lt = gen_exp(n-1);
		break;

	case 3:
		cur.t = PAREN;
		cur.lt = gen_exp(n-1);
		break;

	case 4:
		cur.t = VAR;
		cur.var = 'a' + (rand() % 10);
		break;
	}
	return idx;
}

void print_exp(int idx)
{
	Node &cur = nodes[idx];

	switch (cur.t) {
	case OP_AND:
		print_exp(cur.lt);
		putchar('&');
		print_exp(cur.rt);
		break;

	case OP_OR:
		print_exp(cur.lt);
		putchar('|');
		print_exp(cur.rt);
		break;

	case OP_NOT:
		putchar('!');
		print_exp(cur.lt);
		break;

	case PAREN:
		putchar('(');
		print_exp(cur.lt);
		putchar(')');
		break;

	case VAR:
		putchar(cur.var);
		break;
	}
}

int gen_exp_base(bool crit)
{
	int n = crit ? MAXNODES : rand() % MAXNODES + 1;
	nnodes = 0;
	return gen_exp(n);
}

void mod_exp(int idx)
{
	Node &cur = nodes[idx];

	switch (cur.t) {
	case OP_AND:
	case OP_OR:
		if (rand() % 2 == 0)
			swap(cur.lt, cur.rt);
		mod_exp(cur.lt);
		mod_exp(cur.rt);
		break;

	case OP_NOT:
		if (nodes[cur.lt].t == OP_NOT && rand() % 2 == 0)
			cur = nodes[ nodes[cur.lt].lt ];
		break;

	case PAREN:
		if (rand() % 4 == 0)
			cur = nodes[cur.lt];
		break;

	default:
		break;
	}
}

void gen(bool crit = false)
{
	int exp = gen_exp_base(crit);
	print_exp(exp);
	puts("");

	if (rand() % 5 == 0)
		exp = gen_exp_base(crit);
	else
		mod_exp(exp);

	print_exp(exp);
	puts("");

	--T;
}

int main()
{
	srand(time(NULL));

	T = MAXT;
	printf("%d\n", T);

	for (int i = 0; i < NCRIT; ++i) gen(true);
	while (T) gen();

	return 0;
}
