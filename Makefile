CC = gcc
CFLAGS = -Wall -g -Iinclude
LDFLAGS = -lmysqlclient -lreadline

SRC = src/main.c src/mysql_cli.c src/table.c src/row.c
OBJ = build/main.o build/mysql_cli.o build/table.o build/row.o
EXE = bin/mysql_cli

all: $(EXE)

$(EXE): $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(LDFLAGS)

build/%.o: src/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build/*.o $(EXE)
