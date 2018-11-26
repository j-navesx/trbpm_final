#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

struct stock {

int id;
int amount;
};

void main() {

  int countF= 0, countAl= 0, countV= 0, countP= 0, countB= 0, countAc= 0;
  char a;

  struct stock ferro;
  struct stock aluminio;
  struct stock vidro;
  struct stock plastico;
  struct stock borracha;
  struct stock aco;

  ferro.id= 1;
  aluminio.id= 2;
  vidro.id= 3;
  plastico.id= 4;
  borracha.id= 5;
  aco.id= 6;

  char text[20];
  FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    while(fgets(text,20,fp)){
      a = text[0];
      switch (a){
        case '1': countF++;break;
        case '2': countAl++;break;
        case '3': countV++;break;
        case '4': countP++;break;
        case '5': countB++;break;
        case '6': countAc++;break;
      }
      printf("%s",text);
    }
    fclose(fp);
  }
  
  printf("%d %d %d %d %d %d\n", countF,countAl,countV,countP,countB,countAc);

  fp= fopen("files/quantities.txt","w+");
  if(fp!=NULL) {
    fprintf(fp,"1 %d\n",countF);
    fprintf(fp,"2 %d\n",countAl);
    fprintf(fp,"3 %d\n",countV);
    fprintf(fp,"4 %d\n",countP);
    fprintf(fp,"5 %d\n",countB);
    fprintf(fp,"6 %d\n",countAc);
 }


/*struct stock.price ferro= 1.40;
struct stock.price aluminio= 7.80;
struct stock.price vidro= 12.50;
struct stock.price plastico= 2.20;
struct stock.price borracha= 1.50;
struct stock.price aco= 3.30;*/

}


