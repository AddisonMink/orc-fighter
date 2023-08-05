.PHONY: game
.PHONY: web

game:
	$(CC) main.c \
	game.c \
	geometry.c \
	components.c \
	map.c \
	textures.c \
	systems/damagesystem.c \
	systems/drawhudsystem.c \
	systems/drawsystem.c \
	systems/movesystem.c \
	systems/observersystem.c \
	systems/orcsystem.c \
	systems/overlayspritesystem.c \
	systems/playersystem.c \
	-I . \
	-I systems/ \
	$(shell pkg-config --libs --cflags raylib) -o game

run: game 
	./game