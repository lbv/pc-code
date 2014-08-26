//
// Recursive Descent Parser
//

/**
 * Example Grammar:
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
};

struct Lexer {
	Reader &rr;
	bool has_tok;
	Token tok;
	Lexer(Reader &R): rr(R), has_tok(false) {}

	void read_token() {
		if (rr.has_next_int())
			tok = (Token) { INT, rr.next_int() };
		else if (rr.has_next()) {
			char c = rr.next_char();
			switch (c) {
			case '(': tok = (Token) { PAREN_OPEN }; break;
			case ')': tok = (Token) { PAREN_CLOSE }; break;
			default: tok = (Token) { NONE };
			}
		}
		else
			tok = (Token) { NONE };

		has_tok = true;
	}

	TokenT peek() { if (! has_tok) read_token(); return tok.t; }
	Token pop() { if (! has_tok) read_token(); has_tok = false; return tok; }
};

// Problem-specific data structure
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
