CC=emcc
CXX=em++
OUT=pong.html
CFLAGS=-std=c++23
SRC=main.cpp src/Bola.cpp src/Juego.cpp src/Jugador.cpp src/Misc.cpp src/texturas.cpp src/WindowRenderer.cpp
LDFLAGS=-s USE_SDL=2
INCLUDES=-I.

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CFLAGS) $^ -o $@ $(INCLUDES) $(LDFLAGS)
	@echo Compilación terminada. Abra el navegador para ejecutar $(OUT).
