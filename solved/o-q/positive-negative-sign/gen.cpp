/*
	Author       :	Jan
	Problem Name :
	Algorithm    :
	Complexity   :
*/

#include <set>
#include <map>
#include <list>
#include <cmath>
#include <ctime>
#include <deque>
#include <queue>
#include <stack>
#include <cctype>
#include <cstdio>
#include <string>
#include <vector>
#include <cassert>
#include <cstdlib>
#include <cstring>
#include <sstream>
#include <iostream>
#include <algorithm>

using namespace std;

#define LIM 1000000000

int main() {
	freopen("a.in", "w", stdout);

    srand(time(NULL));
	int cases = 100000;
	printf("%d\n", cases);

	while( cases-- ) {
		int n, m;

        if (rand() % 5 == 0)
            m = rand() % (100) + 1;
        else
            m = rand() % (LIM / 2) + 1;
            
        n = m*2;
        
        int maxf = LIM/n;
        if (maxf > 100 && rand() % 3 == 0)
            maxf = rand() % 100 + 1;

        int f = rand() % maxf + 1;
        n *= f;

		printf("%d %d\n", n, m);
	}
	return 0;
}

