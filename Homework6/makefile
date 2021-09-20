main : main.o SuffixTrie.o
	g++ -o main main.o SuffixTrie.o

SuffixTrie.o : SuffixTrie.cpp
	g++ -c SuffixTrie.cpp

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o SuffixTrie.o
