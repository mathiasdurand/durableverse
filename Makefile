CC = gcc

FLAGS = -Wall -Wextra -std=c99

all : durableverse

obj/%.o : src/%.c
	$(CC) $(FLAGS) -c $< -o $@

durableverse : obj/carte.o obj/structure.o obj/plateau.o obj/joueur.o obj/jeu.o obj/interface.o obj/main.o obj/utils.o
	$(CC) $(FLAGS) -o ./bin/$@ $^

clean :
	rm bin/durableverse obj/main.o obj/joueur.o obj/jeu.o obj/interface.o obj/carte.o obj/plateau.o obj/structure.o obj/utils.o