#ifndef __program_sequence_h__
#define __program_sequence_h__

#include <stdbool.h>

typedef enum nodetype {
    ARITHMETIC,
    NAVIGATION,
    LOOP,
    IO
} nodetype;

typedef struct node {
    struct node* next;

    nodetype type;
    union {
        int value;          // For arithmetic/memory navigation
        bool direction;     // For IO
        struct node* sub;   // For loops
    };
} node;

node* addNode(node* sequence, node* node);
void deleteNode(node* target);
void displaySequence(node* sequence);

node* createArithmetic(int value);
node* createNavigation(int value);
node* createLoop(node* sequence);
node* createIO(bool direction);

#endif
