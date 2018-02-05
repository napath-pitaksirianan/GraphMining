# Declaration of variables
CC = g++
CC_FLAGS = -O3 -pipe -DNDEBUG  -DIPOPT_BUILD `PKG_CONFIG_PATH=/home/napath/Ipopt/Build/lib64/pkgconfig:/home/napath/Ipopt/Build/lib/pkgconfig:/home/napath/Ipopt/Build/share/pkgconfig: pkg-config --cflags ipopt` 

#-Wparentheses -Wreturn-type -Wcast-qual -Wall -Wpointer-arith -Wwrite-strings -Wconversion -Wno-unknown-pragmas -Wno-long-long


CC_LIB = -Wl,--rpath -Wl,/home/napath/Ipopt/Build/lib `PKG_CONFIG_PATH=/home/napath/Ipopt/Build/lib64/pkgconfig:/home/napath/Ipopt/Build/lib/pkgconfig:/home/napath/Ipopt/Build/share/pkgconfig: pkg-config --libs ipopt`
 
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