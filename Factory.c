#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

typedef struct stock 
{ 
  int id;
  int amount;
  float cost;
  char name[20];
}stock;
//! Passar esta parte para ler do items.txt
 /*ferro= {1,-1,1.40,"Ferro"},
 aluminio= {2,-1,7.80,"Aluminio"},
 vidro= {3,-1,12.50,"Vidro"},
 plastico= {4,-1,2.20,"Plástico"},
 borracha= {5,-1,1.50,"Borracha"},
 aco= {6,-1,3.30,"Aço"};*/

typedef struct stations 
{
  int id;
  char ops[3];
  int temp_ops[3];
  double cost;
  int temp_final;
}stations;

//Stations State
struct stations_use
{
  int used;
} st1 = {-1},st2 = {-1}, st3 = {-1}, st4 = {-1}, st5 = {-1};
  
//Cars
typedef struct car
{
  int id;
  char name[10];
  struct items
  {
    int carF;
    int carAl;
    int carV;
    int carP;
    int carB;
    int carAc;
  }item;
  int std;
  struct fab_proc
  {
    //Tempo restante
    int timeleft;
    //Ordem das operações originais
    char opso[3];
  }fabproc;
}car;

void lertxt(stock *stock_ptr[sizeof(stock)],int *countstock) {
  //int countF= 0, countAl= 0, countV= 0, countP= 0, countB= 0, countAc= 0;
  stock_ptr[*countstock] = malloc(sizeof(stock));
  int id;
  char name[20];
  float cost;
  char a;
  int noitem = 0;
  stock_ptr[*countstock]->amount = 1;
  //Leitura do stock.txt de modo a ver a quantidade inicial
  //ps: para atualizar existe no final um codigo que coloca todas as informações da estrutura para o stock.txt
  FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    do{
      fscanf(fp, "%d %s %f", &id, name, &cost);
      printf("scanf\n\n");
      if (*countstock == 0){
        stock_ptr[*countstock] -> id = id;
        strcpy(stock_ptr[*countstock] -> name, name);
        stock_ptr[*countstock] -> cost = cost;
        stock_ptr[*countstock+1] = malloc(sizeof(stock));
        *countstock++; 
        printf("Primeiro item\n\n");
      }
      else{
        printf("Else\n\n");
        for(int i = 0; i<*countstock; i++){
          printf("begin for\n\n");
          printf("i: %d",i);
          printf("stock_ptr compared %d\n",stock_ptr[i]->id);
          printf("id compared %d\n",id);
          if(stock_ptr[i]->id == id){
            noitem=0;
            stock_ptr[i]->amount += 1;
            printf("Added\n");
            break;
          }
          else{noitem=1;}
        }
        printf("End of for \n\n");
      }
        if(noitem==1){
          printf("olá1\n");
          printf("countstock before  %d",*countstock);
          printf("countstock after    %d",*countstock);
          printf("olá2\n\n");
          stock_ptr[*countstock] -> amount = 1;
          printf("amount\n");
          stock_ptr[*countstock] -> id = id;
          printf("stock_ptr2   %d\n\n",stock_ptr[2]->id);
          printf("id\n");
          printf("stock lido:%d     stock_ptr:%d\n\n\n",id,stock_ptr[*countstock]->id);
          strcpy(stock_ptr[*countstock] -> name, name);
          printf("nome\n");
          stock_ptr[*countstock] -> cost = cost;
          printf("cost\n");
          noitem = 0;
          stock_ptr[*countstock+1] = malloc(sizeof(stock));
          *countstock++;
        }
        printf("%d countstock\n\n",*countstock);
        printf("End of loop\n\n\n");
    }while((a=fgetc(fp))!=EOF);
    /*while(fgets(text,20,fp)){
      a = text[0];
      switch (a){
        case '1': countF++;break;
        case '2': countAl++;break;
        case '3': countV++;break;
        case '4': countP++;break;
        case '5': countB++;break;
        case '6': countAc++;break;
      }
    }*/
    fclose(fp);
  }
  //define o tamanho de cada elemento do vetor de pointers
 /* stock_ptr[0]= malloc(sizeof(ferro));
  stock_ptr[1]= malloc(sizeof(aluminio));
  stock_ptr[2]= malloc(sizeof(vidro));
  stock_ptr[3]= malloc(sizeof(plastico));
  stock_ptr[4]= malloc(sizeof(borracha));
  stock_ptr[5]= malloc(sizeof(aco));
  //define a quantidade de cada material na structure
  ferro.amount= countF;
  aluminio.amount= countAl;
  vidro.amount= countV;
  plastico.amount= countP;
  borracha.amount= countB;
  aco.amount= countAc;
  //aponta o stock_ptr pela ordem ao seu correspondente material
  stock_ptr[0]= &ferro;
  stock_ptr[1]= &aluminio;
  stock_ptr[2]= &vidro;
  stock_ptr[3]= &plastico;
  stock_ptr[4]= &borracha;
  stock_ptr[5]= &aco;
  */
}

