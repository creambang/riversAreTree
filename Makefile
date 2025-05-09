all: compile run_main run_test clean

compile:
	@g++ -std=c++11 main.cpp tree.cpp -o river
	@g++ g++ -std=c++17 tree_test.cpp tree.cpp -o tree_tests

run_main:
	@echo "Running main program:"
	@./river
run_test:
	@echo "Running tree tests:"
	@./tree_tests
clean:
	@rm -f river tree_tests

