main : main.o prefix_trie.o
	g++ -o main main.o prefix_trie.o

prefix_trie.o : prefix_trie.cpp
	g++ -c prefix_trie.cpp

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o prefix_trie.o
