#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

void lertxt(int qnt[6]){
  char input[4];
  int id,quant;
  FILE *fp;
  fp = fopen("files/quantities.txt","r");
  if (fp!=NULL){  
    while(fgets(input,4,fp)){
      id = input[0]-48;
      printf("id:%d\n",id);
      quant = input[2]-48;
      printf("quant:%d\n",quant);
      qnt[id-1] = quant; 
    }
    fclose(fp);
  }
} 

void main(){
  int qnt[6];
  lertxt(qnt);
  for(int i=0;i<6;i++){
    printf("%d\n",qnt[i]);
  }
}