// Read Files Function -> Stores in strings
void r_files(car *processing[sizeof(car)],int queue, char *stationsv){
  //Process.txt variables
  char carname[15];
  char processstate[15];
  char processesleft[6];
  char local;
  int  timel;
  //Auxiliary variables (Check for EOF)
  char aux;
  char aux1;
  //Create a temporary car imported from carmodel.txt(database of all cars) 
  struct car tempcar;
  FILE *fp;
  FILE *cp;
  //Abrir processing.txt
  fp = fopen("files/processing.txt","r");
  if (fp!=NULL){
    do{
    int i=0;
    fscanf(fp,"%s %s %c %d %s",carname ,processstate, &local, &timel, processesleft);
    if((strcmp(processstate,"Processing")==0)||(strcmp(processstate,"Waiting")==0)){
      // Changed from '-' to '0' for easy compreension
      if (local == '-'){local = '0';}
      //Opened carmodel.txt to compare to the car currently being used on this loop of processing.txt
      cp = fopen("files/carmodel.txt","r");
      if(cp!=NULL){
        do{
          fscanf(cp,"%d %s %d %d %d %d %d %d %d %d %s", &tempcar.id ,tempcar.name, &tempcar.item.carF, &tempcar.item.carAl, &tempcar.item.carV, &tempcar.item.carP, &tempcar.item.carB, &tempcar.item.carAc, &tempcar.std, &tempcar.fabproc.timeleft, tempcar.fabproc.opso);
          //If the car in carmode.txt is equal to the car in processing.txt we store it in a queue of cars and change to the current information
          if (strcmp(tempcar.name, carname)==0){
            processing[queue]->id = tempcar.id;
            strcpy(processing[queue]->name, tempcar.name);
            processing[queue]->item.carF = tempcar.item.carF;
            processing[queue]->item.carAl = tempcar.item.carAl;
            processing[queue]->item.carV = tempcar.item.carV;
            processing[queue]->item.carP = tempcar.item.carP;
            processing[queue]->item.carB = tempcar.item.carB;
            processing[queue]->item.carAc = tempcar.item.carAc;
            processing[queue]->std = tempcar.std;
            processing[queue]->fabproc.timeleft = tempcar.fabproc.timeleft;
            strcpy(processing[queue]->fabproc.opso, tempcar.fabproc.opso);
          }

        }while((aux1 = fgetc(cp))!=EOF);
      }
      fclose(cp);
      processing[queue+1] = malloc(sizeof(car));
      queue++;
    } 
    }while((aux = fgetc(fp))!= EOF);
    fclose(fp);
  }
  
}

void view_stock(stock *stock_ptr[sizeof(stock)],float ct, int *countstock) {
  system("clear");
  char user;
  //Esta confusão é o printf da interface do view stock que vai buscar a informação à estrutura.
  do {
  //menu stock
    printf("        ***STOCK***         \n\n");
    printf("ID   Type       Price    Qt.\n\n");
    for(int i = 0; i< *countstock; i++){
      printf("%d   %s        %.2f  %d", stock_ptr[i]->id, stock_ptr[i]->name, stock_ptr[i]->cost, stock_ptr[i]->amount);
    }
    printf("\n");
    printf("Total cost: %.2f€\n\n",ct);
    getchar();
    scanf("%c", &user);
  } while(user != '\n');
}

void refill_stock(stock *stock_ptr[sizeof(stock)]) {
    system("clear");
    int user_id;
    int user_qnt;
    //pede ao user o id do material e a quantidade do dito.
    printf("Escolha um id\n   1- ferro\n   2- aluminio\n   3- vidro\n   4- plastico\n   5- borracha\n   6- aço\n Opção:");
    scanf("%d", &user_id);
    printf("%s selected\n",(*stock_ptr[user_id-1]).name);
    printf("Quanto deseja adicionar?\n");
    scanf("%d", &user_qnt);
    //Adicionar a quantidade de um material à estrutura que o user escolher.
    stock_ptr[user_id-1]->amount += user_qnt;
}

