#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(){
    FILE fp*;
    char* str= "string";
    int x= 10;

    fp= fopen("files/test.txt","w");
    fprintf(fp, "This is a string which")
}