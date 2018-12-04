#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

struct livro{
  int id;
  char letra;
}a={0,'A'},b={1,'B'};

void main(){
  char lol='a';
  printf("%d",a.id);
}