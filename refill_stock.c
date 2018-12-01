#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

struct stock {
    
    int id;
    int amount;
    float cost;
    char name[20];
    
  }ferro= {1,-1,1.40,"Ferro"},
   aluminio= {2,-1,7.80,"Aluminio"},
   vidro= {3,-1,12.50,"Vidro"},
   plastico= {4,-1,2.20,"Plástico"},
   borracha= {5,-1,1.50,"Borracha"},
   aco= {6,-1,3.30,"Aço"};

void lertxt(struct stock* ptr[6]){
  

  int countF= 0, countAl= 0, countV= 0, countP= 0, countB= 0, countAc= 0;
  char text[20];
  char a;

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

  ptr[0]= malloc(sizeof(ferro));
  ptr[1]= malloc(sizeof(aluminio));
  ptr[2]= malloc(sizeof(vidro));
  ptr[3]= malloc(sizeof(plastico));
  ptr[4]= malloc(sizeof(borracha));
  ptr[5]= malloc(sizeof(aco));

  ferro.amount= countF;
  aluminio.amount= countAl;
  vidro.amount= countV;
  plastico.amount= countP;
  borracha.amount= countB;
  aco.amount= countAc;

  ptr[0]= &ferro;
  ptr[1]= &aluminio;
  ptr[2]= &vidro;
  ptr[3]= &plastico;
  ptr[4]= &borracha;
  ptr[5]= &aco;
}

void refill_stock(struct stock* ptr[6]) {
    char a;
    int refillcountAc= 0, refillcountAl= 0, refillcountB= 0, refillcountF= 0, refillcountP= 0, refillcountV= 0;
    char text[20];

    FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    while(fgets(text,20,fp)){
      a = text[0];
      switch (a){
        case '1': refillcountF++;break;
        case '2': refillcountAl++;break;
        case '3': refillcountV++;break;
        case '4': refillcountP++;break;
        case '5': refillcountB++;break;
        case '6': refillcountAc++;break;
      }
    }
    fclose(fp);
  }
    (*ptr[0]).amount += refillcountF;
    (*ptr[1]).amount += refillcountAl;
    (*ptr[2]).amount += refillcountV;
    (*ptr[3]).amount += refillcountP;
    (*ptr[4]).amount += refillcountB;
    (*ptr[5]).amount += refillcountAc;

    for(int i=0; i < 6; i++) {
        printf("%d\n", (*ptr[i]).amount);
    }
}


void main() {
    struct stock* ptr[6];

    lertxt(ptr);
    refill_stock(ptr);
}