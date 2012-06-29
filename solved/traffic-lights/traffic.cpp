#include <cstdio>
#include <cstring>

#define LIMIT 18000

#define Zero(v) memset(v, 0, sizeof(v))

// greens[i] will have the number of green lights at second i
int greens[LIMIT + 1];

int n;   // number of lights
int lo;  // minimum cycle found

void add_light(int c)
{
    ++n;
    for (int i = 0; i <= LIMIT; i += 2*c)
        for (int j = i, J = i + c - 5; j <= LIMIT && j < J; ++j)
            ++greens[j];
    if (c < lo) lo = c;
}

void print_solution()
{
    bool found = false;
    for (int i = lo*2; i <= LIMIT; ++i)
        if (greens[i] == n) {
            printf("%02d:%02d:%02d\n", i / 3600, (i % 3600) / 60, i % 60);
            found = true;
            break;
        }

    if (! found)
        puts("Signals fail to synchronise in 5 hours");

    n = 0;
    Zero(greens);
    lo = LIMIT;
}

int main()
{
    n = 0;
    lo = LIMIT;

    while (true) {
        int c;  // cycle
        scanf("%d", &c);
        if (c == 0) {
            if (n == 0) break;
            print_solution();
        }
        else
            add_light(c);
    }

    return 0;
}
