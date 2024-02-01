# Makefile pour compiler le programme

# Compilateur
CC = gcc

# Options de compilation
CFLAGS = -Wall -Wextra -std=c99

# Nom du programme de sortie
TARGET = mon_programme

# Liste des fichiers source
SRCS = fonctionsT.c fonctionsS.c main.c

# Liste des fichiers objets dérivés des fichiers sources
OBJS = $(SRCS:.c=.o)

# Définition des règles de construction

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

cleanobj:
	rm -f $(OBJS)
