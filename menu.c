#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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

void build_car_display() {

  printf("        ***Product List Menu***         \n\n");
  printf("  1 - Ford\n");
  printf("  2 - Renault\n");
  printf("  3 - Honda\n");
  printf("  4 - Mercedes\n");
  printf("  5 - Ferrari\n\n");
  printf("  B - Back\n\n");
  printf("Opção: ");
  
}

void factory_state_display() {

  printf("        ***Factory State Menu***         \n\n");
  printf("  1 - Show all processes\n");
  printf("  2 - Show processes by type\n");
  printf("  3 - Show processes by state\n");
  printf("  4 - Machine state\n");
  printf("  5 - Machine info\n");
  printf("  6 - Map\n\n");
  printf("  B - Back\n\n");
  printf("Opção: ");
  
}

void stats_display() {

  printf("        ***Factory Stats Menu***         \n\n");
  printf("  1 - Finished products by type\n");
  printf("  2 - Products state\n");
  printf("  3 - Stations cost\n\n");
  printf("  B - Back\n\n");
  printf("Opção: ");
  
}

void menu_display() {

  printf("\n\t\t***Factory Admin Menu***\n\n");
  printf("1- Show stock\n");
  printf("2- Refill stock\n");
  printf("3- Build car\n");
  printf("4- Factory State\n");
  printf("5- Stats\n");
  printf("6- Time skip\n\n");
  printf("E- Exit\n\n");
  printf("Option: ");
}

void lertxt(struct stock* stock_ptr[6]) {
  
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

  stock_ptr[0]= malloc(sizeof(ferro));
  stock_ptr[1]= malloc(sizeof(aluminio));
  stock_ptr[2]= malloc(sizeof(vidro));
  stock_ptr[3]= malloc(sizeof(plastico));
  stock_ptr[4]= malloc(sizeof(borracha));
  stock_ptr[5]= malloc(sizeof(aco));

  ferro.amount= countF;
  aluminio.amount= countAl;
  vidro.amount= countV;
  plastico.amount= countP;
  borracha.amount= countB;
  aco.amount= countAc;

  stock_ptr[0]= &ferro;
  stock_ptr[1]= &aluminio;
  stock_ptr[2]= &vidro;
  stock_ptr[3]= &plastico;
  stock_ptr[4]= &borracha;
  stock_ptr[5]= &aco;
}

void view_stock(struct stock* stock_ptr[6],float ct) {

  char user;
  
  do {
  
    printf("        ***STOCK***         \n\n");
    printf("ID   Type       Price    Qt.\n\n");
  
    printf("%d    %s      %.2f     %d\n",(*stock_ptr[0]).id,(*stock_ptr[0]).name,(*stock_ptr[0]).cost,(*stock_ptr[0]).amount);
    printf("%d    %s   %.2f     %d\n",(*stock_ptr[1]).id,(*stock_ptr[1]).name,(*stock_ptr[1]).cost,(*stock_ptr[1]).amount);
    printf("%d    %s      %.2f    %d\n",(*stock_ptr[2]).id,(*stock_ptr[2]).name,(*stock_ptr[2]).cost,(*stock_ptr[2]).amount);
    printf("%d    %s   %.2f     %d\n",(*stock_ptr[3]).id,(*stock_ptr[3]).name,(*stock_ptr[3]).cost,(*stock_ptr[3]).amount);
    printf("%d    %s   %.2f     %d\n",(*stock_ptr[4]).id,(*stock_ptr[4]).name,(*stock_ptr[4]).cost,(*stock_ptr[4]).amount);
    printf("%d    %s        %.2f     %d\n",(*stock_ptr[5]).id,(*stock_ptr[5]).name,(*stock_ptr[5]).cost,(*stock_ptr[5]).amount);
  
    printf("\n");
    printf("Total cost: %.2f€\n\n",ct);

    getchar();
    scanf("%c", &user);
  } while(user != '\n');

} 

void refill_stock(struct stock* stock_ptr[6]) {
    char a;
    int refillcountAc= 0, refillcountAl= 0, refillcountB= 0, refillcountF= 0, refillcountP= 0, refillcountV= 0;
    char text[20];
    char File[200]= {"files/"};
    char UserFile[200];

    printf("Filename: ");
    scanf(" %s", UserFile);
    strcat(File, UserFile);
    printf("\n");

    FILE *refill;
    refill = fopen(File,"r");
    if (refill!=NULL){  
      while(fgets(text,20,refill)){
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
    fclose(refill);
    }
    (*stock_ptr[0]).amount += refillcountF;
    (*stock_ptr[1]).amount += refillcountAl;
    (*stock_ptr[2]).amount += refillcountV;
    (*stock_ptr[3]).amount += refillcountP;
    (*stock_ptr[4]).amount += refillcountB;
    (*stock_ptr[5]).amount += refillcountAc;

}

void build_car_interface() {

  char user;

  do {
    build_car_display();
    scanf(" %c", &user);

    switch(user) {
      case '1': break;
      case '2': break;
      case '3': break;
      case '4': break;
      case '5': break;
    }
  }while(user != 'B' && user != 'b');
}

void factory_state_interface() {

  char user;

  do {
    factory_state_display();
    scanf(" %c", &user);

    switch(user) {
      case '1': break;
      case '2': break;
      case '3': break;
      case '4': break;
      case '5': break;
      case '6': break;
    }
  }while(user != 'B' && user != 'b');
}

void stats_interface() {

  char user;

  do {
    stats_display();
    scanf(" %c", &user);

    switch(user) {
      case '1': break;
      case '2': break;
      case '3': break;
    }
  }while(user != 'B' && user != 'b');
}

/*void txt(struct stock* ptr[6]) {

    int i,j;
    
    FILE *f;
    f= fopen("files/stock.txt", "r+");
    for(i= 0; i < 6; i++) {
        for(j= 0; j < (*ptr[i]).amount; j++) {
            fprintf(f,"%d %s %.2f \n",(*ptr[i]).id, (*ptr[i]).name,(*ptr[i]).cost);
        }
    }
    fclose(f);
}*/

void main() {

  char user;
  struct stock* stock_ptr[6];
  char UserChoice;
  int i;
  float custo_total= 0;
  
  lertxt(stock_ptr);

  do {
    menu_display();
    scanf(" %c", &user);
    printf("\n");
    switch(user) {
      case '1': custo_total= 0;
                for(i= 0; i < 6; i++)
                   custo_total += ((*stock_ptr[i]).cost)*((*stock_ptr[i]).amount);
                view_stock(stock_ptr, custo_total);
                break;
      case '2': refill_stock(stock_ptr);
                break;
      case '3': build_car_interface();
                break;
      case '4': factory_state_interface();
                break;
      case '5': stats_interface();
                break;
      case '6': break;
    } 
  } while(user != 'E' && user != 'e');

  /*printf("quer modificar txt (s/n)?\n");
  scanf("%c",&UserChoice);
  if(UserChoice== 's') {
  txt(ptr);
  }*/
}