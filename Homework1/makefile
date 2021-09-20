main : main.o FASTA_readset.o
	g++ -o main main.o FASTA_readset.o

FASTA_readset.o : FASTA_readset.cpp 
	g++ -c FASTA_readset.cpp 

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o FASTA_readset.o
