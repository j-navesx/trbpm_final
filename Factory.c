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

typedef struct item
{
  int id;
  int amount;
}item;

//Cars
typedef struct car
{
  int id;
  char name[10];
  struct item *itemcar;
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
  *countstock = 0;
  stock_ptr[*countstock] = malloc(sizeof(stock));
  int id;
  char name[20];
  float cost;
  char a;
  int noitem = 0;
  FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    do{
      fscanf(fp, "%d %s %f", &id, name, &cost);
      if (*countstock == 0){
        stock_ptr[*countstock] -> id = id;
        strcpy(stock_ptr[*countstock] -> name, name);
        stock_ptr[*countstock] -> cost = cost;
        stock_ptr[*countstock+1] = malloc(sizeof(stock));
        *countstock +=1; 
      }
      else{
        for(int i = 0; i<*countstock; i++){
          if(stock_ptr[i]->id == id){
            noitem=0;
            stock_ptr[i]->amount += 1;
            break;
          }
          else{noitem=1;}
        }
      }
      if(noitem==1){
        stock_ptr[*countstock] -> amount = 1;
        stock_ptr[*countstock] -> id = id;
        strcpy(stock_ptr[*countstock] -> name, name);
        stock_ptr[*countstock] -> cost = cost;
        noitem = 0;
        stock_ptr[*countstock+1] = malloc(sizeof(stock));
        *countstock += 1;
        }
    }while((a=fgetc(fp))!=EOF);
    fclose(fp);
  }
}
// Read Files Function -> Stores in strings
void r_files(car *processing[sizeof(car)],int queue, char *stationsv, int *countstock, stock *stock_ptr[sizeof(stock)]){
  //Process.txt variables
  item *itemtemp[sizeof(item)];
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
  processing[queue] = malloc(sizeof(car));
  printf("queue: %d\n\n", queue);
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
              fscanf(cp,"%d %s ", &tempcar.id ,tempcar.name);
              printf("tempcar:%d\n\n",tempcar.id);
              for (i=0;i<*countstock;i++){
                itemtemp[i]->id = (i+1);
                fscanf(cp,"%d ",&itemtemp[i]->amount);
                itemtemp[i+1] = malloc(sizeof(item));
              }
              fscanf(cp,"%d %d %s", &tempcar.std, &tempcar.fabproc.timeleft, tempcar.fabproc.opso);
              //If the car in carmode.txt is equal to the car in processing.txt we store it in a queue of cars and change to the current information
              if (strcmp(tempcar.name, carname)==0){
                printf("queue: %d\n\n", queue);
                printf("tempcar id2:%d\n\n ",tempcar.id );
                processing[queue]->id = tempcar.id;
                printf("processing:%d\n\n ",processing[queue]->id);
                strcpy(processing[queue]->name, carname);
                printf("Name %d : %s\n\n",queue, processing[queue]->name);
              //  processing[queue]->itemcar[i].id = itemtemp[i]->id;
                printf("1\n\n");
              // processing[queue]->itemcar[i].amount = itemtemp[i]->amount;
                printf("2\n\n");
                processing[queue]->std = local-48;
                printf("3\n\n");
                processing[queue]->fabproc.timeleft = timel;
                printf("4\n\n");
                strcpy(processing[queue]->fabproc.opso, processesleft);
                printf("5\n\n");
                processing[queue+1] = malloc(sizeof(car));
                queue++; 
              }
            }while((aux1 = fgetc(cp))!=EOF);
          }
      fclose(cp);
      
      
    }
    }while((aux = fgetc(fp))!= EOF);
    fclose(fp);
  }
  
}
void r_finished(car *finished[sizeof(car)], int fin){
  char carname[15];
  char processstate[15];
  //Auxiliary variables (Check for EOF)
  char aux;
  //Create a temporary car imported from carmodel.txt(database of all cars) 
  struct car tempcar;
  FILE *fp;
  //Abrir processing.txt
  finished[fin] = malloc(sizeof(car));
  fp = fopen("files/processing.txt","r");
  if (fp!=NULL){
    do{
    int i=0;
    fscanf(fp,"%s %s %*c %*d %*s",carname ,processstate);
    if(strcmp(processstate, "Finished") == 0){
      strcpy(finished[fin]->name,carname);
      finished[fin+1] = malloc(sizeof(car));
      fin++;
    }
    }while((aux = fgetc(fp))!= EOF);
    fclose(fp);
  }
}
void view_stock(stock *stock_ptr[sizeof(stock)],float ct, int *countstock) {
  system("clear");
  char user;
  int i;
  printf("countstock %d\n\n",*countstock);
  //Esta confusão é o printf da interface do view stock que vai buscar a informação à estrutura.
  do {
  //menu stock
    printf("        ***STOCK***         \n\n");
    printf("ID   Type       Price    Qt.\n\n");
    for(i = 0; i < *countstock; i++){
      printf("%d    %s  \t %.2f\t %d\n", stock_ptr[i]->id, stock_ptr[i]->name, stock_ptr[i]->cost, stock_ptr[i]->amount);
    }
    printf("\n");
    printf("Total cost: %.2f€\n\n",ct);
    getchar();
    scanf("%c", &user);
  } while(user != '\n');
}

