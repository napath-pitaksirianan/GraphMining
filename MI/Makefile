# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11
CC_LIB = -lm nauty26r7/nauty.a
CC_INC = -I nauty26r7
 
# File names
EXEC = main
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	$(MAKE) -C nauty26r7
	$(CC) $(OBJECTS) -o $(EXEC) $(CC_LIB)
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ $(CC_INC)
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
	$(MAKE) -C nauty26r7 clean