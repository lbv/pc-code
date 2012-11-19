#include <cstdio>
#include <cstring>


#define MAXRAM 1000
#define MAXREG 10
#define MOD    1000

#define Zero(v) memset((v), 0, sizeof(v))


struct Op {
    int op;    // operation
    int x, y;  // arguments
    int d;     // decimal representation
    void read(const char *line) {
        op = line[0] - '0';
        x  = line[1] - '0';
        y  = line[2] - '0';

        d = op * 100 + x*10 + y;
    }
    void from(int v) {
        op = v / 100;
        x = (v / 10) % 10;
        y = v % 10;
        d = v;
    }
};


Op ram[MAXRAM];
int reg[MAXREG];
char line[8];


int simulate()
{
    int cnt = 0;

    int ip = 0;
    while (true) {
        ++cnt;

        Op o = ram[ip++];
        switch(o.op) {
        case 1:
            return cnt;

        case 2:
            reg[o.x] = o.y;
            break;

        case 3:
            reg[o.x] += o.y;
            reg[o.x] %= MOD;
            break;

        case 4:
            reg[o.x] *= o.y;
            reg[o.x] %= MOD;
            break;

        case 5:
            reg[o.x] = reg[o.y];
            break;

        case 6:
            reg[o.x] += reg[o.y];
            reg[o.x] %= MOD;
            break;

        case 7:
            reg[o.x] *= reg[o.y];
            reg[o.x] %= MOD;
            break;

        case 8:
            reg[o.x] = ram[reg[o.y]].d;
            break;

        case 9:
            ram[reg[o.y]].from(reg[o.x]);
            break;

        case 0:
            if (reg[o.y] != 0)
                ip = reg[o.x];
            break;
        }

    }

    return cnt;
}

int main()
{
    int T;
    scanf("%d", &T);
    gets(line); gets(line);

    bool first = true;
    while (T--) {
        Zero(reg);
        Zero(ram);

        int p = 0;
        while (true) {
            gets(line);
            if (line[0] == 0) break;
            ram[p++].read(line);
        }

        if (first) first = false;
        else putchar('\n');

        printf("%d\n", simulate());
    }

    return 0;
}
