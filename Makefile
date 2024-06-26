CC=gcc
CFLAGS=-g -Wall

SRC=src
SRCS=$(wildcard $(SRC)/*.c)
OBJ=obj
OBJS=$(patsubst $(SRC)/%.c, $(OBJ)/%.o, $(SRCS))

TEST=test
TESTS=$(wildcard $(TEST)/*.c)
TESTRUNNER=$(TEST)/bin/test_runner

LIBDIR=lib
LIB=$(LIBDIR)/lib.a

VALGRIND_LOG=valgrind.log

####

all: $(LIB)

test: $(LIB) $(TEST)/bin $(TESTRUNNER)
	@bash -c 'valgrind --trace-children=yes --leak-check=full ./$(TESTRUNNER) --color=always 2>&1 | tee >(grep -E "^\[") > $(VALGRIND_LOG)'
	@grep "definitely lost: [1-9][0-9]* bytes in [1-9][0-9]* blocks" $(VALGRIND_LOG) || true

main: $(LIB) $(OBJ)/main.o
	$(CC) $(CFLAGS) -o main $(OBJ)/main.o -Iinclude -L$(LIBDIR) -l:lib.a

clean:
	$(RM) -r $(LIBDIR) $(OBJ) $(TEST)/bin $(VALGRIND_LOG) main

####

$(LIB): $(LIBDIR) $(OBJ) $(OBJS)
	$(RM) $(LIB)
	ar -cvrs $(LIB) $(OBJS)

$(OBJ)/%.o: $(SRC)/%.c 
	$(CC) $(CFLAGS) -c $< -o $@

$(TESTRUNNER): $(TESTS) $(OBJS)
	$(CC) $(CFLAGS) $(TESTS) $(OBJS) -o $(TESTRUNNER) -lcriterion

$(OBJ)/main.o: main.c
	$(CC) $(CFLAGS) -Iinclude -c main.c -o $(OBJ)/main.o

$(TEST)/bin:
	mkdir $@

$(OBJ):
	mkdir $@

$(LIBDIR):
	mkdir $@
