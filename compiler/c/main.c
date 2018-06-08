#include <stdio.h>

#include "program_sequence.h"
#include "program_optimise.h"
#include "utils.h"

#include "bf.parse.h"
#include "bf.lex.h"

node* get_program_sequence(char* source){
    node* sequence = NULL;

    yyscan_t scanner;
    YY_BUFFER_STATE state;

    if (yylex_init(&scanner)) {
        return NULL;
    }

    state = yy_scan_string(source, scanner);

    if (yyparse(&sequence, scanner)){
        return NULL;
    }

    yy_delete_buffer(state, scanner);     
    yylex_destroy(scanner);

    return sequence;
}

node* optimise_program_sequence(node* sequence){
    for (node* (**optimisation)(node*) = optimisations; *optimisation != NULL; optimisation++){
        sequence = (*optimisation)(sequence);
    }
    return sequence;
}

int main(){
    char* test="+++[--[-]]..,,[]+-+-<<<++>><<[++--]";

    node* sequence = get_program_sequence(test);

    fprintf(stderr, "+ Original source:\n");
    fprintf(stderr, "\t%s\n", test);

    fprintf(stderr, "+ Compiling\n");
    displaySequence(sequence);

    fprintf(stderr, "+ Optimising\n");
    sequence = optimise_program_sequence(sequence);
    displaySequence(sequence);
    writeDot(sequence);

    return 0;
}
