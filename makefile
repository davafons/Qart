CC = g++

TARGET = Qart

_dummy := $(shell mkdir obj bin)

SRCS := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/, $(notdir $(SRCS:.cpp=.o)))

INCLUDE_PATHS = -I$(CURDIR)\include\SDL2
LIBRARY_PATHS = -L$(CURDIR)\lib

LINKER_FLAGS = -lSDL2 -lSDL2_image

COMPILER_FLAGS = -Wall -std=c++14

ifeq ($(OS), Windows_NT)
$(TARGET): $(OBJS)
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $^ -o bin\$@ -lmingw32 -lSDL2main $(LINKER_FLAGS)

obj/%.o: src/%.cpp
	$(CC) $(INCLUDE_PATHS) $(LIBRARY_PATHS) $(COMPILER_FLAGS) -c $< -o $@

clean:
	del /s /q *.o $(TARGET).exe

else
$(TARGET) : $(OBJS)
	$(CC) $^ -o bin/$@ $(LINKER_FLAGS)

obj/%.o: src/%.cpp
	$(CC) $(COMPILER_FLAGS) -c $< -o $@

clean:
	rm -rf $(OBJS) bin/$(TARGET)
endif
