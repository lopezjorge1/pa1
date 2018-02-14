#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ctype.h>

char * rle(char * s,int length);

int main(int argc, char ** argv) {
    char * compressed = NULL; //compressed string
    char * original = NULL; //original string
    int length = 0; //length of original argument

    if (argc < 2) {
        printf("error\n");
        exit(0);
    }

    original = argv[1];
    length = strlen(original);

    compressed = rle(original,length);

    if (strlen(original) < strlen(compressed)) {
        printf("%s\n",original);
    } else {
        for (int i = 0; i < strlen(compressed); i += 2) {
            printf("%c%d",compressed[i],compressed[i+1]);
        }
        printf("\n");
    }

    free(compressed); //free allocated memory from returned string
    return 0;
}

char * rle(char * s,int length) {
    char c; //character being tracked in the string
    char * result; //returned string 
    int tracker = 1; //tracks how many 2 bytes there are
    int count = 1; //how many repeating characters there are (at least 1)
    int index = 0; //index of compressed string

    result = malloc(2+1); //allocate at least two bytes for compressed string plus a null-terminating byte
    result[2] = '\0';

    c = s[0]; //first character of string
    tracker++;

    for (int i = 1; i < length; i++) {
        if (isdigit(s[i])) {
            printf("error\n");
            exit(0);
        } else {
            if (s[i] == c) {
                count++;
            } else {
                result[index] = c;
                result[index+1] = (char) count;
                result = (char *) realloc(result,2*tracker+1); //reallocate more memory for the compressed string
                result[2*tracker] = '\0'; //maintaining the null-terminating byte at the end of compressed string
                c = s[i];
                index += 2;
                tracker++;
                count = 1;
            }
        }
    }

    result[index] = c;
    result[index+1] = (char) count;

    return result;
}

