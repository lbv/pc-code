#include <cstdio>
#include <queue>
#include <vector>
using namespace std;


#define MAXLEN 100


typedef unsigned int u32;


u32 vars_bm;


enum TType {
    NONE,
    VAR,
    AND,
    OR,
    NOT,
    PAREN1,
    PAREN2
};

struct Token {
    int v;    // index of var (a is 0, b is 1, ...)
    TType t;
    Token(TType T) : v('?'), t(T) {}
    Token(int V, TType T) : v(V), t(T) {}
};
typedef queue<Token> TQ;

struct AST {
    struct Node {
        int lt, rt;
        int v;
        TType op;
        Node(int V) : lt(-1), rt(-1), v(V) {}
        Node(TType O, int L, int R) : lt(L), rt(R), op(O) {}
    };
    vector<Node> nodes;

    int add(int v) {
        int idx = nodes.size();
        nodes.push_back(Node(v));
        return idx;
    }
    int add(TType op, int lt, int rt) {
        int idx = nodes.size();
        nodes.push_back(Node(op, lt, rt));
        return idx;
    }

    bool eval(int root) {
        Node &nd = nodes[root];

        if (nd.lt < 0)
            return (vars_bm & (1 << nd.v)) != 0;

        if (nd.op == NOT)
            return !eval(nd.lt);

        if (nd.op == OR)
            return eval(nd.lt) || eval(nd.rt);

        if (nd.op == AND)
            return eval(nd.lt) && eval(nd.rt);

        return false;
    }
};

/*
 * Grammar:
 *
 * <expression> ::= <term> [ '|' <term> ]*
 * <term>       ::= <factor> [ '&' <factor> ]*
 * <factor>     ::= <sub> | '!' <factor>
 * <sub>        ::= VAR | '(' <expression> ')'
 */
struct Parser {
    TQ &in;
    Parser(TQ &In) : in(In) { }

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

    int expression(AST &ast) {
        int lt = term(ast);
        while (in_peek() == OR) {
            in_pop();
            int rt = term(ast);
            lt = ast.add(OR, lt, rt);
        }
        return lt;
    }

    int term(AST &ast) {
        int lt = factor(ast);
        while (in_peek() == AND) {
            in_pop();
            int rt = factor(ast);
            lt = ast.add(AND, lt, rt);
        }
        return lt;
    }

    int factor(AST &ast) {
        if (in_peek() == NOT) {
            in_pop();
            return ast.add(NOT, factor(ast), -1);
        }
        return sub(ast);
    }

    int sub(AST &ast) {
        if (in_peek() == VAR) {
            Token tok = in_pop();
            return ast.add(tok.v);
        }
        in_pop();  // '('
        int root = expression(ast);
        in_pop();  // ')'
        return root;
    }
};


char s1[MAXLEN + 1];
char s2[MAXLEN + 1];
int nvars;


int parse_exp(const char *s, AST &ast)
{
    TQ input;
    for (const char *p = s; *p; ++p) {
        if      (*p == '&') input.push(Token(AND));
        else if (*p == '|') input.push(Token(OR));
        else if (*p == '!') input.push(Token(NOT));
        else if (*p == '(') input.push(Token(PAREN1));
        else if (*p == ')') input.push(Token(PAREN2));
        else if (*p >= 'a' && *p <= 'j') {
            int idx = *p - 'a';
            if (idx + 1 > nvars) nvars = idx + 1;
            input.push(Token(idx, VAR));
        }
    }

    Parser p(input);
    return p.expression(ast);
}

bool solve(AST &ast1, int r1, AST &ast2, int r2)
{
    u32 all = (1 << nvars) - 1;

    for (vars_bm = 0; vars_bm <= all; ++vars_bm) {
        bool b1 = ast1.eval(r1);
        bool b2 = ast2.eval(r2);

        if (b1 != b2) return false;
    }
    return true;
}

int main()
{
    int T;
    scanf("%d", &T);

    int ncase = 0;
    while (T--) {
        scanf("%s%s", s1, s2);

        nvars = 0;
        AST ast1, ast2;
        int root1 = parse_exp(s1, ast1);
        int root2 = parse_exp(s2, ast2);

        printf("Case %d: ", ++ncase);
        if (solve(ast1, root1, ast2, root2))
            puts("Equivalent");
        else
            puts("Not Equivalent");
    }

    return 0;
}
