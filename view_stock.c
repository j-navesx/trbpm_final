#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

struct stock {

int id;
int amount;
};

void main() {

struct stock ferro;
struct stock aluminio;
struct stock vidro;
struct stock plastico;
struct stock borracha;
struct stock aco;

struct ferro.id= 1;
struct aluminio.id= 2;
struct vidro.id= 3;
struct plastico.id= 4;
struct borracha.id= 5;
struct aco.id= 6;

void main(){
  char text[20];
  FILE *fp;
  fp = fopen("files/stock.txt","r");
  if (fp!=NULL){  
    while(fgets(text,20,fp)){
      a = text[0];
      switch (a){
        case 1: countF++;
      }
      printf("%s",text);
    }
    fclose(fp);
  }


/*struct stock.price ferro= 1.40;
struct stock.price aluminio= 7.80;
struct stock.price vidro= 12.50;
struct stock.price plastico= 2.20;
struct stock.price borracha= 1.50;
struct stock.price aco= 3.30;*/

}


