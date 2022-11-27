bin/test_circular_list: tests/test_circular_list.cpp
	mkdir -p bin
	$(CXX) -std=c++11 -I./ -o $@ $^

test: bin/test_circular_list
	./bin/test_circular_list

.PHONY: test

