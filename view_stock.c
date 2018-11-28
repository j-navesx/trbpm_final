
#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
struct stock {
    char *name;
    int id;
    int amount;
  };

void lertxt(int qnt[6],struct stock *ptr[6]){
  

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

  ferro.name= "Ferro";
  aluminio.name= "Aluminio";
  vidro.name= "Vidro";
  plastico.name= "Plastico";
  borracha.name= "Borracha";
  aco.name= "Aço";

  ptr[0]= &ferro;
  ptr[1]= &aluminio;
  ptr[2]= &vidro;
  ptr[3]= &plastico;
  ptr[4]= &borracha;
  ptr[5]= &aco;

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
  qnt[0]= countF;
  qnt[1]= countAl;
  qnt[2]= countV;
  qnt[3]= countP;
  qnt[4]= countB;
  qnt[5]= countAc;


  printf("ID   Type       Price    Qt.\n\n");
  printf("1    Ferro      ----     %d\n",countF);
  printf("2    Aluminio   ----     %d\n",countAl);
  printf("3    Vidro      ----     %d\n",countV);
  printf("4    Plastico   ----     %d\n",countP);
  printf("5    Borracha   ----     %d\n",countB);
  printf("6    Aço        ----     %d\n\n",countAc);
  printf("Total cost: ------€\n");
} 

void txt(struct stock *ptr[6],int qnt[6]){

    int i,j;
    for(int k;k<6;k++){
        printf("%d\n",qnt[k]);
    }
    FILE *f;
    f= fopen("files/stock.txt", "r+");
    for(i= 0;i<6;i++) {
        for(j= 0;j<qnt[i];j++) {
            fprintf(f,"%d \n",(*ptr[i]).id);
        }
    }
    fclose(f);
}

void main(){
    struct stock *ptr[6];
    char UserChoice;
    int qnt[6];
    lertxt(qnt,ptr);
    
    printf("quer modificar txt (s/n)?\n");
    scanf("%c",&UserChoice);
    if(UserChoice== 's') {
    txt(ptr,qnt);
    }
    
}