void refill_stock(stock *stock_ptr[sizeof(stock)], int *countstock) {
    system("clear");
    int user_id;
    int user_qnt;
    //pede ao user o id do material e a quantidade do dito.
    printf("Escolha um id\n");
    for(int i=0; i<*countstock;i++){
      printf("%d %s\n", stock_ptr[i]->id, stock_ptr[i]->name);
    }
    printf("\nOpção: ");
    scanf("%d", &user_id);
    printf("%s selected\n",(stock_ptr[user_id-1])->name);
    printf("Quanto deseja adicionar?\n");
    scanf("%d", &user_qnt);
    //Adicionar a quantidade de um material à estrutura que o user escolher.
    stock_ptr[user_id-1]->amount += user_qnt;
}

void carP(car *processing[sizeof(car)],int queue, char *stationsv,int *countstock, stock *stock_ptr[sizeof(stock)]){
  system("clear");
  int choice;
  char answer;
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
  getchar();
  cp = fopen("files/carmodel.txt","r");
  if(cp!=NULL){
  for(int i=0;i<choice;i++){
    fscanf(cp,"%d %s ",&newcar.id,newcar.name);
    for (int j=0;j<*countstock;j++){
      newcar.itemcar[j].id = j+1;
      fscanf(cp,"%d ",&newcar.itemcar[j].amount);
    }
    fscanf(cp,"%d %d %s", &newcar.std,&newcar.fabproc.timeleft,newcar.fabproc.opso);
    }
  printf("\nAo produzir um %s vai usar os items listados abaixo: \n", newcar.name);
  for(int i=0;i<*countstock;i++){
    printf("\t%d ",newcar.itemcar[i].amount);
    for(int j=0;j<*countstock;j++){
      if(newcar.itemcar[i].id == stock_ptr[j]->id){printf("%s\n", stock_ptr[j]->name);}
    }
  }
  printf("\nTem a certeza que pretende continuar?: ");
  scanf("%c", &answer);
  if((answer == 'y')||(answer == 'Y')){
    for(int i =0;i<*countstock;i++){
      stock_ptr[i]->amount -= newcar.itemcar[i].amount;
    } 
    processing[queue]->id = newcar.id;
    strcpy(processing[queue]->name, newcar.name);
    for(int i=0;i<*countstock; i++){
      processing[queue]->itemcar[i].id = newcar.itemcar[i].id;
      processing[queue]->itemcar[i].amount = newcar.itemcar[i].amount;
      (processing[queue]->itemcar) = malloc(sizeof(item)*(*countstock));
    }
    processing[queue]->std = newcar.std;
    processing[queue]->fabproc.timeleft = newcar.fabproc.timeleft;
    strcpy(processing[queue]->fabproc.opso, newcar.fabproc.opso);
  
    FILE *fp;
    fp = fopen("files/processing.txt", "a");
    if(fp!=NULL){
      system("pwd");
      fprintf(fp,"\n%s Waiting - 0 %s",processing[queue]->name,processing[queue]->fabproc.opso);
    }
    fclose(fp);
    
  }
  else{
    system("clear");
    }
  }
  system("clear");
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
//display da opção 4 (factory o_to
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
//dá a hipotese do user ir utilizcar *processing[sizeof(car)],int queuecar *processing[sizeof(car)],int queuear cada opção do menu que diz stats (opção 5)
      switch(user) {
        case '1': break;
        case '2': break;
        case '3': break;
        default:system("clear"); 
                continue;
    }
  }while(user != 'B' && user != 'b');
}
void time_skip(int currenttime,car *processing[sizeof(car)],int queue,car *finished[sizeof(car)],int fin){
  int timeadded;
  printf("Insira o tempo que pretende que passe (em minutos): ");
  scanf("%d", &timeadded);
  currenttime += timeadded;
  for(int i=0; i<queue; i++){
    if((processing[i]->std != 0) && (processing[i]->std != -1)){
      processing[i]->fabproc.timeleft -= timeadded;
      if(processing[i]->fabproc.timeleft <= 0){
        
      }
    }
  }
}
void main(){
  int currenttime=0;
  int queue=0;
  int fin=0;
  char *user = calloc(1000, sizeof(char));
  char *stationsv= calloc(1000, sizeof(char));
  stations station[5];
  car *processing[sizeof(car)];
  car *finished[sizeof(car)];
  float custo_total= 0;
  stock *stock_ptr[sizeof(stock)];
  int stockcount = 0;
  int *countstock;
  countstock = &stockcount;
  //car.itemcar = malloc(sizeof(item));
  lertxt(stock_ptr,countstock);
  r_files(processing,queue,stationsv,countstock,stock_ptr);
  r_finished(finished,fin);
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
      case '2': refill_stock(stock_ptr,countstock);
                system("clear");
                break;
      case '3': carP(processing,queue,stationsv,countstock,stock_ptr);
                system("clear");
                break;
      case '4': factory_state_interface();
                system("clear");
                break;
      case '5': stats_interface();
                system("clear");
                break;
      case '6': time_skip(currenttime, processing, queue, finished,fin);
                break;
      default: continue;
    } 
  } while(strchr(user,'E')== 0 && strchr(user,'e')==0);
  printf("Exiting...\n");
}