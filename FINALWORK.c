#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

//Structure for items in stock.txt
typedef struct stock 
{ 
  int id;
  int amount;
  float cost;
  char name[20];
}stock;

//Structure for data in stations.dat
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

//Structure of the items inside the car
typedef struct item
{
  int id;
  int amount;
}item;

//Structure of a car
typedef struct car
{
  int id;
  char name[10];
  struct item *itemcar;
  int std;
  char processstate[20];
  struct fab_proc
  {
    //Time to finish a operation
    int timeleft;
    //Cars operations left
    char opso[3];
  }fabproc;
}car;

//Fuction to read the stock.txt and store it in struct
void lertxt(stock *stock_ptr[sizeof(stock)],int *countstock) {
  //Pointer used to count the number of different item types that exist
  *countstock = 0;
  //Adding a space for a item
  stock_ptr[*countstock] = malloc(sizeof(stock));
  //Temporary variables to add to structure
  int id;
  char name[20];
  float cost;
  //Auxiliary variables
  char a;
  int noitem = 0;
  //Stock.txt opening
  FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    do{
      fscanf(fp, "%d %s %f", &id, name, &cost);
      //Adds the first item to the position 0
      if (*countstock == 0){
        stock_ptr[*countstock] -> id = id;
        strcpy(stock_ptr[*countstock] -> name, name);
        stock_ptr[*countstock] -> cost = cost;
        stock_ptr[*countstock] -> amount = 1;
        stock_ptr[*countstock+1] = malloc(sizeof(stock));
        *countstock +=1; 
      }
      else{
        //Verifies if the item already exist
        for(int i = 0; i<*countstock; i++){
          if(stock_ptr[i]->id == id){
            noitem=0;
            stock_ptr[i]->amount += 1;
            break;
          }
          else{noitem=1;}
        }
      }
      //If doesnt exist add
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

// Read the process.txt
void r_files(car *processing[sizeof(car)], char *stationsv, int *countstock, stock *stock_ptr[sizeof(stock)], int *queue){
  //Temporary variables to add to process.txt
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
  //Open processing.txt
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
                processing[*queue]->id = tempcar.id;
                strcpy(processing[*queue]->name, carname);
                processing[*queue]->std = local-48;
                processing[*queue]->fabproc.timeleft = timel;
                strcpy(processing[*queue]->processstate, processstate);
                strcpy(processing[*queue]->fabproc.opso, processesleft);
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

//Read the cars that are finished in process.txt and stores it in a diferent vector of structures
void r_finished(car *finished[sizeof(car)], int *finish){
  //Temporary Variables
  char carname[15];
  char processstate[15];
  //Auxiliary variables (Check for EOF)
  char aux;
  //Create a temporary car imported from carmodel.txt(database of all cars) 
  struct car tempcar;
  FILE *fp;
  finished[*finish] = malloc(sizeof(car));
  //Open processing.txt
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

//Function that prints the stock available
void view_stock(stock *stock_ptr[sizeof(stock)],float ct, int *countstock) {
  system("clear");
  char user;
  int i;
  do {
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

//Function to reffil the stock from the items listed in another file
void refill_stock(stock *stock_ptr[sizeof(stock)], int *countstock) {
  //Auxiliary and Temporary variables
  char a;
  char text[20];
  char aux[60]= "files/";
  char usertext[50];
  int i;
  //Ask for the file to reffil from
  printf("filename: ");
  scanf("%s", usertext);
  printf("\n");
  strcat(aux,usertext);
  //Opens the file we asked him and adds to the stock
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

//Car production menu
int carP(car *processing[sizeof(car)], char *stationsv,int *countstock, stock *stock_ptr[sizeof(stock)], int *queue){
  system("clear");
  //Auxiliary variables
  int choice;
  char answer;
  char aux;
  //Temporary variables
  char name[15];
  int id;
  car newcar;
  printf("\n\tEscolha o carro que pretende produzir:\n\n");
  //Opens carmodel.txt to display the cars we have available
  FILE *cp;
  cp = fopen("files/carmodel.txt","r");
  if(cp!=NULL){
    do{
      fscanf(cp,"%d %s ",&id,name);
      for (int j=0;j<*countstock;j++){
        fscanf(cp,"%*d ");
      }
      fscanf(cp,"%*d %*d %*s");
      printf("%d %s\n", id, name);
    }while((aux=fgetc(cp))!=EOF);
  }
  fclose(cp);
  printf("Sua opção: ");
  getchar();
  choice= getchar();
  if(choice == 'b'){return 0;}
  //Opens car carmodel.txt to store the car we asked him in a temporary car for further adding
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
  //Informs the user of how many items is going to use
  printf("\nAo produzir um %s vai usar os items listados abaixo: \n", newcar.name);
  for(int i=0;i<*countstock;i++){
    printf("\t%d ",newcar.itemcar[i].amount);
    for(int j=0;j<*countstock;j++){
      if(newcar.itemcar[i].id == stock_ptr[j]->id){printf("%s\n", stock_ptr[j]->name);}
    }
  }
  //Asks for confirmation
  printf("\nTem a certeza que pretende continuar?: ");
  scanf("%c", &answer);
  //Adds the new car to the processing (array of structures of cars in production or waiting)
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
    //Opens processing.txt to add to the waiting queue
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
  return 0;
} 

//Reads the stations.dat files and stores in the respective structure
void ler_stations(stations station[5]) {

    FILE *fp;
    fp= fopen("files/stations.dat","rb");
    if(fp!=NULL) {
        fread(station,sizeof(stations),5,fp);    
    }
    fclose(fp);
}

//Displays the map of the factory
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

//Display the state of the stations
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

//Displays the time that machines worked for and the money that come from that use
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

//Search engine for the type of state the car is in
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

//Search engine for the type of car
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

//Counts the cars that were finished
void finished_by_type(int *finish, car *finished[], int *countstock) {
  system("clear");
  char user;
  char name[20];
  int id;
  float countcar;
  char aux;
  FILE *fp;
  fp= fopen("files/carmodel.txt","r");
  do {
    printf("\n\nNum   Marca      Qtd.    Percentage\n\n");
    do {
      countcar= 0;
      fscanf(fp,"%d %s ",&id,name);
      for (int j=0;j<*countstock;j++){
        fscanf(fp,"%*d ");
      }
      fscanf(fp,"%*d %*d %*s");
      for(int i= 0; i < *finish; i++) {
        if(strcmp(finished[i]->name,name)== 0) { 
          countcar++;
        }
      }
      printf(" %d  - %s \t %.0f \t %.2f%%\n", id, name, countcar, countcar/(*finish)*100);
    }while((aux=fgetc(fp))!=EOF);
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
  fclose(fp);
}

//Counts the number of cars Waiting or Processing
void Products_state(car *processing[], int *finish, int *queue) {
  system("clear");
  char user;
  int countP= 0, countW= 0;

  for(int i= 0; i < *queue; i++) {
    if(strcmp(processing[i]->processstate,"Processing")== 0) { countP++;}
    if(strcmp(processing[i]->processstate,"Waiting")== 0) { countW++;}
  }

  do {
    printf("\t\t  ***State chart***\n\n");
    printf("Processing: \t %d\n\n", countP);
    printf("Waiting: \t %d\n\n", countW);
    printf("Stored: \t %d\n\n", *finish);
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

//Says the money that was spent in each station and gives the final money spent on the stations
void station_cost(stations station[5]) {
  char user;
  double totalcost= 0;
  int totaltime= 0;

  system("clear");
  do {
    printf("\t\t  ***Stations Info***\n\n");
    printf("ID \t\t      Op.Time \t        Op.Cost\n\n");
    for(int i= 0; i < 5; i++) {
      printf("Station: %d \t\t %d \t\t %.2f€\n", i+1, station[i].temp_final, station[i].cost*station[i].temp_final);
    }
    printf("\n");
    for(int j= 0; j < 5; j++) {
      totalcost += station[j].cost*station[j].temp_final;
      totaltime += station[j].temp_final;
    }
    printf("Total operating time:   %d mins\n", totaltime);
    printf("Total cost:             %.2lf€\n", totalcost);
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

//Shows the cars finished, processing and waiting
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

//Dysplay to factory state
void factory_state_display() {
  system("clear");
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

//Stats display
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

//Menu display
void menu_display() {
  system("clear");
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

//Selection interace for Factory State
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

//Selection interface for Stats
void stats_interface(car *processing[], car *finished[sizeof(car)], int *finish, int *queue, stations station[5], int *countstock) {
  system("clear");
  char user;
    
      do {
        stats_display();
        scanf(" %c", &user);
  //dá a hipotese do user ir utilizcar *processing[sizeof(car)],int queuecar *processing[sizeof(car)],int queuear cada opção do menu que diz stats (opção 5)
      switch(user) {
        case '1': finished_by_type(finish,finished,countstock);
                  break;
        case '2': Products_state(processing,finish,queue);
                  break;
        case '3': station_cost(station);
                  break;
        default: system("clear"); 
                 continue;
    }
  }while(user != 'B' && user != 'b');
}

//Funtions that handles the timeskip function
void time_skip(int currenttime,car *processing[sizeof(car)],int *finish, int *queue,car *finished[sizeof(car)], stock *stock_ptr[sizeof(stock)], int *countstock, stations_use st[5], stations station[5]){
  int timeadded;
  double aux= 1000;
  double aux2;
  char user;
  int k;
  int done;
  int count= 0;
  //Asks the user how time he wants the machine do skip
  printf("Insira o tempo que pretende que passe (em minutos): ");
  scanf(" %d", &timeadded);
  do {
    do {
      //Every time it goes up, it curresponds to 1 min passed, so timeadded - 1 minute
      timeadded -= 1;
      //Finds the cars that have time in the clock and takes one away
      //Also does the same to the station, but in that case it adds, because one minute passed
      for(int i= 0; i < *queue; i++) {
        if(processing[i]->fabproc.timeleft != 0) {
          processing[i]->fabproc.timeleft -= 1;
          station[processing[i]->std-1].temp_final += 1;
        }
      }
      //Will apply every thing below to every car one by one
      for(int j= 0; j < *queue; j++) {
        if(processing[j]->fabproc.timeleft == 0 && strcmp(processing[j]->processstate,"Processing") == 0) {
          //If the conditions are met it puts the car in waiting
          strcpy(processing[j]->processstate, "Waiting");
          //The station is no longer in use
          st[processing[j]->std-1].used = -1;
          //The state of the station is the following:
          //Operation in progress: NONE
          //Car in progress: NONE
          //Name of the operation: NOT DEFINED
          //State of the station: IDLE
          st[processing[j]->std-1].operations = '-';
          strcpy(st[processing[j]->std-1].carname,"   -");
          strcpy(st[processing[j]->std-1].opName,"   -");
          strcpy(st[processing[j]->std-1].state,"   Idle");
          //Initializing variable "done"
          done= 0;
          //Removes the letter that marked the previous operation
          for(int k= 0; k < 3 && done == 0; k++) {
            if(processing[j]->fabproc.opso[k] != '-') {
              processing[j]->fabproc.opso[k] = '-';
              done= 1;
            }
          }
          //The station the car is marked to is now: NOT DEFINED
          processing[j]->std = 0;
        }
        else {
          //If the time left to finish the operation is 0 and it still has one or more operations to do
          if(processing[j]->fabproc.timeleft == 0 && strcmp(processing[j]->fabproc.opso, "---") != 0) {
            for(k= 0; processing[j]->fabproc.opso[k] == '-' && k < 3; k++) {}
            //Initializing aux variable
            aux= 1000;
            aux2= 0; 
            //Choosing whats the smallest cost but only if the station is free
            for(int h= 0; h < 5 ; h++) {
              for(int x= 0; x < 3 ; x++) {
                if(processing[j]->fabproc.opso[k] == station[h].ops[x] && st[h].used == -1 && station[h].cost < aux) {
                  aux= station[h].cost;
                }
              }
            }
            for(int h= 0; h < 5 ; h++) {
              for(int x= 0; x < 3 ; x++) {
                if(processing[j]->fabproc.opso[k] == station[h].ops[x] && st[h].used == -1 && station[h].cost == aux) {
                  //The car is in progress
                  strcpy(processing[j]->processstate, "Processing");
                  //Now the time left is the time that the station needs to complete the operation
                  processing[j]->fabproc.timeleft = station[h].temp_ops[x];
                  //Now the station identifier is the station id
                  processing[j]->std = station[h].id;
                  //The station is used
                  st[h].used = 1;
                  //Modifing the state (st[h].state), name of the car (st[h].carname) and operation (st[h].operations) in the station status
                  strcpy(st[h].carname,processing[j]->name);
                  strcpy(st[h].state,"Processing");
                  st[h].operations = processing[j]->fabproc.opso[k];
                  //Giving a name for the operation fron the caracter of the operation in progress
                  switch(st[h].operations) {
                  case 'A': strcpy(st[h].opName,"Soldering"); break;
                  case 'B': strcpy(st[h].opName,"Cuting"); break;
                  case 'C': strcpy(st[h].opName,"Painting"); break;
                  case 'D': strcpy(st[h].opName,"Assembling"); break;
                  case 'E': strcpy(st[h].opName,"Finishing"); break;
                  default: strcpy(st[h].opName,"-"); break;
                  }
                  printf("%s -> station %d\n", processing[j]->name, h+1);
                  break;
                }
              }
            }
          }
        }
      }
    }while(timeadded != 0);
    //Everything that is finished but still waiting will be transfered to a finished state
    //If the count == *queue it means that the selection already covered every possible car in the condition below
    for(int h= 0; count != *queue; h++) {
      count= 0;
      for(int j= 0; j < *queue; j++) {
        if(strcmp(processing[j]->fabproc.opso, "---") == 0 && strcmp(processing[j]->processstate, "Waiting") == 0) {
          strcpy(finished[*finish]->name, processing[j]->name);
          finished[*finish+1]= malloc(sizeof(car));
          printf("%s has Finished -> Warehouse\n", processing[j]->name);
          // + 1 to the finish count
          *finish += 1;
          // - 1 to the queue count, because theres now - one car in progress or waiting
          *queue -= 1;
          //Shifts every member next to the one that just left, one place to the left 
          for(int k= j; k < *queue; k++) {
            processing[k] = processing[k+1];
          }
        }
        else {
          count++;
        }
      }
    }
    getchar();
    scanf("%c",&user);
  }while( user != '\n');
}

//Displays the processes that the station is doing right now
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
  int totalitems=0;
  int aux=0;
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
  //Initializes the initial information in the files
  lertxt(stock_ptr,countstock);
  r_files(processing,stationsv,countstock,stock_ptr,queue);
  r_finished(finished,finish);
  ler_stations(station);
  stations_process(st);
  printf("%d\n",*queue);
  printf("%d\n",*finish);
  do {
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
      case '5': stats_interface(processing,finished,finish,queue,station,countstock);
                system("clear");
                break;
      case '6': time_skip(currenttime, processing, finish, queue, finished,stock_ptr, countstock,st,station);
                break;
      default: continue;
    } 
  } while(strchr(user,'E')== 0 && strchr(user,'e')==0);
  //Writes changes in stock.txt
  FILE *stck;
  stck = fopen("files/stock.txt", "w+");
    for(int i=0;i<*countstock;i++){
      totalitems += stock_ptr[i]->amount;
    }
    for(int i=0;i<*countstock;i++){
      for(int j=0;j<stock_ptr[i]->amount;j++){
        fprintf(stck,"%d %s %.2f", stock_ptr[i]->id, stock_ptr[i]->name, stock_ptr[i]->cost);
        if(aux != (totalitems-1)){
          fprintf(stck,"\n");
        }
        aux +=1;
      }
    }
    fclose(stck);
  //Writes changes in processing.txt
  FILE *prc;
  prc = fopen("files/processing.txt", "w+");
    for(int i=0;i<*finish;i++){
      fprintf(prc,"%s Finished - 0 ---\n", finished[i]->name);
    }
    for(int i=0;i<*queue;i++){
      fprintf(prc,"%s %s %d %d %s", processing[i]->name, processing[i]->processstate, processing[i]->std, processing[i]->fabproc.timeleft, processing[i]->fabproc.opso);
      if(i != (*queue - 1)){
        fprintf(prc,"\n");
      }
    }
    fclose(prc);
  //Writes changes in stations.dat
  FILE *sta;
  sta = fopen("files/stations.dat","wb+");
    fwrite(station,sizeof(stations),5,sta);
    fclose(sta);
  printf("\nExiting...\n");
}