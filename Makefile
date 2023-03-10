path = ..\Menu\src
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system

all: compile link
compile:
	g++ -c main.cpp menu.cpp -I $(INCLUDE)
link:
	g++ main.o -o main.exe -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
run:
	./main.exe