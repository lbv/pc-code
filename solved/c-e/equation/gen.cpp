#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <vector>
using namespace std;


#define MAXT 20
#define MAXD 5   /* tree depth for syntax tree */


enum Token {
    TOK_PAR,
    TOK_NUM,
    TOK_ADD,
    TOK_SUB,
    TOK_MUL,
    TOK_DIV
};

struct Tree {
    struct Node {
        Token tok;
        int dig;
        int lt, rt;
    };

    vector<Node> nodes;
    int root;

    Tree() {
        root = generate(MAXD);
    }

    int generate_num() {
        Node nd;
        nd.tok = TOK_NUM;
        nd.dig = rand() % 10;

        int idx = nodes.size();
        nodes.push_back(nd);
        return idx;
    }

    int generate(int d) {
        if (d == 0) return generate_num();

        Node nd;
        Token type = (Token) (rand() % 6);
        switch (type) {
        case TOK_PAR:
            nd.tok = type;
            nd.lt = generate(d - 1);
            break;

        case TOK_NUM:
            return generate_num();

        case TOK_ADD:
        case TOK_SUB:
        case TOK_MUL:
        case TOK_DIV:
            nd.tok = type;
            nd.lt = generate(d - 1);
            nd.rt = generate(d - 1);
            break;
        }

        int idx = nodes.size();
        nodes.push_back(nd);
        return idx;
    }

    void print() {
        print_node(root);
    }

    void print_node(int idx) {
        Node &nd = nodes[idx];
        switch (nd.tok) {
        case TOK_PAR:
            puts("(");
            print_node(nd.lt);
            puts(")");
            break;

        case TOK_NUM:
            printf("%d\n", nd.dig);
            break;

        case TOK_ADD:
            print_node(nd.lt);
            puts("+");
            print_node(nd.rt);
            break;

        case TOK_SUB:
            print_node(nd.lt);
            puts("-");
            print_node(nd.rt);
            break;

        case TOK_MUL:
            print_node(nd.lt);
            puts("*");
            print_node(nd.rt);
            break;

        case TOK_DIV:
            print_node(nd.lt);
            puts("/");
            print_node(nd.rt);
            break;
        }
    }
};


void test_case()
{
    Tree t;
    puts("");
    t.print();
}

int main()
{
    srand(time(NULL));

    int T = MAXT;
    printf("%d\n", T);

    while (T--) test_case();

    return 0;
}
