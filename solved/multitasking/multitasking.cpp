#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;


#define MAXTIME 1000000

#define Neg(v)  memset((v), -1, sizeof(v))


struct Task {
    int b, e;  // begin, end time
    int r;     // repetition interval (0 if it doesn't repeat)
    Task(int B, int E, int R) : b(B), e(E), r(R) {}
};
typedef vector<Task> TV;


int n, m;
int sched[MAXTIME + 1];


bool solve(TV &tasks)
{
    int last = 0;
    for (int t = 0; t <= MAXTIME; ++t) {
        if (sched[t] < 0) continue;

        Task &tsk = tasks[sched[t]];
        if (tsk.b < last) return false;
        last = tsk.e;

        if (tsk.r > 0) {
            tsk.b += tsk.r;
            tsk.e += tsk.r;

            if (tsk.b <= MAXTIME) {
                if (sched[tsk.b] != -1) return false;
                sched[tsk.b] = sched[t];
            }
        }
    }

    return true;
}

int main()
{
    while (true) {
        scanf("%d%d", &n, &m);
        if (n == 0 && m == 0) break;

        TV tasks;
        Neg(sched);

        int nt = 0;  // number of tasks
        int t1, t2, r;
        bool conflict = false;

        while (n--) {
            scanf("%d%d", &t1, &t2);
            tasks.push_back(Task(t1, t2, 0));
            if (sched[t1] != -1)
                conflict = true;
            else
                sched[t1] = nt++;
        }
        while (m--) {
            scanf("%d%d%d", &t1, &t2, &r);
            tasks.push_back(Task(t1, t2, r));
            if (sched[t1] != -1)
                conflict = true;
            else
                sched[t1] = nt++;
        }

        if (conflict) {
            puts("CONFLICT");
            continue;
        }

        if (solve(tasks))
            puts("NO CONFLICT");
        else
            puts("CONFLICT");
    }

    return 0;
}
