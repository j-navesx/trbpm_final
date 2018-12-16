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
typedef struct stations_use
{
  int used;
  char operations;
  char carname[10];
  char opName[15];
  char state[15];
} stations_use;

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
  char processstate[20];
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
        stock_ptr[*countstock] -> amount = 1;
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
void r_files(car *processing[sizeof(car)], char *stationsv, int *countstock, stock *stock_ptr[sizeof(stock)], int *queue){
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
  processing[*queue] = malloc(sizeof(car));
  printf("queue: %d\n\n", *queue);
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
                printf("queue: %d\n\n", *queue);
                printf("tempcar id2:%d\n\n ",tempcar.id );
                processing[*queue]->id = tempcar.id;
                printf("processing:%d\n\n ",processing[*queue]->id);
                strcpy(processing[*queue]->name, carname);
                printf("Name %d : %s\n\n",*queue, processing[*queue]->name);
              //  processing[queue]->itemcar[i].id = itemtemp[i]->id;
                printf("1\n\n");
              // processing[queue]->itemcar[i].amount = itemtemp[i]->amount;
                printf("2\n\n");
                processing[*queue]->std = local-48;
                printf("3\n\n");
                processing[*queue]->fabproc.timeleft = timel;
                strcpy(processing[*queue]->processstate, processstate);
                printf("4\n\n");
                strcpy(processing[*queue]->fabproc.opso, processesleft);
                printf("5\n\n");
                processing[*queue+1] = malloc(sizeof(car));
                *queue += 1; 
              }
            }while((aux1 = fgetc(cp))!=EOF);
          }
      fclose(cp);
      
      
    }
    }while((aux = fgetc(fp))!= EOF);
    fclose(fp);
  }
  
}

