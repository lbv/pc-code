#include <cctype>
#include <cstdio>
#include <queue>
using namespace std;


#define MAXLEN 100


template<typename T>
T gcd(T a, T b) { for (T c = a%b; c != 0; a=b,b=c,c=a%b); return b; }

enum TType {
    NONE,
    INT,
    X,
    PAREN1,
    PAREN2,
    EQUALS,
    PLUS,
    MINUS,
    TIMES
};

struct Token {
    int v;
    TType t;
    Token(TType T) : v(0), t(T) {}
    Token(int V, TType T) : v(V), t(T) {}
};
typedef queue<Token> TQ;

struct AST {
    struct Node {
        int lt, rt;
        int c0, c1;  // coefficients: c1*x + c0
        TType op;
        Node(int C0, int C1) : lt(-1), rt(-1), c0(C0), c1(C1) {}
        Node(TType O, int L, int R) : lt(L), rt(R), op(O) {}
    };
    vector<Node> nodes;

    int add(int c0, int c1) {
        int idx = nodes.size();
        nodes.push_back(Node(c0, c1));
        return idx;
    }
    int add(TType op, int lt, int rt) {
        int idx = nodes.size();
        nodes.push_back(Node(op, lt, rt));
        return idx;
    }
    void eval(int r, int &c0, int &c1) {
        Node &nd = nodes[r];
        if (nd.lt < 0) {
            c0 = nd.c0, c1 = nd.c1;
            return;
        }
        int c0_lt, c1_lt, c0_rt, c1_rt;
        eval(nd.lt, c0_lt, c1_lt);
        eval(nd.rt, c0_rt, c1_rt);

        if (nd.op == TIMES) {
            c1 = c1_lt * c0_rt + c1_rt * c0_lt;
            c0 = c0_lt * c0_rt;
            return;
        }
        if (nd.op == PLUS) {
            c0 = c0_lt + c0_rt;
            c1 = c1_lt + c1_rt;
            return;
        }
        if (nd.op == MINUS || nd.op == EQUALS) {
            c0 = c0_lt - c0_rt;
            c1 = c1_lt - c1_rt;
        }
    }
    void print(int r, int l = 0) {
        for (int i = 0; i < l; ++i) putchar(' ');
        Node &nd = nodes[r];
        if (nd.lt < 0) {
            printf("(%d,%d)\n", nd.c0, nd.c1);
            return;
        }

        if (nd.op == TIMES) puts("*");
        else if (nd.op == PLUS) puts("+");
        else if (nd.op == MINUS) puts("-");
        else if (nd.op == EQUALS) puts("=");
        else puts("?");
        print(nd.lt, l + 1);
        print(nd.rt, l + 1);
    }
};

/*
 * Grammar:
 * <equation>   ::= <expression> '=' <expression>
 * <expression> ::= <term> [ ('+'|'-' <term> ]*
 * <term>       ::= <factor> [ '*' <factor> ]*
 * <factor>     ::= INT | 'x'
 *                | '(' <expression> ')'
 */
struct Parser {
    TQ &in;
    Parser(TQ &In) : in(In) {}

    TType in_peek() {
        if (in.empty()) return NONE;
        return in.front().t;
    }
    Token in_pop() {
        if (in.empty()) return Token(NONE);
        Token t = in.front();
        in.pop();
        return t;
    }

    int equation(AST &ast) {
        int lt = expression(ast);
        in_pop();
        int rt = expression(ast);
        return ast.add(EQUALS, lt, rt);
    }

    int expression(AST &ast) {
        int lt = term(ast);
        while (in_peek() == PLUS || in_peek() == MINUS) {
            TType op = in_peek();
            in_pop();
            int rt = term(ast);
            lt = ast.add(op, lt, rt);
        }
        return lt;
    }

    int term(AST &ast) {
        int lt = factor(ast);
        while (in_peek() == TIMES) {
            in_pop();
            int rt = factor(ast);
            lt = ast.add(TIMES, lt, rt);
        }
        return lt;
    }

    int factor(AST &ast) {
        if (in_peek() == INT) {
            Token tok = in_pop();
            return ast.add(tok.v, 0);
        }
        if (in_peek() == X) {
            in_pop();
            return ast.add(0, 1);
        }
        in_pop();  // '('
        int root = expression(ast);
        in_pop();  // ')'
        return root;
    }
};


char line[MAXLEN + 1];

void lexer(TQ &in)
{
    for (char *p = line; *p; ++p) {
        if      (*p == '*') in.push(Token(TIMES));
        else if (*p == '+') in.push(Token(PLUS));
        else if (*p == '-') in.push(Token(MINUS));
        else if (*p == 'x') in.push(Token(X));
        else if (*p == '=') in.push(Token(EQUALS));
        else if (*p == '(') in.push(Token(PAREN1));
        else if (*p == ')') in.push(Token(PAREN2));
        else if (isdigit(*p)) {
            int v = 0;
            while (isdigit(*p))
                v = v * 10 + (*p++ - '0');
            --p;
            in.push(Token(v, INT));
        }
    }
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s", line);

        TQ input;
        lexer(input);
        Parser p(input);

        AST ast;
        int root = p.equation(ast);

//        puts("debugging AST:");
//        ast.print(root);

        int c0, c1;
        ast.eval(root, c0, c1);

        printf("Case %d: ", ++ncase);

        if (c1 != 0) {
            int num = -c0, den = c1;
            int g = gcd(num, den);
            num /= g;
            den /= g;
            if (den < 0) num *= -1, den *= -1;

            if (den == 1)
                printf("%d\n", num);
            else
                printf("%d/%d\n", num, den);
        }
        else if (c1 == 0 && c0 == 0)
            puts("infinitely many solutions");
        else
            puts("no solution");
    }

    return 0;
}
