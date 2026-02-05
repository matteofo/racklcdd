.PHONY: tests

SOURCES := src/*.cpp src/data/*.cpp src/data/*.c src/data/pve/*.cpp

CFLAGS :=  -static -static-libgcc -static-libstdc++ -Isrc/ -Isrc/data/ -I/src/data/pve/
LFLAGS := -lboost_thread -g

STD_VER := c++23

TARGET := racklcdd

all:
	g++ $(CFLAGS) -o $(TARGET) -std=$(STD_VER) $(SOURCES) $(LFLAGS)

tests:
	cd ./tests/ && make

clean:
	rm -rf $(TARGET)
	cd ./tests/ && make clean