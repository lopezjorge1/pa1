#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main(int argc,char ** argv) {
    char * newS = NULL; //will hold value of uppercase string
    int length = 0; //length of original string

    //if the string isn't given
    if (argc < 2) {
        printf("error\n");
        exit(0);
    }

    char * original = argv[1]; //original string
    length = strlen(original);
    newS = (char *) malloc(length + 1); //add one more byte for null-terminating character
    
    //loop through string and capitalize characters
    int i;
    for (i = 0; i < length; i++) {
        if (original[i] >= 'A' && original[i] >= 'Z') {
            newS[i] = original[i] - 32;
        } else {
            newS[i] = original[i];
        }
    }
    
    newS[length] = '\0'; //null-terminating character


    printf("%s\n",newS);
    free(newS);
    return 0;
}
