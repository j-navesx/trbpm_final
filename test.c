#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

void main(){
    char c;
    char name[20];
    int i= 0;

    FILE *fp;
    fp= fopen("files/processing.txt","r");
    if(fp!=NULL) {
        while((c=getc(fp))!= EOF) {
            if(c == ' ') {
                break;
            }
            name[i]= c;
            i++;
        }
        printf("%s", name);
        fclose(fp);
    }
}