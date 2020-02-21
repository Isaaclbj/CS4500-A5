build:
	g++ bench.cpp -lpthread -o bench

run: 
	gunzip < datafile.tar.gz | tar xvf -
	./bench

clean:
	rm -f bench.o
	rm -f bench.exe
	rm -f datafile.txt