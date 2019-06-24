include Makefile.inc
SOURCES = $(wildcard *.c)
OBJECTS = $(SOURCES:.c=.o)
DEPS = $(wildcard include/*.h)
PROJECT = ../ss

all: $(PROJECT)

%.o: %.c $(DEPS)
	$(GCC) $(GCCFLAGS) -I./include -c $< -o $@


$(PROJECT): $(DEPS) $(OBJECTS)
	$(GCC) -o $@ $(SOURCES) -I./include $(GCCFLAGS)


clean:
	rm -rf *.o $(PROJECT)

.PHONY: all clean
