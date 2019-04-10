.PHONY: clean debug run

RunDijkstra: RunDijkstra.o hash.o heap.o graph.o
	@echo "Building 'RunDijkstra'..."
	@g++ -std=c++11 RunDijkstra.o hash.o heap.o graph.o -o RunDijkstra

RunDijkstra.o: RunDijkstra.cpp
	@echo "Building 'RunDijkstra.o'..."
	@g++ -std=c++11 -c RunDijkstra.cpp

hash.o: hash.cpp hash.hpp
	@echo "Building 'hash.o'..."
	@g++ -std=c++11 -c hash.cpp hash.hpp

heap.o: heap.cpp heap.hpp
	@echo "Building 'heap.o'..."
	@g++ -std=c++11 -c heap.cpp heap.hpp

graph.o: graph.cpp graph.hpp
	@echo "Building 'graph.o'..."
	@g++ -std=c++11 -c graph.cpp graph.hpp

clean:
	@echo "Cleaning all built files..."
	@rm -f *.gch *.o RunDijkstra

debug:
	@echo "Building RunDijkstra with debugging capabilities..."
	@g++ -std=c++11 -g RunDijkstra.cpp hash.cpp heap.cpp -o RunDijkstra

run:
	@./RunDijkstra
