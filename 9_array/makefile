CXX = g++

CXXFLAGS = -std=c++17 -lgtest

TARGET1 = test
TARGET2 = program

SRC1 = test.cpp
SRC2 = maxsum.cpp

$(TARGET1): $(SRC1)
	$(CXX) $(SRC1) $(CXXFLAGS) -o $(TARGET1)

$(TARGET2): $(SRC2)
	$(CXX) $(SRC2) $(CXXFLAGS) -o $(TARGET2)

all: $(TARGET1) $(TARGET2)

clean:
	rm -f $(TARGET1) $(TARGET2)