CXX = g++
CXXFLAGS = -std=c++11
OBJ = circular_sector.o ellipse.o triangle.o sort.o main.o
SRC = circular_sector.cpp ellipse.cpp triangle.cpp sort.cpp main.cpp
EXE = main
.PHONY: all clean
all: $(EXE)
$(EXE): $(OBJ)
	$(CXX) -o $@ $(OBJ)
$(OBJ): $(SRC)
	$(CXX) -c $?
clean:
	rm -f $(EXE)
	rm -f $(OBJ)
