#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

//nodes for collisions
struct Node {
    int value;
    struct Node * next;
};

//global 10000 bucket array
struct Node * h[10000];

//prototypes
void insert(int value,int hash);
bool search(int value,int hash);

int main(int argc, char** argv) {
    char * filename = NULL;
    FILE * f = NULL;
    char op; //given operation
    int value; //given value
    int hash; //hash value of value given


    if (argc < 2) {
        printf("error\n");
        exit(0);
    }

    filename = argv[1];

    //open file for reading
    f = fopen(filename,"r");

    //check if there is a file
    if (f == NULL) {
        printf("error\n");
        exit(0);
    }

    while(!feof(f)) {
        fscanf(f,"%c %d\n",&op,&value);

        if (value < 0) {
            hash = (value * -1) % 10000;
        } else {
            hash = value % 10000;
        }

        if (op == 'i') {
            insert(value,hash);
        } else if (op == 's') {
            if (search(value,hash)) {
                printf("present\n"); 
            } else {
                printf("absent\n");
            }
        } else {
            printf("error\n");
            exit(0);
        }
    }

    fclose(f);
    return 0;
}

void insert(int value,int hash) {
    if (h[hash] == NULL) {
        struct Node * n = (struct Node *) malloc(sizeof(struct Node));
        n->value = value;
        n->next = NULL;
        h[hash] = n;
        printf("inserted\n");
    } else {
        bool s = search(value,hash);
        if (!s) {
            struct Node * n = (struct Node *) malloc(sizeof(struct Node));
            n->value = value;
            n->next = h[hash];
            h[hash] = n;
            printf("inserted\n");
        } else {
            printf("duplicate\n");
        }
    }
    return;
}

bool search(int value,int hash) {
    if (h[hash] == NULL) {
        return false;
    } else {
        struct Node * temp = h[hash]; //temp value for first node in linked list

        while (temp != NULL) { 
            if (temp->value == value) {
                return true;
            }
            temp = temp->next;
        }
    }
    return false;
}
