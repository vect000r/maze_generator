CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra
SFML_LIBS = -lsfml-graphics -lsfml-window -lsfml-system

# Nazwa twojego programu
TARGET = maze_generator

# Pliki źródłowe (dostosuj nazwy do swoich plików)
SOURCES = main.cpp 
OBJECTS = $(SOURCES:.cpp=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(OBJECTS) -o $(TARGET) $(SFML_LIBS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

.PHONY: all clean