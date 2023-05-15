path = ..\Menu\src
CODE_DIR = ..\Menu\code
INCLUDE_DIR = ..\Menu\include
INCLUDE = "$(path)\include"
LIBRARY = "$(path)\lib"
SFML_INCLUDE = -lsfml-graphics -lsfml-window -lsfml-system
RES_FILE = ..\Menu\resource.rc

SRCS = $(wildcard $(CODE_DIR)/*.cpp)
OBJS = $(SRCS:$(CODE_DIR)/%.cpp=%.o)

all: compile link

compile: $(OBJS)

%.o: $(CODE_DIR)/%.cpp
	g++ -c $< -o $@ -I $(INCLUDE) -I $(INCLUDE_DIR) -g

link: $(OBJS) $(RES_FILE)
	windres.exe $(RES_FILE) -O coff -o resources.o
	g++ $(OBJS) resources.o -o dsv.exe -L $(LIBRARY) $(SFML_INCLUDE) -mwindows