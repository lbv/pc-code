#include <cstdio>


struct Reader {
    int b; Reader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32) read(); }

    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; 48<=b&&b<=57; read()) v = v*10 + b-48; return s ? -v : v; }
    char next_char() { skip(); char c = b; read(); return c; }
    bool has_next() { skip(); return b > 0; }
    bool has_next_int() { skip(); return b == 45 || (48 <= b && b <= 57); }
};


//
// Recursive Descent Parser
//

/**
 * Grammar:
 *
 *   tree ::= '(' ( | INT <tree> <tree> ) ')'
 */
enum TokenT {
	NONE,
	PAREN_OPEN,
	PAREN_CLOSE,
	INT
};

struct Token {
	TokenT t;
	int n;
	Token() {}
	Token(TokenT T): t(T) {}
	Token(TokenT T, int N): t(T), n(N) {}
};

struct Lexer {
	Reader &rr;
	bool has_tok;
	Token tok;
	Lexer(Reader &R): rr(R), has_tok(false) {}

	void read_token() {
		rr.skip();
		if (rr.has_next_int())
			tok = Token(INT, rr.next_int());
		else if (rr.has_next()) {
			char c = rr.next_char();
			switch (c) {
			case '(': tok = Token(PAREN_OPEN); break;
			case ')': tok = Token(PAREN_CLOSE); break;
			default: tok = Token(NONE);
			}
		}
		else
			tok = Token(NONE);

		has_tok = true;
	}

	TokenT peek() { if (! has_tok) read_token(); return tok.t; }
	Token pop() { if (! has_tok) read_token(); has_tok = false; return tok; }
};

struct TreeNode {
	bool empty, leaf, ok;
	TreeNode(): empty(true), leaf(false), ok(false) {}
};


struct Parser {
	Lexer lex;
	Parser(Reader &R): lex(Lexer(R)) {}

	TreeNode tree(int sum) {
		lex.pop(); // must be a PAREN_OPEN

		TreeNode ans;
		if (lex.peek() == INT) {
			ans.empty = false;
			Token tok = lex.pop();

			TreeNode lt = tree(sum - tok.n);
			TreeNode rt = tree(sum - tok.n);

			if (lt.empty && rt.empty) {
				ans.leaf = true;
				if (tok.n == sum) ans.ok = true;
			}
			else
				ans.ok = lt.ok || rt.ok;
		}

		lex.pop();  // must be a PAREN_CLOSE
		return ans;
	}
};


Reader rr;


int main()
{
	while (rr.has_next()) {
		int sum = rr.next_int();
		Parser parser(rr);
		if (parser.tree(sum).ok)
			puts("yes");
		else
			puts("no");
	}

	return 0;
}
