path = ..\Menu\src
CODE_DIR = ..\Menu\code
INCLUDE_DIR = ..\Menu\include
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = $(wildcard $(CODE_DIR)/*.cpp)
OBJS = $(SRCS:$(CODE_DIR)/%.cpp=%.o)

all: compile link

compile: $(OBJS)

%.o: $(CODE_DIR)/%.cpp
	g++ -c $< -o $@ -I $(INCLUDE) -I $(INCLUDE_DIR) -g

link:
	g++ $(OBJS) -o dsv.exe -L $(LIBRARY) $(SFMLFLAGS) $(SFML_INCLUDE) -mwindows