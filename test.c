#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

typedef struct stations {
    int id;
    char ops[3];
    int temp_ops[3];
    double cost;
    int temp_final;
}stations;

void main() {
    stations station[5];

    FILE *fp;
    fp= fopen("files/stations.dat","rb");
    if(fp!=NULL) {
        fread(station,sizeof(stations),5,fp);
        for(int j= 0; j < 5; j++) {
              printf("%d ", station[j].id);
          for(int i= 0; i < 3; i++) {
              printf("%c ", station[j].ops[i]);
          }
          for(int i= 0; i<3; i++) {
              printf("%d ", station[j].temp_ops[i]);
          }
          printf("%.2f ", station[j].cost);
          printf("%d ", station[j].temp_final);
          printf("\n");     
        }
    }
    fclose(fp);
}
        
