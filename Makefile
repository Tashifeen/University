CXX := g++
CXXFLAGS := -Wall -Wextra -O2 -std=c++17

SRC := graph_colouring.cc
OUT := graph_colouring

all: $(OUT)

$(OUT): $(SRC)
	$(CXX) $(CXXFLAGS) -o $(OUT) $(SRC)

clean:
	rm -f $(OUT)

.PHONY: all clean
