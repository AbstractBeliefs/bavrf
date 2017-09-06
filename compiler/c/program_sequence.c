#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "program_sequence.h"

node* createArithmetic(int value){
    node* program_node = malloc(sizeof(node));
    program_node->next = NULL;
    program_node->type = ARITHMETIC;
    program_node->value = value;
    return program_node;
}

node* createNavigation(bool direction){
    node* program_node = malloc(sizeof(node));
    program_node->next = NULL;
    program_node->type = NAVIGATION;
    program_node->direction = direction;
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

void displaySequenceDepth(node* sequence, int depth){
    char* prefix = malloc(sizeof(char) * depth * 4 + 1);
    memset(prefix, ' ', sizeof(char) * depth * 4);
    prefix[depth*4] = '\0';

    while (sequence){
        printf("%s", prefix);
        switch (sequence->type){
            case ARITHMETIC: printf("Got arithmetic: %d\n", sequence->value); break;
            case NAVIGATION: printf("Got navigation: %s\n", sequence->direction ? "right" : "left"); break;
            case LOOP: displaySequenceDepth(sequence->sub, depth+1); break;
            case IO: printf("Got IO: %s\n", sequence->direction ? "out" : "in"); break;
        }
        sequence = sequence->next;
    }
    free(prefix);
    return;
}

void displaySequence(node* sequence){
    displaySequenceDepth(sequence, 0);
    return;
}
