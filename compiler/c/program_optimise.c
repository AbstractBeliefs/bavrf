#include "program_optimise.h"
#include "program_sequence.h"

#include <stdlib.h>

node* combine_arithmetic(node* sequence){
    if (!sequence){ return sequence; }

    node* currnode = sequence;
    while (currnode){
        if (currnode->type == ARITHMETIC && currnode->next && currnode->next->type == ARITHMETIC){
            currnode->value += currnode->next->value;
            currnode->next = currnode->next->next;
        } else if (currnode->type == LOOP){
            combine_arithmetic(currnode->sub);
            currnode = currnode->next;
        } else {
            currnode = currnode->next;
        }
    }
    return sequence;
}

node* combine_navigation(node* sequence){
    if (!sequence){ return sequence; }

    node* currnode = sequence;
    while (currnode){
        if (currnode->type == NAVIGATION && currnode->next && currnode->next->type == NAVIGATION){
            currnode->value += currnode->next->value;
            currnode->next = currnode->next->next;
        } else if (currnode->type == LOOP){
            combine_navigation(currnode->sub);
            currnode = currnode->next;
        } else {
            currnode = currnode->next;
        }
    }
    return sequence;
}

node* eliminate_noops(node* sequence){
    if (!sequence){ return sequence; }

    node* prev = NULL;
    node* curr = sequence;
    node* next = NULL;

    while (curr){
        next = curr->next;
        if ((curr->type == ARITHMETIC || curr->type == NAVIGATION) && curr->value == 0){
            deleteNode(curr);
            curr = next;
            if (prev) {
                prev->next = next;
            } else {
                sequence = next;
            }
            continue;
        }
        if (curr->type == LOOP){
            curr->sub = eliminate_noops(curr->sub);
        }
        prev = curr;
        curr = next;
    }
    return sequence;
}

node* (*optimisations[])(node*) = {
    &combine_arithmetic,
    &combine_navigation,
    &eliminate_noops,
    NULL
};
