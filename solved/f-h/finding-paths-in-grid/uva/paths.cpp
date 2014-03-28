#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;


#define MOD 1000000007

const int MAX_STATES = 35;		// max number of configurations of a row (7C4)
const int STATE_MEM  = 1 << 7;	// memory to store states (12 bits)


#define Clr(m) memset((m), 0, sizeof(m))
#define Neg(m) memset((m), -1, sizeof(m))


typedef unsigned int u32;
typedef long long i64;
typedef int MatrixT;


#define MAX_ROWS MAX_STATES
#define MAX_COLS MAX_STATES
struct Matrix {
	int r, c;
	MatrixT m[MAX_ROWS][MAX_COLS];

	void init(int R, int C) { r = R, c = C; }
	void iden() { Clr(m); for (int i = 0; i < r; ++i) m[i][i] = 1; }
	void print() {
		for (int i = 0; i < r; ++i) {
			for (int j = 0; j < c; ++j) printf("%3d ", m[i][j]);
			puts("");
		}
	}

	MatrixT x[MAX_ROWS][MAX_COLS];
	Matrix &operator*=(const Matrix &y) {
		Clr(x); i64 v;
		for (int i = 0; i < r; ++i)
			for (int j = 0; j < c; ++j) {
				v = 0;
				for (int k = 0; k < c; ++k) {
					v += 1LL * m[i][k] * y.m[k][j];
					if (v >= MOD) v %= MOD;
				}
				x[i][j] = v;
			}
		memcpy(m, x, sizeof(m)); return *this;
	}
};

template<typename T>
void matrix_pow(Matrix &b, T e, Matrix &res) {
	res.init(b.r, b.c);	res.iden(); if (e == 0) return;
	while (true) {
		if (e & 1) res *= b;
		if ((e >>= 1) == 0) break;
		b *= b;
	}
}


int N;
Matrix mat, matp;

// states[b]: the step incremental index for state b (bitmask)
int stidx[STATE_MEM];
int nstates;


void decode(u32 s, int *p)
{
	int cnt = 0;
	for (int i = 0; i < 7; ++i)
		if (s & (1 << i))
			p[cnt++] = i;
}

u32 encode(int *p)
{
	u32 ans = 0;
	for (int i = 0; i < 4; ++i)
		ans |= 1 << p[i];
	return ans;
}

bool is_valid(int *p)
{
	for (int i = 0; i < 4; ++i) {
		if (p[i] < 0 || p[i] > 6) return false;

		for (int j = 0; j < i; ++j)
			if (p[i] == p[j]) return false;
	}
	return true;
}

void dfs(u32 s)
{
	int p[4], q[4];
	decode(s, p);

	int i = stidx[s];
	for (int a = -1; a <= 1; a += 2)
		for (int b = -1; b <= 1; b += 2)
			for (int c = -1; c <= 1; c += 2)
				for (int d = -1; d <= 1; d += 2) {
					q[0] = p[0] + a;
					q[1] = p[1] + b;
					q[2] = p[2] + c;
					q[3] = p[3] + d;

					if (! is_valid(q)) continue;
					u32 sp = encode(q);

					if (stidx[sp] < 0) {
						stidx[sp] = nstates++;
						dfs(sp);
					}
					mat.m[i][stidx[sp]] = 1;
				}
}

int solve(u32 s1)
{
	if (N == 1) return 1;

	Clr(mat.m);
	Neg(stidx);

	stidx[s1] = 0;
	nstates = 1;

	// fill matrix
	dfs(s1);
	mat.init(nstates, nstates);

	matrix_pow(mat, N - 1, matp);

	i64 res = 0;
	for (int i = 0; i < nstates; ++i)
		res += matp.m[0][i];

	return res % MOD;
}

int main()
{
	int T;
	scanf("%d", &T);

	while (T--) {
		scanf("%d", &N);

		u32 state = 0;
		for (int i = 0, p; i < 7; ++i) {
			scanf("%d", &p);
			if (p > 0)
				state |= 1 << i;
		}

		printf("%d\n", solve(state));
	}

	return 0;
}
