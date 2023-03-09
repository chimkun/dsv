path = ..\Menu\src
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system

all: compile link
compile:
	g++ -c menu.cpp -I $(INCLUDE)
link:
	g++ menu.o -o menu.exe -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
run:
	./main.exe