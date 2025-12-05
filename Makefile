CXX = g++
TARGET = main
CXXFLAGS = -g -Wall -Werror -std=c++17 -I./headers
LDFLAGS =
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system

SRCS = $(shell find ./src -type f -name '*.cpp') main.cpp
HEADERS = $(shell find ./headers -type f -name '*.hpp' -o -name '*.h')

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(SRCS) -o $@ $(LDFLAGS) $(LDLIBS)

debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -O0 -D_DEBUG $(SRCS) -o $(TARGET)-debug $(LDFLAGS) $(LDLIBS)

clean:
	rm -f $(TARGET) $(TARGET)-debug *.o
