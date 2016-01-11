all: hash cerca_binaria bloom generadorRandom

hash: hash_table.o
	g++ -g -o hash hash_table.o

hash_table.o: hash_table.cc
	g++ -c -g hash_table.cc

bloom: Bloom_filter.o
	g++ -g -o bloom Bloom_filter.o

Bloom_filter.o:
	g++ -c -g Bloom_filter.cpp

cerca_binaria: cerca_binaria.o
	g++ -g -o cerca_binaria cerca_binaria.o

cerca_binaria.o:
	g++ -c -g cerca_binaria.cc

generadorRandom: generadorRandom.o
	g++ -g -o generadorRandom generadorRandom.o

generadorRandom.o:
	g++ -c -g generadorRandom.cc

clean:
	rm -f *.o
	rm -f hash
	rm -f bloom
	rm -f cerca_binaria
	rm -f generadorRandom
