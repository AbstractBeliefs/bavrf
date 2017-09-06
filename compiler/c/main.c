#include "program_sequence.h"

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

int main(){
    char* test="+++[---]";

    node* sequence = get_program_sequence(test);

    puts(test);
    displaySequence(sequence);

    return 0;
}
