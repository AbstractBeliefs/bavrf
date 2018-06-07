#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "utils.h"

void displaySequenceDepth(node* sequence, int depth){
    char* prefix = malloc(sizeof(char) * depth * 4 + 1);
    memset(prefix, ' ', sizeof(char) * depth * 4);
    prefix[depth*4] = '\0';

    while (sequence){
        fprintf(stderr, "%s", prefix);
        switch (sequence->type){
            case ARITHMETIC: fprintf(stderr, "Got arithmetic: %d\n", sequence->value); break;
            case NAVIGATION: fprintf(stderr, "Got navigation: %d\n", sequence->value); break;
            case LOOP: fprintf(stderr, "Entered loop\n"); displaySequenceDepth(sequence->sub, depth+1); break;
            case IO: fprintf(stderr, "Got IO: %s\n", sequence->direction ? "out" : "in"); break;
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

void drawNode(unsigned int id, node* astnode){
    switch (astnode->type){
        case ARITHMETIC: printf("%d [shape=\"box\" label=\"Arith: %+d\"];\n", id, astnode->value); break;
        case NAVIGATION: printf("%d [shape=\"hexagon\" label=\"Nav: %+d\"]; \n", id, astnode->value); break;
        case IO: printf("%d [shape=\"house\" label=\"IO: %s\"]; \n", id, astnode->direction ? "out" : "in"); break;
        case LOOP: printf("%d [shape=\"diamond\" label=\"\"]; \n", id); break;
        default: break;
    }
    return;
}

void drawLink(unsigned int from, unsigned int to){
    printf("%d -> %d;\n", from, to);
    return;
}

unsigned int drawSequence(node* sequence, unsigned int parent, unsigned int index){
    unsigned int next = index+1;

    if (!sequence){
        return index;
    }

    drawNode(index, sequence);
    if (parent){
        drawLink(parent, index);
    }

    if (sequence->type == LOOP){
        next = drawSequence(sequence->sub, index, next);
    }

    if (!sequence->next){
        return next;
    }

    return drawSequence(sequence->next, index, next);
}

void writeDot(node* sequence){
    printf("digraph main {\nrankdir=LR;\n");
    drawSequence(sequence, 0, 1);
    printf("}");
}
