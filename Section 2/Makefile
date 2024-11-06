EXECUTABLE=answer
C_FILES=$(wildcard *.c)
OBJS=$(C_FILES:.c=.o)
EXTERNAL_OBJ=./libs/evaluateur.o
HANDIN_FILE=handin.tar.xz

C_FLAGS=-std=gnu17 -no-pie
C_FLAGS+=-Wall -Wno-unused-result -Wno-unused-variable
C_FLAGS+=-Werror

.phony: all handin clean

all: $(EXECUTABLE)

handin: $(EXECUTABLE) $(HANDIN_FILE)

clean:
	rm -f $(HANDIN_FILE) $(EXECUTABLE) $(OBJS)

$(EXECUTABLE): $(OBJS)
	gcc -no-pie $< $(EXTERNAL_OBJ) -o $@

%.o: %.c
	gcc $(C_FLAGS) -c $< -o $@

$(HANDIN_FILE): $(C_FILES)
	tar -cjf $@ $<
