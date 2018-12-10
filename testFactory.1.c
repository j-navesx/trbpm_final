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

typedef struct processing_info {
  char name[20];
  char processstate[20];
  char std;
  int timel;
  char ops[5];
}processing_info;

typedef struct stations
{
  int id;
  char ops[3];
  int temp_ops[3];
  double cost;
  int temp_final;
}stations;

//Stations State
typedef struct stations_use
{
  int used;
  char operations;
  char carname[10];
  char opName[15];
  char state[15];
} stations_use;
  
//Cars
typedef struct car
{
  int id;
  char name[10];
  char processstate[20];
  char std;
  struct items
  {
    int carF;
    int carAl;
    int carV;
    int carP;
    int carB;
    int carAc;
  }item;
  struct fab_proc
  {
    //Tempo restante
    int timeleft;
    char ops[3];
  }fabproc;
}car;

/*void ler_processing(processing_info *processesInfo[], int *countProdution_ptr) {
  int count= 0;
  char aux;
  char name[20], processstate[20], std, processesleft[5];
  int timeleft;

  FILE *ptr;
  ptr= fopen("files/processing.txt","r");
  do {
    processesInfo[count]= malloc(sizeof(processing_info));
    fscanf(ptr,"%s %s %c %d %s", name, processstate, &std, &timeleft, processesleft);
    strcpy((*processesInfo[count]).name,name);
    strcpy(processesInfo[count]->processstate,processstate);
    processesInfo[count]->std= std;
    processesInfo[count]->timel= timeleft;
    strcpy(processesInfo[count]->ops,processesleft);
    count++;
  }while(aux= fgetc(ptr) != EOF);
  fclose(ptr);
  *countProdution_ptr= count;
}*/

void lertxt(stock *stock_ptr[sizeof(stock)],int *countstock) {
  stock_ptr[*countstock] = malloc(sizeof(stock));
  int id;
  char name[20];
  float cost;
  char a;
  int i;
  int dif;
  stock_ptr[*countstock]->amount = 1;
  FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    do{
      fscanf(fp,"%d %s %f", &id, name, &cost);
      stock_ptr[*countstock]->id= id;
      strcpy(stock_ptr[*countstock]->name,name);
      stock_ptr[*countstock]->cost= cost;
      if(*countstock == 0) {
         *countstock += 1;
         stock_ptr[*countstock] = malloc(sizeof(stock));
         stock_ptr[*countstock]->amount = 1;
      }
      else {
        for(i= 0, dif= 0; (i < *countstock) && (dif != *countstock); i++) {
          if(stock_ptr[i]->id != stock_ptr[*countstock]->id) {
             dif++;
          }  
          else {
            (stock_ptr[i]->amount)++;
          } 
        }
        if(dif == *countstock) {
            *countstock += 1;
            stock_ptr[*countstock] = malloc(sizeof(stock));
            stock_ptr[*countstock]->amount = 1;
          }
      }
    }while((a=fgetc(fp))!=EOF);
    fclose(fp);
  }
}

