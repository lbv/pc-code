#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define UW (!strcmp(argv[0]+strlen(argv[0])-4,".cmd"))

#define WRONG (UW?1:2)
#define FORMAT (UW?2:1)
#define OK 0
char buf[1000];
char withbride[100][256];

char bad[]={
0,
1,
0,
1,
0,
0,
1,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
0,
1,
0,
1,
1,
1,
1,
0,
1,
0,
1,
1};
int bcnt;
main(int argc, char **argv){
   int i,n,m,a,c; char b,d;
   FILE *f;
   if (UW) {
      char buf[100];
      strcpy(buf,argv[0]);
      strcpy(buf+strlen(buf)-3,"dat");
      f = fopen(buf,"r");
   } else f = fopen(argv[1],"r");
   while (2 == fscanf(f,"%d%d",&n,&m) && n) {
      printf("===\n");
      memset(withbride,0,sizeof(withbride));
      withbride[0][0] = 1;
      for (i=1;i<n;i++) {
         if (2 != scanf("%d%c",&a,&b)) {
            printf("bad luck!\n");
            gets(buf);
            if (strcmp(buf,"bad luck")) {
               printf("bad luck misspelled\n"); exit(WRONG);
            }
            if (!bad[bcnt]) {
               printf("failed to find soln\n"); exit(WRONG);
            }
            memset(withbride,1,sizeof(withbride));
            break;
         }
         if (withbride[a][0] || withbride[a][1]) {
            printf("dupe couple %d\n",a); exit(WRONG); 
         }
         withbride[a][b=='h'] = 1;
      }
      for (i=0;i<m;i++) {
         fscanf(f,"%d%c%d%c",&a,&b,&c,&d);
         if (withbride[a][b=='h'] || withbride[c][d=='h']) {
         } else {
            printf("adulterous %d%c %d%c\n",a,b?'h':'w',c,d?'h':'w');
            exit(WRONG);
         }
      }
   bcnt++;}
   printf("judge says OK\n");
   exit(OK);
}
