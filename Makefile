all: compile run clean

compile:
	@g++ -std=c++11 main.cpp riverTree.cpp -o river

run:
	@./river

clean:
	@rm -f river
