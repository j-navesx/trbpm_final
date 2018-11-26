#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
void lertxt(){
  struct stock {
    int id;
    int amount;
  };
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
    }
    fclose(fp);
  }
} 

void main(){
  lertxt();
}