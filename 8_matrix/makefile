CXX = gcc

# Для избежания ошибки для sigaction
CXXFLAGS = -D_XOPEN_SOURCE=700

TARGET1 = sigaction
TARGET2 = signal

SRC1 = sigaction.c
SRC2 = signal.c

$(TARGET1): $(SRC1)
	$(CXX) $(SRC1) $(CXXFLAGS) -o $(TARGET1)

$(TARGET2): $(SRC2)
	$(CXX) $(SRC2) $(CXXFLAGS) -o $(TARGET2)

all: $(TARGET1) $(TARGET2)

clean:
	rm -f $(TARGET1) $(TARGET2)