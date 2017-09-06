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
        int value;          // For arithmetic
        bool direction;     // For IO/memory navigation
        struct node* sub;   // For loops
    };
} node;

node* addNode(node* sequence, node* node);
void deleteNode(node* target);
void displaySequence(node* sequence);

node* createArithmetic(int value);
node* createNavigation(bool direction);
node* createLoop(node* sequence);
node* createIO(bool direction);

#endif
