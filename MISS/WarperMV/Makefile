# Declaration of variables
CC = g++
CC_FLAGS = -std=c++11
CC_LIB =  -L. -lmv
 
# File names
EXEC = main
SOURCES = $(wildcard *.cpp)
OBJECTS = $(SOURCES:.cpp=.o)
 
# Main target
$(EXEC): $(OBJECTS)
	ar -cvq libwarpermv.a $^
 
# To obtain object files
%.o: %.cpp
	$(CC) -c $(CC_FLAGS) $< -o $@ 
 
# To remove generated files
clean:
	rm -f $(EXEC) $(OBJECTS)
