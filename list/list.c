#include <stdlib.h>
#include <stdio.h>

//node struct to hold value and ptr to next node in list
struct Node {
    int value;
    struct Node * next;
};

//prototypes
void insert(int value);
void delete(int value);

struct Node * head = NULL; //global variable that holds value of head
int count = 0; //number of nodes in linked list

int main(int argc,char** argv) {
    char * filename = NULL;
    FILE * f = NULL;
    char op;
    int value;
    size_t size = 0;

    if (argc < 2) {
        printf("error\n");
        exit(0);
    }

    filename = argv[1];


    //open file for reading 
    f = fopen(filename,"r");

    //if there is no file
    if (f == NULL) {
        printf("error\n");
        exit(0);
    }
    
    fseek(f,0,SEEK_END);
    size = ftell(f); //get the size of the file pointer

    if (size == 0) { //if file pointer is 0, then the file is empty
        printf("0\n");
        exit(0);
    }

    fseek(f,0,SEEK_SET); //reset file pointer to the beginning of the file

    while (!feof(f)) {
        fscanf(f,"%c %d\n",&op,&value);

        if (op == 'i') {
            insert(value);
        } else if (op == 'd') {
            delete(value);
        } else {
            printf("error\n");
            exit(0);
        }

    }

    printf("%d\n",count);
    //loop through linked list
    while (head != NULL) {
        printf("%d ",head->value);
        head = head->next;
    }
    printf("\n");

    fclose(f); //close file
    free(head); //free memory 
    return 0;
}

void insert(int value) {
    //if a value hasn't been inserted yet
    if (head == NULL) {
        struct Node * n = (struct Node *) malloc(sizeof(struct Node));
        n->value = value;
        n->next = NULL;
        head = n;
        count++;
        return;
    } 

    struct Node * current = head;  
    struct Node * previous = head;
    struct Node * n = (struct Node *) malloc(sizeof(struct Node)); //new node to be inserted
    n->value = value;
    n->next = NULL;

    while (current != NULL) {
        if (current->value == value) {
            break;
        } else if (current->value < value) {
            //if the current node is the last node in the linked list
            if (current->next == NULL) {
                current->next = n;
                count++;
                return;
            }
            //variable to keep track of the previous and current nodes
            previous = current;
            current = current->next;
            continue;
        } else if (current->value > value) {
            //if the current node is the head of the linked list
            if (current->value == head->value) {
                n->next = head;
                head = n;
                count++;
                return;
            }

            //may be a breakpoint
            n->next = previous->next;
            previous->next = n;
            count++;
            break;
        }
    }
    return;
}

void delete(int value) {
    //if the linked list is empty
    if (head == NULL) {
        return;
    }

    struct Node * current = head;
    struct Node * previous = head;

    while (current != NULL) {
        if (current->value == value) {
            //count decrements regardless of where the node is in the linked list
            count--;

            //if the current node is the head of the linked list
            if (current->value == head->value) {
                head = head->next;
                break;
            }

            //if the current node is the last node
            if (current->next == NULL) {
                previous->next = NULL;
                break;
            }

            //if the current node is in the middle of the linked list
            previous->next = current->next;
            break;
        }

        previous = current;
        current = current->next;
    }
    return;
}

