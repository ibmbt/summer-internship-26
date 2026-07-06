# Compiler and Flags
CC = gcc
CFLAGS = -O3 -march=native
INCLUDES = -I/usr/local/include
LDFLAGS = -L/usr/local/lib
LIBS = -lblis -lm

TARGET = blis_benchmark
SRC = blis_benchmark.c

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(INCLUDES) $(SRC) $(LDFLAGS) $(LIBS) -o $(TARGET)

run: $(TARGET)
	BLIS_NUM_THREADS=8 ./$(TARGET)

clean:
	rm -f $(TARGET)