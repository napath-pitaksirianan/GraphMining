# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11
CC_LIB = -L. -lm -lwarpermv -lmv
 
# File names
EXEC = main
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC) $(CC_LIB)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ 
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)