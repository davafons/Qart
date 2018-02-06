CC = g++

TARGET = qart

FLAGS = -Wall -std=c++14

LINKER_FLAGS = -lSDL2 -lSDL2_image

_dummy := $(shell mkdir -p obj)


SRCS := $(wildcard src/*.cpp)
OBJS := $(addprefix obj/,$(notdir $(SRCS:.cpp=.o)))

$(TARGET) : $(OBJS)
	$(CC) $^ -o $@ $(LINKER_FLAGS)
	
obj/%.o : src/%.cpp
	$(CC) $(FLAGS) -c $< -o $@
	
clean:
	rm $(OBJS) $(TARGET)