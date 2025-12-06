# --- Variables de Base ---
CXX = g++
TARGET = main
TEST_TARGET = test_main

# --- Drapeaux de Compilation (CXXFLAGS) ---
CXXFLAGS = -g -Wall -Werror -std=c++17 -I./headers

# --- Librairies (LDLIBS) et chemins (LDFLAGS/IFLAGS) ---
IFLAGS = 
LDFLAGS = 
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system $(LDFLAGS)

# --- Découverte des Fichiers Sources ---
EXCLUDE_DIRS = -path ./.git -prune -o -path ./.ccls-cache -prune -o
SRCS = $(filter-out ./src/mainTest.cpp,$(shell find ./src -type f -name '*.cpp' -print)) main.cpp
TEST_SRCS = $(filter-out ./src/mainTest.cpp,$(shell find ./src -type f -name '*.cpp' -print)) test.cpp
HEADERS = $(shell find ./headers -type f -name '*.h' -print -o -type f -name '*.hpp' -print)


# --- Cibles ---

.PHONY: all clean debug test

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(SRCS) -o $@ $(LDLIBS)

test: $(TEST_TARGET)
	./$(TEST_TARGET)

$(TEST_TARGET): $(TEST_SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(TEST_SRCS) -o $@ $(LDLIBS)

debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 -D_DEBUG $(IFLAGS) $(SRCS) -o $(TARGET)-debug $(LDLIBS)

clean:
	rm -f $(TARGET) $(TARGET)-debug $(TEST_TARGET) *.o