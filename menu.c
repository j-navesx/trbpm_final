#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>
void text(){
  printf("\n\t\t**Factory Admin Menu**\n\n");
  printf("1- Show stock\n");
  printf("2- Refill stock\n");
  printf("3- Build car\n");
  printf("4- Factory State\n");
  printf("5- Stats\n");
  printf("6- Time skip\n");
  printf("E- Exit\n");
}
void main(){
  text();
}
