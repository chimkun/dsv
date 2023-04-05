path = ..\Menu\src
CODE_DIR = ..\Menu\code
INCLUDE_DIR = ..\Menu\include
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system

all: compile link
compile:
	g++ -c $(CODE_DIR)\main.cpp -o main.o -I $(INCLUDE) -I $(INCLUDE_DIR)
#	g++ -c $(CODE_DIR)\menu.cpp -o menu.o -I $(INCLUDE) -I $(INCLUDE_DIR)
	g++ -c $(CODE_DIR)\general.cpp -o general.o -I $(INCLUDE) -I $(INCLUDE_DIR)
	g++ -c $(CODE_DIR)\LLscreen.cpp -o LLscreen.o -I $(INCLUDE) -I $(INCLUDE_DIR)
	g++ -c $(CODE_DIR)\node.cpp -o node.o -I $(INCLUDE) -I $(INCLUDE_DIR)
#	g++ -c $(CODE_DIR)\button.cpp -o button.o -I $(INCLUDE) -I $(INCLUDE_DIR)
link:
#	g++ main.o menu.o button.o LLscreen.o -o main.exe -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
	g++ main.o general.o LLscreen.o node.o -o main.exe -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE)
