CC = gcc
CFLAGS = -std=c11 -Wall
LDFLAGS =
SOURCES = $(wildcard *.c) bf.lex.c bf.parse.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = bfc

all: $(EXECUTABLE)

bf.parse.c bf.parse.h: bf.y
	bison $<

bf.lex.c bf.lex.h: bf.l bf.parse.h
	flex $<

main.o: main.c bf.parse.h bf.lex.h
%.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) $(LDFLAGS) $^ -o $@

.PHONY: clean all
clean:
	rm -f *.o bf.lex.* bf.parse.* $(EXECUTABLE)

print-%  : ; @echo $* = $($*)
