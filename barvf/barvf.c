/*
 * barvf.c
 *
 * Created: 22/02/2014 11:59:18
 *  Author: Gareth Pulham
 */ 


#include <avr/io.h>
#include <string.h>

// Prepare memory and memory pointer
unsigned char memory[1024];
unsigned char* memptr = memory;

// Prepare program space and program counter
char* program = "++++++++++[>+++++++>++++++++++>+++>+<<<<-]>++.>+.+++++++..+++.>++.<<+++++++++++++++.>.+++.------.--------.>+.>.";
char* pc;

int main(){
    pc = program;               // point the pc at the first instruction
    memset(memory, 0, 1024);    // Initialise all memory to 0
    for(;;){}
}