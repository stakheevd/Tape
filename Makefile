all: build test
.PHONY: all build run test clean

build:
	clang++ main.cpp Tape.cpp -o main
	clang++ generator.cpp -o generator
	touch config.txt

run:
	./main $(fname)

test:
	clang++ generator.cpp -o generator
	clang++ unit_tests.cpp Tape.cpp -o unit_tests -lgtest -lgmock
	./generator 0
	./generator 1
	./generator 100
	./generator 1000
	./generator 10000
	./generator 100000
	./generator 1000000
	./generator 10000000
	echo "3 0 -12 4 12 -99 1 -35 4 pl 6 2 -32 1 8" > invalid_data.txt
	./unit_tests

clean:
	rm /tmp/first_tape
	rm /tmp/second_tape
	rm numbers_*.txt
	rm invalid_data.txt
