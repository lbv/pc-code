#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char done[100][2][100][2];

doit(int n, int m){
   int i,a,c; char b,d;
   memset(done,0,sizeof(done));
   printf("%d %d\n",n,m);
   for (i=0;i<m;i++) {
      do {
         a = random()%n;
         b = random()%2;
         c = random()%n;
         d = random()%2;
      } while (a == c || done[a][b][c][d]);
      done[a][b][c][d] = 1;
      printf("%d%c %d%c\n",a,b?'w':'h',c,d?'w':'h');
   }
}
 
main(){
   int i;
   for (i=0;i<10;i++) doit(10,10);
   for (i=0;i<10;i++) doit(30,30);
   for (i=0;i<10;i++) doit(30,50);
   printf("0 0\n");
}
