#include <algorithm>
#include <cctype>
#include <cstdio>
#include <cstring>
#include <map>
#include <string>
using namespace std;


#define MAXNAME    30
#define MAXTEAMS   30
#define MAXTOURNEY 100
#define MAXLINE    (2*MAXNAME + 10)


typedef unsigned int u32;

typedef map<string, int> SIM;


struct Team {
    char name[MAXNAME + 1];
    int len;  // name length
    int p;    // points
    int w;    // wins
    int t;    // ties
    int l;    // loses
    int gs;   // goals scored
    int ga;   // goals against
    int gp;   // games played

    Team() {}
    Team(const char *Name) {
        strcpy(name, Name);
        len = strlen(name);
        p = w = t = l = gs = ga = gp = 0;
    }

    bool operator<(const Team &x) const {
        if (p != x.p) return p > x.p;
        if (w != x.w) return w > x.w;
        int d1 = gs - ga;
        int d2 = x.gs - x.ga;
        if (d1 != d2) return d1 > d2;
        if (gs != x.gs) return gs > x.gs;
        if (gp != x.gp) return gp < x.gp;

        for (int i = 0; i < len; ++i) {
            if (i >= x.len) return true;
            char c1 = tolower(name[i]);
            char c2 = tolower(x.name[i]);
            if (c1 != c2)
                return c1 < c2;
        }
        return false;
    }
};

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
    void skip_line() {
        for (; b != 10 && b != 13 && b != 0; read());
        char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
    u32 next_u32() {
        u32 v = 0; for (skip(); b > 32; read()) v = v*10 + b-48; return v; }
    void next_real_line(char *s, int &l) {
        for (l = 0; b != 10 && b != 13 && b != 0; read()) *s++ = b, ++l;
        *s = 0; char p = b; read();
        if ((p == 10 && b == 13) || (p == 13 && b == 10)) read(); }
};


SIM team_map;

Team teams[MAXTEAMS];

char tourney[MAXTOURNEY + 1];
char team1[MAXNAME + 1];
char team2[MAXNAME + 1];
char game[MAXLINE + 1];

int len;
int T;


int main()
{
    Reader rr;
    int N = rr.next_u32();
    rr.skip_line();

    bool first = true;
    while (N--) {
        rr.next_real_line(tourney, len);
        T = rr.next_u32();
        rr.skip_line();

        team_map.clear();

        for (int i = 0; i < T; ++i) {
            rr.next_real_line(team1, len);
            teams[i] = Team(team1);
            team_map[string(team1)] = i;
        }

        int G = rr.next_u32();
        rr.skip_line();

        while (G--) {
            rr.next_real_line(game, len);
            int g1, g2;

            char *p = game;
            int x = strcspn(p, "#");
            game[x] = 0;
            strcpy(team1, p);

            p += x + 1;
            sscanf(p, "%d@%d#", &g1, &g2);
            x = strcspn(p, "#");
            p += x + 1;
            strcpy(team2, p);

            int idx1 = team_map[string(team1)];
            int idx2 = team_map[string(team2)];

            ++teams[idx1].gp;
            ++teams[idx2].gp;

            teams[idx1].gs += g1;
            teams[idx1].ga += g2;
            teams[idx2].gs += g2;
            teams[idx2].ga += g1;

            if (g1 == g2) {
                ++teams[idx1].p;
                ++teams[idx2].p;
                ++teams[idx1].t;
                ++teams[idx2].t;
            }
            else if (g1 > g2) {
                ++teams[idx1].w;
                ++teams[idx2].l;
                teams[idx1].p += 3;
            }
            else {
                ++teams[idx2].w;
                ++teams[idx1].l;
                teams[idx2].p += 3;
            }

        }

        sort(teams, teams + T);

        if (first) first = false;
        else puts("");

        printf("%s\n", tourney);

        for (int i = 0; i < T; ++i) {
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                   i + 1, teams[i].name, teams[i].p,
                   teams[i].gp, teams[i].w, teams[i].t, teams[i].l,
                   teams[i].gs - teams[i].ga, teams[i].gs, teams[i].ga);
        }
    }

    return 0;
}
