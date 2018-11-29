#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
//States
struct states
{
  int finished;
  int processing;
  int waiting;
}state;
//Processing
struct fab_proc
{
  int local;
  int timeleft;
  char opsr[3];
  char *type[];
};
// Read Files Function -> Stores in strings
void r_files(char *stock[8000][20]){
  char text[20];
  int countAc=0,countAl=0,countV=0,countP=0,countF=0,countB=0;
  int lastc;
  FILE *fp;
  int nid;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    while(fgets(text,20,fp)){
      nid = text[0];
      text[20] = '\0';
      switch (nid){
        case '1': 
          countF++;
          strcpy(stock[(nid-1)],text);
          lastc = (strlen(stock[(nid-1)]))+1;
          stock[nid-1][lastc-2] = itoa(countF,10);
          stock[nid-1][lastc-1] = '\0';
          printf("%s",stock[(nid-1)]);
          break;
        case '2': 
          countAl++;
          strcpy(stock[(nid-1)],text);
          break;
        case '3': 
          countV++;
          strcpy(stock[(nid-1)],text);
          break;
        case '4': 
          countP++;
          strcpy(stock[(nid-1)],text);
          break;
        case '5': 
          countB++;
          strcpy(stock[(nid-1)],text);
          break;
        case '6': 
          countAc++;
          strcpy(stock[(nid-1)],text);
          break;
      }
    }
    fclose(fp);
    for (int i=0; i<6;i++){
      printf("%s",stock[i]);
    }
  }
  
}

void main(){
  char *processing[8000][20];
  char *stations[8000][20];
  char *stock[8000][20];
  r_files(stock);
}