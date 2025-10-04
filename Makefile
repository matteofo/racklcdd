SOURCES := src/*.cpp src/data/*.cpp src/data/*.c

CFLAGS := -Isrc/ -Isrc/data/
LFLAGS := -lboost_system -lboost_thread -g

STD_VER := c++23

TARGET := racklcdd

all:
	g++ $(CFLAGS) -o $(TARGET) -std=$(STD_VER) $(SOURCES) $(LFLAGS)