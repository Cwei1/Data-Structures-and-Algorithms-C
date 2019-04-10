.PHONY: clean debug run

spellCheck: spellCheck.o hash.o
	@echo "Building 'spellCheck'..."
	@g++ -std=c++11 spellCheck.o hash.o -o spellChecker

spellCheck.o: src/SpellChecker.cpp
	@echo "Building 'spellCheck.o'..."
	@g++ -std=c++11 -c src/SpellChecker.cpp

hash.o: src/hash.cpp src/hash.hpp
	@echo "Building 'hash.o'..."
	@g++ -std=c++11 -c src/hash.cpp src/hash.hpp

clean:
	@echo "Cleaning all built files..."
	@rm -f src/*.gch *.o SpellChecker

debug:
	@echo "Building 'spellChecker' with debugging capabilities..."
	@g++ -std=c++11 -g src/SpellChecker.cpp src/hash.cpp  -o SpellChecker

run:
	@./spellChecker