// Read Files Function -> Stores in strings
void r_files(car *processing[sizeof(car)],int queue, char *stationsv, int *countProdution_ptr, int *finishcount){
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
  processing[queue]= malloc(sizeof(car));
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
      //Opened carmodel.txt to compare to the car currently being used on this loop of processing.txt
      cp = fopen("files/carmodel.txt","r");
      if(cp!=NULL){
        do{
          fscanf(cp,"%d %s %d %d %d %d %d %d %c %d %s", &tempcar.id ,tempcar.name, &tempcar.item.carF, &tempcar.item.carAl, &tempcar.item.carV, &tempcar.item.carP, &tempcar.item.carB, &tempcar.item.carAc, &tempcar.std, &tempcar.fabproc.timeleft, tempcar.fabproc.ops);
          //If the car in carmode.txt is equal to the car in processing.txt we store it in a queue of cars and change to the current information
          if (strcmp(tempcar.name, carname)==0){
            processing[queue]->id = tempcar.id;
            strcpy(processing[queue]->name, tempcar.name);
            strcpy(processing[queue]->processstate,processstate);
            processing[queue]->item.carF = tempcar.item.carF;
            processing[queue]->item.carAl = tempcar.item.carAl;
            processing[queue]->item.carV = tempcar.item.carV;
            processing[queue]->item.carP = tempcar.item.carP;
            processing[queue]->item.carB = tempcar.item.carB;
            processing[queue]->item.carAc = tempcar.item.carAc;
            processing[queue]->std = local;
            processing[queue]->fabproc.timeleft = timel;
            strcpy(processing[queue]->fabproc.ops, processesleft);
          }

        }while((aux1 = fgetc(cp))!=EOF);
      }
      fclose(cp);
      processing[queue+1] = malloc(sizeof(car));
      queue++;
    }
    else {
      strcpy(processing[queue]->name,carname);
      strcpy(processing[queue]->processstate,processstate);
      processing[queue]->std= local;
      processing[queue]->fabproc.timeleft= timel;
      strcpy(processing[queue]->fabproc.ops,processesleft);
      processing[queue+1] = malloc(sizeof(car));
      queue++;
      *finishcount += 1;
    } 
    }while((aux = fgetc(fp))!= EOF);
    fclose(fp);
  }
  *countProdution_ptr= queue;
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
      printf("%d   %s \t %.2f \t %d\n", stock_ptr[i]->id, stock_ptr[i]->name, stock_ptr[i]->cost, stock_ptr[i]->amount);
    }
    printf("\n");
    printf("Total cost: %.2f€\n\n",ct);
    getchar();
    scanf("%c", &user);
  } while(user != '\n');
}

void refill_stock(stock *stock_ptr[sizeof(stock)], int *countstock) {
  char a;
  char text[20];
  char aux[60]= "files/";
  char usertext[50];
  int i;

  printf("filename: ");
  scanf("%s", usertext);
  printf("\n");
  strcat(aux,usertext);
  FILE *fp;
  fp = fopen(aux,"r");
  if (fp!=NULL){  
    while(fgets(text,20,fp)){
      a = text[0];
      for(i= 0; i < *countstock; i++) {
        if(a-48 == stock_ptr[i]->id) {
          stock_ptr[i]->amount += 1;
        }
      }
    }
    fclose(fp);
  }
}

