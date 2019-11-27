CC 			= g++
CCFLAGS 	= -static -std=c++11
INCLUDE		= -I"../src"
TARGET		= test.exe
OPTIMIZE	= -O3

$(TARGET):	test.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) $(OPTIMIZE) test.cpp -o $(TARGET)

opt:	test.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) -O3 test.cpp -o $(TARGET)

nopt:	test.cpp
	$(CC) $(CCFLAGS) $(INCLUDE) -O0 test.cpp -o $(TARGET)

all: $(TARGET)


clean:
	rm test.exe
