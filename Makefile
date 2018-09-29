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
	cp lists /usr/local/bin/lists

.PHONY: clean

clean:
	rm -f ${OBJDIR}/*.o ${TARGET}
