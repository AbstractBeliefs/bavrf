BAVRF Compiler
==============

Compiler + Runtime for brainfuck targeting the AVR Mega line.

Register Usage
==============

| Register | Use                                |
|----------|------------------------------------|
| r0       | Zero register, for loop comparison |
| r1       | Scratch register                   |
| r16      | Working register                   |
| Z        | RAM pointer register (r31:r30)     |