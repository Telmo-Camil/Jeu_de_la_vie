# --- Variables de Base ---
CXX = g++
TARGET = main

# --- Drapeaux de Compilation (CXXFLAGS) ---
CXXFLAGS = -g -Wall -Werror -std=c++11

# --- Librairies (LDLIBS) et chemins (LDFLAGS/IFLAGS) ---
IFLAGS = 
LDFLAGS = 
LDLIBS = -lsfml-graphics -lsfml-window -lsfml-system $(LDFLAGS)

# --- Découverte des Fichiers Sources (Correction du chemin) ---
# Exclusion des répertoires .git et .ccls-cache
EXCLUDE_DIRS = -path ./.git -prune -o -path ./.ccls-cache -prune -o
SRCS = $(shell find . $(EXCLUDE_DIRS) -type f -name '*.cpp' -print)
HEADERS = $(shell find . $(EXCLUDE_DIRS) -type f -name '*.h' -print -o -type f -name '*.hpp' -print)


# --- Cibles ---

.PHONY: all clean debug

all: $(TARGET)

$(TARGET): $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) $(IFLAGS) $(SRCS) -o $@ $(LDLIBS)

debug: $(SRCS) $(HEADERS)
	$(CXX) $(CXXFLAGS) -U_FORTIFY_SOURCE -O0 -D_DEBUG $(IFLAGS) $(SRCS) -o $(TARGET)-debug $(LDLIBS)

clean:
	rm -f $(TARGET) $(TARGET)-debug *.o