CC				= g++
COMPILE_OPTS	= -std=c++1z -Wall
INCLUDES		= 
LIBS			= 
OPTIMIZATION	= 
SRC_DIR			= .
OBJ_DIR			= obj
BIN_DIR			= bin

EXEC			= test.exe
SOURCES			= $(SRC_DIR)/Semver.cpp $(SRC_DIR)/main.cpp
ND_SRC			= $(notdir $(SOURCES))
OBJECTS			= $(ND_SRC:%.cpp=$(OBJ_DIR)/%.o)

all: dir $(EXEC)

dir:
	mkdir -p $(OBJ_DIR)
	mkdir -p $(BIN_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(COMPILE_OPTS) $(OPTIMIZATION) -c $< -o $@ $(INCLUDES)

$(EXEC): $(OBJECTS)
	$(CC) $(LINK_OPTS) $(OBJECTS) -o $(BIN_DIR)/$(EXEC) $(LIBS)

clean:
	rm -rf $(OBJ_DIR)
	rm -rf $(BIN_DIR)