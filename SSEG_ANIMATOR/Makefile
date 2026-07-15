default: 
	gcc main.c -lraylib -I. -lGL -lm -lpthread -ldl -lrt -DRAYGUI_IMPLEMENTATION

web:
	emcc -o game.html main.c -Os -Wall ~/Software/raylib/src/libraylib.web.a -I. -I~/Software/raylib/src/ -L. -L~/Software/raylib/src/raylib.h -s USE_GLFW=3 -s ASYNCIFY --shell-file ~/Software/raylib/src/shell.html -DPLATFORM_WEB -lglfw --preload-file textures
