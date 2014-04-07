#include <cstdio>
#include <set>
using namespace std;


#define ABO_O 0
#define ABO_A 1
#define ABO_B 2

#define TYPE_O   0
#define TYPE_A   1
#define TYPE_B   2
#define TYPE_AB  3
#define TYPE_UNK 16

typedef unsigned int u32;


const u32 RH_BIT = 1 << 2;
const int MAX_BLOOD = 6 * 3;
const int MAX_TYPES = 1 << 3;


#define For(t,i,c) for(t::iterator i=(c).begin(); i != (c).end(); ++i)


struct Blood {
	int abo1, abo2;
	int rh1, rh2;

	u32 type;

	Blood() {}
	Blood(int a1, int a2, int r1, int r2):
		abo1(a1), abo2(a2), rh1(r1), rh2(r2) { init(); }

	void init() {
		if (abo1 == ABO_O && abo2 == ABO_O)
			type = TYPE_O;
		else if ((abo1 == ABO_A && abo2 == ABO_B) ||
		         (abo1 == ABO_B && abo2 == ABO_A))
		    type = TYPE_AB;
		else if (abo1 == ABO_A || abo2 == ABO_A)
			type = TYPE_A;
		else
			type = TYPE_B;

		if (rh1 || rh2)
			type |= RH_BIT;

		abo[0] = abo1;
		abo[1] = abo2;
		rh[0] = rh1;
		rh[1] = rh2;
	}

	int abo[2];
	int rh[2];
	int idx_abo, idx_rh;
	void reset() { idx_abo = idx_rh = 0; }
	bool next(int &a, int &r) {
		if (idx_abo >= 2) return false;

		a = abo[idx_abo];
		r = rh[idx_rh++];

		if (idx_rh >= 2) {
			idx_rh = 0;
			++idx_abo;
		}
		return true;
	}

	bool operator<(const Blood &b) const { return type < b.type; }
};
typedef set<Blood> SB;


Blood all[MAX_BLOOD];


SB parent_parent[MAX_TYPES][MAX_TYPES];
SB parent_child[MAX_TYPES][MAX_TYPES];

u32 b1, b2, b3;
char inp[8];


void prepare()
{
	int nblood = 0;
	for (int a = 0; a < 3; ++a)
		for (int b = a; b < 3; ++b)
			for (int c = 0; c < 2; ++c)
				for (int d = c; d < 2; ++d)
					all[nblood++] = Blood(a, b, c, d);

	for (int i = 0; i < nblood; ++i)
		for (int j = 0; j < nblood; ++j) {
			Blood a = all[i];
			Blood b = all[j];

			int abo1, rh1, abo2, rh2;
			for (a.reset(); a.next(abo1, rh1);)
				for (b.reset(); b.next(abo2, rh2);) {

					Blood c(abo1, abo2, rh1, rh2);

					parent_parent[a.type][b.type].insert(c);
					parent_child[a.type][c.type].insert(b);
					parent_child[b.type][c.type].insert(a);
				}

		}
}

void print_type(u32 type)
{
	u32 t = type & ((1 << 2) - 1);
	if (t == TYPE_O)
		putchar('O');
	else if (t == TYPE_A)
		putchar('A');
	else if (t == TYPE_B)
		putchar('B');
	else
		printf("AB");

	if (type & RH_BIT)
		putchar('+');
	else
		putchar('-');
}

void print_unknown(const SB &possible)
{
	if (possible.size() == 0) {
		printf("IMPOSSIBLE");
		return;
	}

	if (possible.size() == 1) {
		print_type(possible.begin()->type);
		return;
	}

	putchar('{');
	int i = 0;
	For (SB, blood, possible) {
		if (i++ > 0) printf(", ");
		print_type(blood->type);
	}
	putchar('}');
}

void solve()
{
	if (b1 == TYPE_UNK)
		print_unknown(parent_child[b2][b3]);
	else
		print_type(b1);

	putchar(' ');

	if (b2 == TYPE_UNK)
		print_unknown(parent_child[b1][b3]);
	else
		print_type(b2);

	putchar(' ');

	if (b3 == TYPE_UNK)
		print_unknown(parent_parent[b1][b2]);
	else
		print_type(b3);

	putchar('\n');
}

bool read_blood(u32 &b)
{
	scanf("%s", inp);
	if (inp[0] == 'E') return false;

	if (inp[0] == '?')
		b = TYPE_UNK;
	else if (inp[1] == 'B') {
		b = TYPE_AB;
		if (inp[2] == '+')
			b |= RH_BIT;
	}
	else {
		if (inp[0] == 'A')
			b = TYPE_A;
		else if (inp[0] == 'B')
			b = TYPE_B;
		else
			b = TYPE_O;

		if (inp[1] == '+')
			b |= RH_BIT;
	}

	return true;
}

int main()
{
	prepare();

	int ncase = 0;
	while (true) {
		if (! read_blood(b1)) break;
		read_blood(b2);
		read_blood(b3);

		printf("Case %d: ", ++ncase);
		solve();
	}

	return 0;
}
