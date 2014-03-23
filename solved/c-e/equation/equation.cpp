#include <cstdio>
#include <queue>
#include <vector>
using namespace std;

typedef unsigned int u32;

//
// I/O
//
#define BUF 65536
struct Reader {
    char buf[BUF]; char b; int bi, bz;
    Reader() { bi=bz=0; read(); }
    void read() {
        if (bi==bz) { bi=0; bz = fread(buf, 1, BUF, stdin); }
        b = bz ? buf[bi++] : 0; }
    void skip() { while (b > 0 && b <= 32) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void skip_line() {
        for (; b != 10 && b != 13 && b != 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};

enum TType {
    NONE,
    DIGIT,
    OP_SUM,
    OP_MUL,
    PAREN1,
    PAREN2
};

struct Token {
    char  tok;
    TType typ;
    Token(char Tok, TType Typ) : tok(Tok), typ(Typ) {}
};
typedef queue<Token> TQ;

struct AST {
    struct Node {
        Token t;
        int l, r;  // left and right children
        Node(Token T, int L, int R) : t(T), l(L), r(R) {}
    };
    vector<Node> nodes;
    int sz;
    AST() { sz = 0; }
    int add(Token t, int l = -1, int r = -1) {
        nodes.push_back(Node(t, l, r));
        return sz++;
    }
    void postfix(int root) {
        if (nodes[root].l >= 0)
            postfix(nodes[root].l);
        if (nodes[root].r >= 0)
            postfix(nodes[root].r);
        putchar(nodes[root].t.tok);
    }
};

/*
 * Grammar:
 *
 * <exp> ::= <sum> { OP_SUM <sum> }*
 *
 * <sum> ::= <fac> { OP_MUL <fac> }*
 *
 * <fac> ::= DIGIT
 *         | PAREN1 <exp> PAREN2
 *
 * OP_SUM ::= '+' | '-'
 * OP_MUL ::= '*' | '/'
 * PAREN1 ::= '('
 * PAREN2 ::= ')'
 * DIGIT  ::= [0-9]
 */
struct Parser {
    TQ &in;
    Parser(TQ &In) : in(In) {}

    TType in_peek() {
        if (in.empty()) return NONE;
        return in.front().typ;
    }
    Token in_pop() {
        Token t = in.front();
        in.pop();
        return t;
    }

    int exp(AST &ast) {
        int root = sum(ast);
        while (in_peek() == OP_SUM) {
            Token op = in_pop();
            int right = sum(ast);
            root = ast.add(op, root, right);
        }
        return root;
    }
    int sum(AST &ast) {
        int root = fac(ast);
        while (in_peek() == OP_MUL) {
            Token op = in_pop();
            int right = fac(ast);
            root = ast.add(op, root, right);
        }
        return root;
    }
    int fac(AST &ast) {
        if (in_peek() == PAREN1) {
            in_pop();
            int ret = exp(ast);
            in_pop();
            return ret;
        }
        return ast.add(in_pop());
    }
};


char line[4];
int len;

int main()
{
    Reader rr;

    int T = rr.next_u32();
    rr.skip_line();
    rr.skip_line();

    bool first = true;
    while (T--) {
        TQ input;

        while (true) {
            rr.next_real_line(line, len);
            if (line[0] == 0) break;

            switch (line[0]) {
            case '+':
            case '-':
                input.push(Token(line[0], OP_SUM));
                break;

            case '*':
            case '/':
                input.push(Token(line[0], OP_MUL));
                break;

            case '(':
                input.push(Token(line[0], PAREN1));
                break;

            case ')':
                input.push(Token(line[0], PAREN2));
                break;

            default:
                input.push(Token(line[0], DIGIT));
            }
        }

        Parser p(input);

        AST ast;
        int root = p.exp(ast);

        if (first) first = false;
        else putchar('\n');

        ast.postfix(root);
        putchar('\n');
    }

    return 0;
}
