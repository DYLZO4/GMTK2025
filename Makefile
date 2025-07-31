CXX = g++
CXXFLAGS = -Wall -g -std=c++17
LIBS = -lsfml-graphics -lsfml-window -lsfml-system
SRC_EXT = cpp

# Pattern rule: e.g., 'make main' builds main from main.cpp
%: %.$(SRC_EXT)
	$(CXX) $(CXXFLAGS) $< -o $@ $(LIBS)

clean:
	rm -f *.out *.o *~ a.out core main