void r_finished(car *finished[sizeof(car)], int *finish){
  char carname[15];
  char processstate[15];
  //Auxiliary variables (Check for EOF)
  char aux;
  //Create a temporary car imported from carmodel.txt(database of all cars) 
  struct car tempcar;
  FILE *fp;
  //Abrir processing.txt
  finished[*finish] = malloc(sizeof(car));
  fp = fopen("files/processing.txt","r");
  if (fp!=NULL){
    do{
    int i=0;
    fscanf(fp,"%s %s %*c %*d %*s",carname ,processstate);
    if(strcmp(processstate, "Finished") == 0){
      strcpy(finished[*finish]->name,carname);
      finished[*finish+1] = malloc(sizeof(car));
      *finish += 1;
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

void carP(car *processing[sizeof(car)], char *stationsv,int *countstock, stock *stock_ptr[sizeof(stock)], int *queue){
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
  (newcar.itemcar) = malloc(sizeof(item)*(*countstock));
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
    processing[*queue]->id = newcar.id;
    strcpy(processing[*queue]->name, newcar.name);
    for(int i=0;i<*countstock; i++){
      (processing[*queue]->itemcar) = malloc(sizeof(item)*(*countstock));
      processing[*queue]->itemcar[i].id = newcar.itemcar[i].id;
      processing[*queue]->itemcar[i].amount = newcar.itemcar[i].amount;
    }
    processing[*queue]->std = newcar.std;
    processing[*queue]->fabproc.timeleft = newcar.fabproc.timeleft;
    strcpy(processing[*queue]->fabproc.opso, newcar.fabproc.opso);
    strcpy(processing[*queue]->processstate, "Waiting");
  
    FILE *fp;
    fp = fopen("files/processing.txt", "a");
    if(fp!=NULL){
      fprintf(fp,"\n%s Waiting - 0 %s",processing[*queue]->name,processing[*queue]->fabproc.opso);
    }
    fclose(fp);
    
  }
  else{
    }
  }
  processing[*queue+1] = malloc(sizeof(car));
  *queue += 1;
} 

void ler_stations(stations station[5]) {

    FILE *fp;
    fp= fopen("files/stations.dat","rb");
    if(fp!=NULL) {
        fread(station,sizeof(stations),5,fp);    
    }
    fclose(fp);
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

void Search_by_state(car *processing[], int *queue, car *finished[sizeof(car)], int *finish) {
  char user_str[20];
  char user;
  char aux;

  printf("State: ");
  getchar();
  scanf("%s", user_str);

  system("clear");
  do {
    printf("\t\t  ***Produtions***\n\n");
    printf("Type \t\t State \t\t Local \t Time left \t ops.\n\n");
    for(int i= 0; i < *queue; i++) {
      if(strcmp(user_str,processing[i]->processstate) == 0) {
        if(processing[i]->std == 0) {aux = '-';}
        else {aux = processing[i]->std + 48;}
        printf("%s    \t %s \t   %c \t     %d    \t %s\n", processing[i]->name, processing[i]->processstate, aux, processing[i]->fabproc.timeleft, processing[i]->fabproc.opso);
      }
    }
    for(int j= 0; j< *finish; j++) {
        if(strcmp(user_str,"Finished") == 0) {
        printf("%s    \t Finished \t   - \t     0    \t ---\n", finished[j]->name);
        }
    }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

void Search_by_type(car *processing[], int *queue, car *finished[sizeof(car)], int *finish) {
  char user_str[20];
  char user;
  char aux;

  printf("Type: ");
  getchar();
  scanf("%s", user_str);

  system("clear");
  do {
    printf("\t\t  ***Produtions***\n\n");
    printf("Type \t\t State \t\t Local \t Time left \t ops.\n\n");
    for(int i= 0; i < *queue; i++) {
      if(strcmp(user_str,processing[i]->name) == 0) {
        if(processing[i]->std == 0) {aux = '-';}
        else {aux = processing[i]->std + 48;}
        printf("%s    \t %s \t   %c \t     %d    \t %s\n", processing[i]->name, processing[i]->processstate, aux, processing[i]->fabproc.timeleft, processing[i]->fabproc.opso);
      }
    }
    for(int j= 0; j< *finish; j++) {
        if(strcmp(user_str,finished[j]->name) == 0) {
        printf("%s    \t Finished \t   - \t     0    \t ---\n", finished[j]->name);
        }
    }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

void processes_display(car *processing[], int *queue, int *finish, car *finished[]) {
  char user;
  char aux;
  
  system("clear");
  do {
    printf("\t\t  ***Produtions***\n\n");
    printf("Type \t\t State \t\t Local \t Time left \t ops.\n\n");
    for (int i= 0; i < *queue; i++) {
      if(processing[i]->std == 0) {aux = '-';}
      else {aux = processing[i]->std + 48;}
      printf("%s    \t %s \t   %c \t     %d    \t %s\n", processing[i]->name, processing[i]->processstate, aux, processing[i]->fabproc.timeleft, processing[i]->fabproc.opso);
    }
    for(int j= 0; j < *finish; j++) {
      printf("%s    \t Finished \t   - \t     0    \t ---\n", finished[j]->name);
      }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
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

void factory_state_interface(stations station[5], stations_use st[5], car *processing[sizeof(car)], int *queue, car *finished[sizeof(car)], int *finish) {
  system("clear");
  char user;
  do {
    factory_state_display();
    scanf(" %s", &user);
  //dá a hipotese do user ir utilizar cada opção do menu que diz factory state (opção 4)
    switch(user) {
      case '1': processes_display(processing,queue,finish,finished);
                break;
      case '2': Search_by_type(processing,queue,finished,finish);
                break;
      case '3': Search_by_state(processing,queue,finished,finish);
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
void time_skip(int currenttime,car *processing[sizeof(car)],int *finish, int *queue,car *finished[sizeof(car)], stock *stock_ptr[sizeof(stock)], int *countstock){
  FILE *pr;
  FILE *stck;
  FILE *std;
  int timeadded;
  printf("%s\n", finished[0]->name);
  printf("Insira o tempo que pretende que passe (em minutos): ");
  scanf("%d", &timeadded);
  for(int t=0; t<timeadded; t++){
    currenttime += 1;
    for(int i=0; i< *queue; i++){
      if((processing[i]->std != 0) && (processing[i]->std != -1)){
        processing[i]->fabproc.timeleft -= 1;
        if(strcmp(processing[i]->fabproc.opso, "---") == 0){
          strcpy(finished[*finish]->name , processing[i]->name);
          finished[*finish+1] = malloc(sizeof(car));
          *finish += 1;
          strcpy(processing[i]->name , "-");
          pr = fopen("file/processing.txt","w+");
          if(pr == NULL){
            for(int j=0; j<*finish; j++){
              fprintf(pr,"%s Finished - 0 ---\n",finished[j]->name);
            }
            for(int j=0; j< *queue; j++){
              if((processing[j]->std != 0) && (strcmp(processing[j]->name , "-")!=0)){
                fprintf(pr,"%s Processing %d %d %s",processing[j]->name, processing[j]->std, processing[j]->fabproc.timeleft, processing[j]->fabproc.opso);
              }
              if((processing[j]->std == 0)&&(strcmp(processing[j]->name , "-")!=0)){
                fprintf(pr,"%s Waiting - 0 %s",processing[j]->name, processing[j]->fabproc.opso);
              }
              if(j != *queue-1){
                fprintf(pr,"\n");
              }
            }
            fclose(pr);
          }
        }
      
      }
    }
  }
  //*countstock = 0;
  //*queue = 0;
  //*finish = 0;
  //free(stock_ptr);
  //free(processing);
  //free(finished);
}

void stations_process(stations_use st[5]) {
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
  int currenttime=0;
  int queuecount= 0;
  int *queue= &queuecount;
  int fin=0;
  int fincount= 0;
  int *finish= &fincount;
  char *user = calloc(1000, sizeof(char));
  char *stationsv= calloc(1000, sizeof(char));
  stations station[5];
  stations_use st[5];
  car *processing[sizeof(car)];
  car *finished[sizeof(car)];
  float custo_total= 0;
  stock *stock_ptr[sizeof(stock)];
  int stockcount = 0;
  int *countstock;
  countstock = &stockcount;
  //car.itemcar = malloc(sizeof(item));
  lertxt(stock_ptr,countstock);
  r_files(processing,stationsv,countstock,stock_ptr,queue);
  r_finished(finished,finish);
  ler_stations(station);
  stations_process(st);
  printf("%d\n",*queue);
  printf("%d\n",*finish);
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
      case '3': carP(processing,stationsv,countstock,stock_ptr,queue);
                system("clear");
                break;
      case '4': factory_state_interface(station,st,processing,queue,finished,finish);
                system("clear");
                break;
      case '5': stats_interface();
                system("clear");
                break;
      case '6': time_skip(currenttime, processing, finish, queue, finished,stock_ptr, countstock);
                break;
      default: continue;
    } 
  } while(strchr(user,'E')== 0 && strchr(user,'e')==0);
  printf("Exiting...\n");
}