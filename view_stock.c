
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

void txt(struct stock* ptr[6]){

    int i,j;
    
    FILE *f;
    f= fopen("files/stock.txt", "r+");
    for(i= 0; i < 6; i++) {
        for(j= 0; j < (*ptr[i]).amount; j++) {
            fprintf(f,"%d %s %.2f \n",(*ptr[i]).id, (*ptr[i]).name,(*ptr[i]).cost);
        }
    }
    fclose(f);
}

void view_stock(struct stock* ptr[6],float ct) {

  printf("***********STOCK************\n\n");
  printf("ID   Type       Price    Qt.\n\n");
  
  printf("%d    %s      %.2f     %d\n",(*ptr[0]).id,(*ptr[0]).name,(*ptr[0]).cost,(*ptr[0]).amount);
  printf("%d    %s   %.2f     %d\n",(*ptr[1]).id,(*ptr[1]).name,(*ptr[1]).cost,(*ptr[1]).amount);
  printf("%d    %s      %.2f    %d\n",(*ptr[2]).id,(*ptr[2]).name,(*ptr[2]).cost,(*ptr[2]).amount);
  printf("%d    %s   %.2f     %d\n",(*ptr[3]).id,(*ptr[3]).name,(*ptr[3]).cost,(*ptr[3]).amount);
  printf("%d    %s   %.2f     %d\n",(*ptr[4]).id,(*ptr[4]).name,(*ptr[4]).cost,(*ptr[4]).amount);
  printf("%d    %s        %.2f     %d\n",(*ptr[5]).id,(*ptr[5]).name,(*ptr[5]).cost,(*ptr[5]).amount);
  
  printf("\n");
  printf("Total cost: %.2f€\n",ct);
} 

void main() {
    struct stock* ptr[6];
    char UserChoice;
    int i;
    float custo_total= 0;

    lertxt(ptr);

    for(i= 0; i < 6; i++)
      custo_total += ((*ptr[i]).cost)*((*ptr[i]).amount);

    view_stock(ptr, custo_total);
    
    printf("quer modificar txt (s/n)?\n");
    scanf("%c",&UserChoice);
    if(UserChoice== 's') {
    txt(ptr);
    }
    
}