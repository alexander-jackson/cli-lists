CC := gcc
CFLAGS := -O2 -Wall -Wextra -std=c99
TARGET := lists

SRCDIR := src
OBJDIR := obj

SRC := ${wildcard ${SRCDIR}/*.c}
OBJ := ${SRC:${SRCDIR}/%.c=${OBJDIR}/%.o}

default: build

debug: CFLAGS += -g
debug: build

build: ${OBJ}
	${CC} ${CFLAGS} ${OBJ} -o ${TARGET}

${OBJDIR}/%.o: ${SRCDIR}/%.c
	$(CC) $(CFLAGS) -c $< -o $@

install:
	mkdir -p ~/.local/share/cli-lists/
	touch ~/.local/share/cli-lists/lists.toml
	cp lists /usr/local/bin/lists

uninstall:
	rm ~/.local/share/cli-lists/lists.toml
	rm /usr/local/bin/lists
	rmdir ~/.local/share/cli-lists

.PHONY: clean

clean:
	rm -f ${OBJDIR}/*.o ${TARGET}
