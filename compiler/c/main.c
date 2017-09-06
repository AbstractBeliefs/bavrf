#include "program_sequence.h"
#include "program_optimise.h"

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
    char* test="+++[--[-]]..,,[]";

    node* sequence = get_program_sequence(test);

    puts("+ Original source:");
    puts(test);

    puts("\n+ Compiling");
    displaySequence(sequence);

    puts("\n+ Optimising");
    sequence = optimise_program_sequence(sequence);
    displaySequence(sequence);

    return 0;
}
