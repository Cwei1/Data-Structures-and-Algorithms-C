heaper.exe: heaper.o heap.o hash.o
	g++ -std=c++11 -o heaper.exe heaper.o heap.o hash.o

heaper.o: heaper.cpp
	g++ -std=c++11 -c heaper.cpp

heap.o: heap.cpp heap.h
	g++ -std=c++11 -c heap.cpp

hash.o: hash.cpp hash.h
	g++ -std=c++11 -c hash.cpp

debug:
	g++ -std=c++11 -g -o heaperDebug.exe heaper.cpp heap.cpp hash.cpp

clean:
	rm -f *.exe *.o *.stackdump *~

backup:
	test -d backups || mkdir backups
	cp *.cpp backups
	cp *.h backups
	cp Makefile backups