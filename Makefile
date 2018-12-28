TARGET=part
all:
	g++ -Wall -Wextra -pedantic -O2 -std=c++14 main.cpp -o $(TARGET)

clean:
	rm -f $(TARGET)
