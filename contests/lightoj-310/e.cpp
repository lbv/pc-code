#include <cctype>
#include <cstdio>
#include <queue>
#include <string>
using namespace std;


struct LineReader {
    char b; LineReader() { read(); }
    void read() { b = getchar_unlocked(); }
    void skip() { while (b >= 0 && b <= 32 && b != 10) read(); }
    void skip_line() { skip(); if (b == 10) { read(); skip(); } }
    bool has_next() { skip(); return b > 0 && b != 10; }

    void next(char *s) { for (skip(); b > 32; read()) *s++ = b; *s = 0; }
    int next_int() {
        int v = 0; bool s = false;
        skip(); if (b == '-') { s = true; read(); }
        for (; b > 32; read()) v = v*10 + b-48; return s ? -v : v; }
};


enum TType {
    NONE,
    S,
    NP,
    VP,
    PP,
    NOUN,
    VERB,
    ADJECTIVE,
    ADVERB,
    PREPOSITION,
    ARTICLE,
    CONJUNCTION
};

struct Token {
    TType typ;
    Token(TType Typ) : typ(Typ) {}
};
typedef queue<Token> TQ;

struct Parser {
    TQ &in;
    bool err;
    Parser(TQ &In) : in(In) { err = false; }

    TType in_peek() {
        if (in.empty()) return NONE;
        return in.front().typ;
    }
    Token in_pop() {
        if (in.empty()) return Token(NONE);
        Token t = in.front();
        in.pop();
        return t;
    }

    void s() {
        np();
        vp();
        if (in_peek() == CONJUNCTION) {
            in_pop();
            np();
            vp();
        }
        if (in_peek() != NONE) err = true;
    }

    void np() {
        if (in_peek() == ARTICLE) in_pop();
        if (in_peek() == ADJECTIVE) in_pop();
        if (in_pop().typ != NOUN) err = true;
    }

    void vp() {
        if (in_pop().typ != VERB) err = true;
        if (in_peek() == ADVERB) in_pop();
        if (in_peek() == PREPOSITION) pp();
    }

    void pp() {
        if (in_pop().typ != PREPOSITION) err = true;
        np();
    }
};



struct WordTuple {
    string s;
    TType t;
    WordTuple(string S, TType T) : s(S), t(T) {}
};

const WordTuple word_table[] = {
    WordTuple("i", NOUN),
    WordTuple("bridge", NOUN),
    WordTuple("boy", NOUN),
    WordTuple("dog", NOUN),
    WordTuple("pizza", NOUN),
    WordTuple("home", NOUN),
    WordTuple("ball", NOUN),
    WordTuple("store", NOUN),

    WordTuple("threw", VERB),
    WordTuple("ran", VERB),
    WordTuple("bought", VERB),
    WordTuple("eats", VERB),
    WordTuple("buy", VERB),
    WordTuple("loves", VERB),
    WordTuple("went", VERB),

    WordTuple("big", ADJECTIVE),
    WordTuple("tall", ADJECTIVE),
    WordTuple("tasty", ADJECTIVE),
    WordTuple("round", ADJECTIVE),
    WordTuple("blue", ADJECTIVE),

    WordTuple("quickly", ADVERB),
    WordTuple("loudly", ADVERB),

    WordTuple("to", PREPOSITION),
    WordTuple("under", PREPOSITION),
    WordTuple("from", PREPOSITION),

    WordTuple("a", ARTICLE),
    WordTuple("an", ARTICLE),
    WordTuple("the", ARTICLE),

    WordTuple("and", CONJUNCTION),
    WordTuple("or", CONJUNCTION),
    WordTuple("but", CONJUNCTION),
    WordTuple("yet", CONJUNCTION),

    WordTuple("", NONE)
};


Token recognize_token(char *s)
{
    for (char *p = s; *p; ++p)
        *p = tolower(*p);

    string w(s);
    for (int i = 0; word_table[i].s.size() > 0; ++i)
        if (word_table[i].s == w) return word_table[i].t;

    return Token(NONE);
}

int main()
{
    LineReader lr;
    int n = lr.next_int();
    lr.skip_line();

    while (n--) {
        TQ input;

        while (lr.has_next()) {
            char s[64];
            lr.next(s);
            input.push(recognize_token(s));
        }
        lr.skip_line();

        Parser p(input);
        p.s();

        if (! p.err)
            puts("Sentence");
        else
            puts("Not a sentence");
    }

    return 0;
}