void carP(car *processing[sizeof(car)],int queue, char *stationsv, int *countProdution_ptr, int *finishcount){
  r_files(processing,queue,stationsv,countProdution_ptr,finishcount);
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
  for(int i=0;i<=choice;i++){
    fscanf(cp,"%d %s %d %d %d %d %d %d %c %d %s",&newcar.id,newcar.name,&newcar.item.carF,&newcar.item.carAl,&newcar.item.carV,&newcar.item.carP,&newcar.item.carB,&newcar.item.carAc,&newcar.std,&newcar.fabproc.timeleft,newcar.fabproc.ops);
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
  strcpy(processing[queue]->fabproc.ops, newcar.fabproc.ops);
  }
  fclose(cp);
  FILE *fp;
  fp = fopen("files/processing.txt", "a");
  if(fp!=NULL){
    fprintf(fp,"\n%s Waiting - 0 %s",processing[queue]->name,processing[queue]->fabproc.ops);
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

void machine_info_display(stations station[5]) {
  system("clear");

  char user;

  do {
  printf("       ***Stations***         \n\n");
  printf("ID \t Operations \t Durations \t Cost.Min \t Oper.Time\n\n");
  for(int i= 0; i < 5; i++) {
    printf("%d \t %c-%c-%c \t\t %d-%d-%d \t %.2f \t\t %d\n",station[i].id, station[i].ops[0], station[i].ops[1],
     station[i].ops[2], station[i].temp_ops[0], station[i].temp_ops[1], station[i].temp_ops[2], station[i].cost,
     station[i].temp_final);
  }
  printf("\n");
  getchar();
  scanf("%c", &user);
  }while(user != '\n');
}

void build_car_display() {
  system("clear");
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
  system("clear");
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
  system("clear");
  //display da opção 5 (stats)
  printf("        ***Factory Stats Menu***         \n\n");
  printf("  1 - Finished products by type\n");
  printf("  2 - Products state\n");
  printf("  3 - Stations cost\n\n");
  printf("  B - Back\n\n");
  printf("Opção: ");
}

void menu_display() {
  system("clear");
  //display do menu principal
  printf("\n    \t***Factory Admin Menu***\n\n");
  printf("1- Show stock\n");
  printf("2- Refill stock\n");
  printf("3- Build car\n");
  printf("4- Factory State\n");
  printf("5- Stats\n");
  printf("6- Time skip\n\n");
  printf("E- Exit\n\n");
  printf("Option: ");
}

void map_display(stations_use st[5]) {
  system("clear");
  char user;

  do {
  printf("\n       ***Factory Map***\n\n");
  printf("   1     2     3     4     5   \n");
  printf(" ----- ----- ----- ----- ----- \n");
  printf("|  %c  |  %c  |  %c  |  %c  |  %c  |\n",st[0].operations,st[1].operations,st[2].operations,st[3].operations,st[4].operations);
  printf(" ----- ----- ----- ----- ----- \n\n");
  getchar();
  scanf("%c",&user);
  }while(user != '\n');
}

void machine_state_display(stations_use st[5]) {
  system("clear");
  char user;
  int i;

  do {
    printf("\n       ***Factory_State***\n\n");
    printf("\t\t   State \t    Type \t    Op.\n\n");
    for(i= 0; i<5 ; i++) {
      printf("Station Nº:%d \t %s \t   %s \t   %s\n",i+1,st[i].state, st[i].carname, st[i].opName);
    }
    getchar();
    scanf("%c",&user);
  }while(user != '\n');
}

void Search_by_state(car *processing[], int *countProdution_ptr) {
  char user_str[20];
  char user;

  printf("State: ");
  getchar();
  scanf("%s", user_str);
  /*ler_processing(processesInfo,countProdution_ptr);*/

  system("clear");
  do {
    printf("\t\t  ***Produtions***\n\n");
    printf("Type \t\t State \t\t Local \t Time left \t ops.\n\n");
    for(int i= 0; i < *countProdution_ptr; i++) {
      if(strcmp(user_str,processing[i]->processstate) == 0) {
        printf("%s    \t %s \t   %c \t     %d    \t %s\n", processing[i]->name, processing[i]->processstate, processing[i]->std, processing[i]->fabproc.timeleft, processing[i]->fabproc.ops);
      }
    }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

void Search_by_type(car *processing[], int *countProdution_ptr) {
  char user_str[20];
  char user;

  printf("Type: ");
  getchar();
  scanf("%s", user_str);
  /*ler_processing(processesInfo,countProdution_ptr);*/
  printf("%d\n", *countProdution_ptr);

  system("clear");
  do {
    printf("\t\t  ***Produtions***\n\n");
    printf("Type \t\t State \t\t Local \t Time left \t ops.\n\n");
    for(int i= 0; i < *countProdution_ptr; i++) {
      if(strcmp(user_str,processing[i]->name) == 0) {
        printf("%s    \t %s \t   %c \t     %d    \t %s\n", processing[i]->name, processing[i]->processstate, processing[i]->std, processing[i]->fabproc.timeleft, processing[i]->fabproc.ops);
      }
    }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

void processes_display(car *processing[], int *countProdution_ptr) {
  char user;
  
  system("clear");
  do {
    printf("\t\t  ***Produtions***\n\n");
    printf("Type \t\t State \t\t Local \t Time left \t ops.\n\n");
    for (int i= 0; i < *countProdution_ptr; i++) {
      printf("%s    \t %s \t   %c \t     %d    \t %s\n",processing[i]->name,processing[i]->processstate,processing[i]->std,processing[i]->fabproc.timeleft,processing[i]->fabproc.ops);
    }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

void factory_state_interface(stations station[5], stations_use st[5], car *processing[sizeof(car)], processing_info *processesInfo[], int *countProdution_ptr) {
  system("clear");
  char user;
  do {
    factory_state_display();
    scanf(" %s", &user);
  //dá a hipotese do user ir utilizar cada opção do menu que diz factory state (opção 4)
    switch(user) {
      case '1': processes_display(processing,countProdution_ptr);
                break;
      case '2': Search_by_type(processing,countProdution_ptr);
                break;
      case '3': Search_by_state(processing,countProdution_ptr);
                break;
      case '4': machine_state_display(st);
                break;
      case '5': machine_info_display(station);
                break;
      case '6': map_display(st);
                break;
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
        default: system("clear"); 
                 continue;
    }
  }while(user != 'B' && user != 'b');
}

void stations_process(car *processing[sizeof(car)],stations_use st[5]) {
  char aux;
  int countaux= 0;
  int i,j,h,k;
  int count=0;
  char name[10], processstate[10], std, processesleft[5];
  int timeleft;

  for(j= 0; j < 5; j++) {
    st[j].used= -1;
    strcpy(st[j].carname,"   -");
    strcpy(st[j].opName,"   -");
  }
  FILE *fp;
  fp= fopen("files/processing.txt","r");
  do {
    fscanf(fp,"%s %s %c %d %s", name, processstate, &std, &timeleft, processesleft);
    if(std != '-') {
      for(i= 0; i < 3; i++) {
        if(processesleft[i] != '-') {
          strcpy(st[std-48-1].carname,name);
          st[std-48-1].operations= processesleft[i];
          break;
        }
      }
      st[std-48-1].used= 1;
    }
  }while(aux= fgetc(fp) != EOF);
  fclose(fp);
  for(k= 0; k<5 ; k++) {
    if(st[k].operations < 'A' || st[k].operations > 'E') {
      st[k].operations= '-';
    }
  }
  for(h= 0; h<5 ; h++) {
    switch(st[h].operations) {
      case 'A': strcpy(st[h].opName,"Soldering"); break;
      case 'B': strcpy(st[h].opName,"Cuting"); break;
      case 'C': strcpy(st[h].opName,"Painting"); break;
      case 'D': strcpy(st[h].opName,"Assembling"); break;
      case 'E': strcpy(st[h].opName,"Finishing"); break;
      default: strcpy(st[h].opName,"-"); break;
    }
    if(st[h].used == -1) {
      strcpy(st[h].state,"   Idle");
    }
    else {
      strcpy(st[h].state,"Processing");
    }
  }
}

void main(){
  int queue=0;
  int fin= 0;
  int *finishcount= &fin;
  char *user = calloc(1000, sizeof(char));
  char *stationsv= calloc(1000, sizeof(char));
  int countprodution;
  int *countProdution_ptr= &countprodution;
  stations_use st[5];
  stations station[5];
  car *processing[sizeof(car)];
  processing_info *processesInfo[sizeof(processing_info)];
  float custo_total= 0;
  stock *stock_ptr[sizeof(stock)];
  int stockcount = 0;
  int *countstock;
  countstock = &stockcount;
  lertxt(stock_ptr,countstock);
  /*ler_processing(processesInfo,countProdution_ptr);*/
  ler_stations(station);
  r_files(processing,queue,stationsv,countProdution_ptr,finishcount);
  stations_process(processing,st);
  do {
    menu_display();
    //Allow the option to be only one character long
    scanf(" %s", user);
    if(strlen(user)>1){continue;}
    printf("\n");
    switch(*user) {
      case '1': custo_total= 0;
                printf("%d",*finishcount);
                for(int i= 0; i < *countstock; i++)
                   custo_total += ((*stock_ptr[i]).cost)*((*stock_ptr[i]).amount);
                view_stock(stock_ptr, custo_total,countstock);
                break;
      case '2': refill_stock(stock_ptr,countstock);
                break;
      case '3': carP(processing,queue,stationsv,countProdution_ptr,finishcount);
                break;
      case '4': factory_state_interface(station,st,processing,processesInfo,countProdution_ptr);
                break;
      case '5': stats_interface();
                break;
      case '6': break;
      default: system("clear");
               continue;
    } 
  } while(strchr(user,'E')== 0 && strchr(user,'e')==0);
  printf("Exiting...\n");
}