all: compile run clean

compile:
	@g++ -std=c++11 main.cpp tree.cpp -o river

run:
	@./river

clean:
	@rm -f river

test: test_compile test_run test_clean

test_compile:
	@g++ -std=c++11 tree_test.cpp tree.cpp -o tree_tests

test_run:
	@./tree_tests

test_clean:
	@rm -f tree_tests test_tree.bin
