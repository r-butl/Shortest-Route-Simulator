view:
	vimdiff tests/test_04.out results/test_04.myout

test: comp
	./executeme < tests/test_01.in

code:
	vim driver.cpp

comp:
	g++ -std=c++11 -o executeme driver.cpp Graph.cpp PQueue.cpp
