#include <cstdio>
#include <stack>
using namespace std;


#define MAX_MOVES 10
#define INF 100

#define GetFS(b) ((b) & -(b))
#define ClrFS(b) (b &= ~GetFS(b))


typedef unsigned u32;


const int moves[8][2] = {
	{ -2, -1 },
	{ -1, -2 },
	{  1, -2 },
	{  2, -1 },
	{  2,  1 },
	{  1,  2 },
	{ -1,  2 },
	{ -2,  1 }
};

u32 bit[5][5];


u32 final_board;

int popcount(u32 x)
{
	int c = 0;
	for (; x; ClrFS(x)) ++c;
	return c;
}

struct Board {
	u32 b;       // bitmask of the board
	int r, c;    // coordinates of the blank cell
	int pr, pc;  // previous coordinates, to avoid "going back"
	int _h;

	int m;  // current move

	Board() { pr=pc=-1;}
	Board(u32 B, int R, int C): b(B), r(R), c(C) { init(); pr=pc=-1; }

	void init() {
		u32 x = b | bit[r][c];
		u32 y = final_board | bit[r][c];

		if (r != 2 || c != 2) x |= bit[2][2];

		_h = popcount(x ^ y);
	}

	int h() { return _h; }

	bool is_solution() { return b == final_board; }

	bool valid_pos(int r, int c) {
		return 0 <= r && r < 5 && 0 <= c && c < 5;
	}

	bool next(Board &child, int &dist, int &delta) {
		bool can_move = false;

		int nr, nc;
		for (; (! can_move) && m < 8; ++m) {
			nr = r + moves[m][0];
			nc = c + moves[m][1];

			if (nr == pr && nc == pc) continue;

			if (valid_pos(nr, nc))
				can_move = true;
		}

		if (! can_move) return false;

		if (b & bit[nr][nc])
			child.b = (b & ~bit[nr][nc]) | bit[r][c];
		else
			child.b = b;

		child.r = nr;
		child.c = nc;
		child.pr = r;
		child.pc = c;
		child.init();

		dist = 1;
		delta = 1;

		return true;
	}

	void reset() { m = 0; }
};

typedef Board NodeT;
typedef int DeltaT;

bool ida_dls(NodeT &node, int depth, int g, int &nxt, stack<DeltaT> &st)
{
	if (g == depth) return node.is_solution();

	NodeT child;
	int dist;
	DeltaT delta;
	for (node.reset(); node.next(child, dist, delta);) {
		int f = g + dist + child.h();
		if (f > depth && f < nxt) nxt = f;
		if (f <= depth	&& ida_dls(child, depth, g + 1, nxt, st)) {
			st.push(delta);
			return true;
		}
	}
	return false;
}

bool ida_star(NodeT &root, int limit, stack<DeltaT> &st)
{
	for (int depth = root.h(); depth <= limit;) {
		int next_depth = INF;
		if (ida_dls(root, depth, 0, next_depth, st)) return true;
		if (next_depth == INF) return false;
		depth = next_depth;
	}
	return false;
}


char board[5][6];


int solve()
{
	u32 b = 0;
	int r = 0, c = 0;

	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j) {
			if (board[i][j] == ' ')
				r = i, c = j;
			else if (board[i][j] == '1')
				b |= bit[i][j];
		}

	stack<int> st;
	Board game(b, r, c);

	if (ida_star(game, MAX_MOVES, st))
		return st.size();

	return -1;
}

void prepare()
{
	for (int i = 0; i < 5; ++i)
		for (int j = 0; j < 5; ++j)
			bit[i][j] = 1 << (i*5 + j);

	final_board = 0;
	for (int i = 0; i < 4; ++i)
		for (int j = i + (i < 2 ? 0 : 1); j < 5; ++j)
			final_board |= bit[i][j];
}

int main()
{
	prepare();

	int N;
	scanf("%d", &N);
	gets(board[0]);  // skip NL

	while (N--) {
		for (int i = 0; i < 5; ++i) gets(board[i]);

		int ans = solve();
		if (ans < 0)
			printf("Unsolvable in less than %d move(s).\n", MAX_MOVES + 1);
		else
			printf("Solvable in %d move(s).\n", ans);
	}

	return 0;
}
