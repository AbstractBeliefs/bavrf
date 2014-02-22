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

// Interpreter parsing vars for loops
int depthLevel = 0;
int matchLevel = 0;

int main(){
    pc = program;               // point the pc at the first instruction
    memset(memory, 0, 1024);    // Initialise all memory to 0
    
    while (*pc){
        switch(*pc){
            case '>':       // Move the memory pointer 1 right
                memptr++;   // TODO: memory wrap around
                break;
            case '<':       // 1 left
                memptr--;
                break;
            case '+':       // increment the current cell
                (*memptr)++;
                break;
            case '-':       // decrement
                (*memptr)--;
                break;
            case '.':       // print char
                break;      // TODO: serial
            case ',':       // get char
                break;
            case '[':       // Looping operator
                // If the current data cell is 0, we skip over the block
                // that is wrapped in [ ].
                // To do this, we step over the program, not executing
                // incrementing a depth counter on [ and decrementing on ]
                // when our depth level matches the level we started off
                // with, then we have our closing ].
                if (!*memptr){
                    matchLevel = depthLevel++;  // Save the current depth
                    pc++;                       // Step into the block
                    while (depthLevel != matchLevel){   // Hunt for the closing ]
                        if(*pc == '['){ depthLevel++; } // Inc depth on nested [
                        if(*pc == ']'){ depthLevel--; } // Dec depth on nested ]
                        pc++;                   // Step to the next instruction
                    }
                    pc--;   // Correct for extra step forward to check next char
                }
                break;
            case ']':
                // This check is actually non-optimal - we can blindly jump back
                // to the start of the loop and run the check on the current
                // memory cell there. But this is just for fuuuuuuuun!
                if (*memptr){
                    matchLevel = depthLevel++;
                    pc--;
                    while (depthLevel != matchLevel){
                        if(*pc == '['){ depthLevel--; } // Inc depth on nested [
                        if(*pc == ']'){ depthLevel++; } // Dec depth on nested ]
                        pc--;
                    }
                    // No need for correcting step here.
                }
                break;
            default:    // Nothing to do on chars that are not valid instructions.
                break;
        }
        pc++;
    }
    for(;;){}
}