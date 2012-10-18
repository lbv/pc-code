#include <cstdio>
#include <cstring>


#define MAXLINE 100


int N;
char line[MAXLINE + 1];
int len;


void process()
{
    printf("printf(\"");
    for (int i = 0; i < len; ++i) {
        if (line[i] == '"')
            printf("\\\"");
        else if (line[i] == '\\')
            printf("\\\\");
        else
            putchar(line[i]);
    }
    printf("\\n\");\n");
}

int main()
{
    int ncase = 0;
    while (true) {
        scanf("%d", &N);
        if (N == 0) break;

        printf("Case %d:\n", ++ncase);
        puts("#include<string.h>");
        puts("#include<stdio.h>");
        puts("int main()");
        puts("{");

        while (true) {
            gets(line);
            len = strlen(line);
            if (len == 0) continue;

            process();

            if (--N == 0) break;
        }

        puts("printf(\"\\n\");");
        puts("return 0;");
        puts("}");

    }

    return 0;
}
