#include <stdlib.h>

#include "program_sequence.h"

node* createArithmetic(int value){
    node* program_node = malloc(sizeof(node));
    program_node->next = NULL;
    program_node->type = ARITHMETIC;
    program_node->value = value;
    return program_node;
}

node* createNavigation(int value){
    node* program_node = malloc(sizeof(node));
    program_node->next = NULL;
    program_node->type = NAVIGATION;
    program_node->value = value;
    return program_node;
}

node* createLoop(node* sequence){
    node* program_node = malloc(sizeof(node));
    program_node->next = NULL;
    program_node->type = LOOP;
    program_node->sub = sequence;
    return program_node;
}

node* createIO(bool direction){
    node* program_node = malloc(sizeof(node));
    program_node->next = NULL;
    program_node->type = IO;
    program_node->direction = direction;
    return program_node;
}

void deleteNode(node* target){
    free(target);
    return;
}

node* addNode(node* sequence, node* newNode){
    if (sequence == NULL){
        return newNode;
    }

    node* end = sequence;
    while (end->next){ end = end->next; }
    end->next = newNode;

    return sequence;
}
