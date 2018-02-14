#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

struct Node {
    int value;
    struct Node * left;
    struct Node * right;
};

struct Node * head = NULL; //initialize global head variable

int insert(struct Node * n,int value);
int search(struct Node * n,int value);
void print(struct Node * n);
int delete(struct Node * n,int value);
struct Node * find(struct Node * n);

int main(int argc,char ** argv) {
    char * filename = NULL;
    FILE * f = NULL;
    char op;
    int value;

    if (argc != 2) {
        printf("error\n");
        exit(0);
    }

    filename = argv[1];

    //open the file for reading
    f = fopen(filename,"r");

    //if the file isn't found
    if (f == NULL) {
        printf("error\n");
        exit(0);
    }

    int x; //value that will be 1 or -1 if (inserted/duplicate) or (present/absent) 
    while(!feof(f)) {
        fscanf(f,"%c %d\n",&op,&value);
        
        if (op == 'i') {
            x = insert(head,value);
            
            if (x == 1) {
                printf("inserted\n");
            } else {
                printf("duplicate\n");
            }
        } else if (op == 's') {
            x = search(head,value);

            if (x == 1) {
                printf("present\n");
            } else {
                printf("absent\n");
            }
        } else if (op == 'p') {
            print(head);
            printf("\n");
        } else if (op == 'd') {
            x = delete(head,value);
            
            if (x == 1) {
                printf("deleted\n");
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

int insert(struct Node * n,int value) {
    struct Node * temp = (struct Node *) malloc(sizeof(struct Node));
    temp->value = value;
    temp->left = NULL;
    temp->right = NULL;

    //if there is no bst 
    if (head == NULL) {
        head = temp;
        return 1;
    } 

    if (n->value < value) {
        if (n->right == NULL) {
            n->right = temp;
            return 1;
        } 
        return insert(n->right,value);
    } else if (n->value > value) {
        if (n->left == NULL) {
            n->left = temp;
            return 1;
        } 
        return insert(n->left,value);
    } else {
        return -1;
    }
}

int search(struct Node * n,int value) {
    if (n == NULL) {
        return -1;
    } else if (n->value == value) {
        return 1;
    }

    
    if (n->value > value) {
        return search(n->left,value);
    } else {
        return search(n->right,value);
    }
}

void print(struct Node * n) {
    if (n != NULL) {
        printf("(");
        print(n->left);
        printf("%d",n->value);
        print(n->right);
        printf(")");
    }
    return;
}

int delete(struct Node * n,int value) {
    struct Node * temp = n;
    struct Node * p = n; //parent node to node being deleted

    bool left = false; //true if the value given is in the left subtree
    
    while (temp->value != value) {
        p = temp; //regardless whether or not the node is in the left/right subtree, current node is p

        if (value < temp->value) { 
            left = true;
            temp = temp->left;
        } else {
            temp = temp->right;
        }

        //if there aren't any more nodes to look at
        if (temp == NULL) return -1;
    }

    //if temp is a leaf
    if (temp->left == NULL && temp->right == NULL) {
        if (head == temp) {
            head = NULL;
        } else if (left) {
            p->left = NULL;
        } else {
            p->right = NULL;
        }
    }
    //if temp has one child
    if (temp->right == NULL) {
        if (head == temp) {
            head = temp->left;
        } else if (left) {
            p->left = temp->left;
        } else {
            p->right = temp->left;
        }
    } else if (temp->left == NULL) {
        if (head == temp) {
            head = temp->right;
        } else if (left) {
            p->left = temp->right;
        } else {
            p->right = temp->right;
        }
    }
    //if temp has two children
    if (temp->left != NULL && temp->right != NULL) {
        struct Node * replace = find(temp); //node that will replace deleted node

        if (head == temp) {
            delete(temp->right,replace->value); //delete the replace node from it's previous spot
            replace->right = temp->right;
        } else if (left) {
            delete(p->left,replace->value);
            p->left = replace;
        } else {
            delete(p->right,replace->value);
            p->right = replace;
        }
        
        replace->left = temp->left; //make sure the bst doesn't break
        if (head == temp) head = replace; //make sure to replace head after switching pointers
    }
    
    return 1; 
}

//find the replacement for node n
struct Node * find(struct Node * n) {
    struct Node * replace = n; //replacement node
    struct Node * temp = NULL;
    
    //if there is a right subtree
    if (n->right != NULL) {
        temp = n->right;
        while (temp != NULL) {
            replace = temp;
            if (temp->left != NULL) {
                temp = temp->left;
            } else {
                break;
            }
        }
    } 
    replace = temp; //the replaced node is cut off
    return replace;
}
