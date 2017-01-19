CC = icpc
MPICC = mpiicpc
CFLAGS = -std=c++11 -qopenmp -O3 -D USE_MKL -mkl=sequential -Wall -xhost

all: main

main: main.cc
	$(CC) main.cc -o main $(CFLAGS)
clean:
	rm -rf main
