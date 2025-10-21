CC = gcc

PKGS = raylib

CFLAGS += -Wall
CFLAGS += -Wextra
CFLAGS += -pedantic
CFLAGS += -Isrc/include
CFLAGS += $$(pkg-config --cflags $(PKGS))

LIBS += -lm
LIBS += -lalloc
LIBS += $$(pkg-config --libs $(PKGS))


OBJS += $(CACHE)/main.o
OBJS += $(CACHE)/game_manager.o
OBJS += $(CACHE)/game_state_menu.o


$(CACHE)/main.o: src/why2/main.c src/why2/version.h
	$(CC) $(CFLAGS) -c src/why2/main.c -o $@


$(CACHE)/game_manager.o: src/why2/game_manager.c src/why2/version.h
	$(CC) $(CFLAGS) -c src/why2/game_manager.c -o $@


$(CACHE)/game_state_menu.o: src/why2/game_state_menu.c src/why2/version.h
	$(CC) $(CFLAGS) -c src/why2/game_state_menu.c -o $@


$(RELEASE)/$(TARGET): $(OBJS)
	$(CC) $(OBJS) $(LIBS) -o $(RELEASE)/$(TARGET)




