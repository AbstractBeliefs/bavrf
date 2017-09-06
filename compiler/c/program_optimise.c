#include "program_optimise.h"
#include "program_sequence.h"

#include <stdlib.h>

node* combine_arithmetic(node* sequence){
    if (!sequence){ return sequence; }

    node* currnode = sequence;
    while (currnode->next){
        if (currnode->type == ARITHMETIC && currnode->next->type == ARITHMETIC){
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

node* (*optimisations[])(node*) = {
    &combine_arithmetic,
    NULL
};