void carP(car *processing[sizeof(car)],int queue, char *stationsv){
  r_files(processing,queue,stationsv);
  system("clear");
  int choice;
  char aux;
  
  char name[15];
  int id;
  
  car newcar;
  printf("\n\tEscolha o carro que pretende produzir:\n");
  FILE *cp;
  cp = fopen("files/carmodel.txt","r");
  if(cp!=NULL){
    do{
      fscanf(cp,"%d %s %*d %*d %*d %*d %*d %*d %*d %*d %*s",&id,name);
      printf("%d %s\n", id, name);
    }while((aux=fgetc(cp))!=EOF);
  }
  fclose(cp);
  printf("Sua opção: ");
  scanf("%d", &choice);
  cp = fopen("files/carmodel.txt","r");
  if(cp!=NULL){
  for(int i=0;i<choice;i++){
    fscanf(cp,"%d %s %d %d %d %d %d %d %d %d %s",&newcar.id,newcar.name,&newcar.item.carF,&newcar.item.carAl,&newcar.item.carV,&newcar.item.carP,&newcar.item.carB,&newcar.item.carAc,&newcar.std,&newcar.fabproc.timeleft,newcar.fabproc.opso);
  }
  processing[queue]->id = newcar.id;
  strcpy(processing[queue]->name, newcar.name);
  processing[queue]->item.carF = newcar.item.carF;
  processing[queue]->item.carAl = newcar.item.carAl;
  processing[queue]->item.carV = newcar.item.carV;
  processing[queue]->item.carP = newcar.item.carP;
  processing[queue]->item.carB = newcar.item.carB;
  processing[queue]->item.carAc = newcar.item.carAc;
  processing[queue]->std = newcar.std;
  processing[queue]->fabproc.timeleft = newcar.fabproc.timeleft;
  strcpy(processing[queue]->fabproc.opso, newcar.fabproc.opso);
  }
  fclose(cp);
  FILE *fp;
  fp = fopen("files/processing.txt", "a");
  if(fp!=NULL){
    fprintf(fp,"\n%s Waiting - 0 %s",processing[queue]->name,processing[queue]->fabproc.opso);
  }
  fclose(fp);
  processing[queue+1] = malloc(sizeof(car));
  queue++;
}

void ler_stations(stations station[5]) {

    FILE *fp;
    fp= fopen("files/stations.dat","rb");
    if(fp!=NULL) {
        fread(station,sizeof(stations),5,fp);    
    }
    fclose(fp);
}

void build_car_display() {
//display da opção 3 (display car)
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
//display da opção 4 (factory state)
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
//display da opção 5 (stats)
  printf("        ***Factory Stats Menu***         \n\n");
  printf("  1 - Finished products by type\n");
  printf("  2 - Products state\n");
  printf("  3 - Stations cost\n\n");
  printf("  B - Back\n\n");
  printf("Opção: ");
}

void menu_display() {
//display do menu principal
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

void factory_state_interface() {
  system("clear");
  char user;
  do {
    factory_state_display();
    scanf(" %s", &user);
//dá a hipotese do user ir utilizar cada opção do menu que diz factory state (opção 4)
    switch(user) {
      case '1': break;
      case '2': break;
      case '3': break;
      case '4': break;
      case '5': break;
      case '6': break;
      default: system("clear");
               continue;

    }
  }while(user != 'B' && user != 'b');
}

void stats_interface() {
  system("clear");
  char user;
    
      do {
        stats_display();
        scanf(" %c", &user);
//dá a hipotese do user ir utilizar cada opção do menu que diz stats (opção 5)
      switch(user) {
        case '1': break;
        case '2': break;
        case '3': break;
        default:system("clear"); 
                continue;
    }
  }while(user != 'B' && user != 'b');
}

void main(){
  int queue=0;
  char *user = calloc(1000, sizeof(char));
  char *stationsv= calloc(1000, sizeof(char));
  stations station[5];
  car *processing[sizeof(car)];
  float custo_total= 0;
  stock *stock_ptr[sizeof(stock)];
  int stockcount = 0;
  int *countstock;
  countstock = &stockcount;
  lertxt(stock_ptr,countstock);
  r_files(processing,queue,stationsv);
  ler_stations(station);
  do {
    system("clear");
    menu_display();
    //Allow the option to be only one character long
    scanf(" %s", user);
    if(strlen(user)>1){continue;}
    printf("\n");
    switch(*user) {
      case '1': custo_total= 0;
                for(int i= 0; i < *countstock; i++)
                   custo_total += ((*stock_ptr[i]).cost)*((*stock_ptr[i]).amount);
                view_stock(stock_ptr, custo_total,countstock);
                system("clear");
                break;
      case '2': refill_stock(stock_ptr);
                system("clear");
                break;
      case '3': carP(processing,queue,stationsv);
                system("clear");
                break;
      case '4': factory_state_interface();
                system("clear");
                break;
      case '5': stats_interface();
                system("clear");
                break;
      case '6': break;
      default: continue;
    } 
  } while(strchr(user,'E')== 0 && strchr(user,'e')==0);
  printf("Exiting...\n");
}