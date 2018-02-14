#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void swap(char * p1,char * p2);
void sort(char * original, int length);

int main(int argc, char** argv) {
    char * original = NULL;

    //make sure an argument is given
    if (argc < 2) {
        printf("error\n");
        exit(0);
    }

    original = argv[1];

    sort(original,strlen(original));

    printf("%s\n",original);

    return 0;
}

void swap(char * p1,char * p2) {

    char temp = *p1;
    *p1 = *p2;
    *p2 = temp;

}

void sort(char * original,int length) {

    //loop until to second to last char then 3rd to last,etc.
    for (int i = 0; i < length-1; i++) { 

        for (int j = 0; j < length-1-i; j++) {
            if (original[j] > original[j+1]) {
                swap(&original[j],&original[j+1]);
            }
        }

    }
}
