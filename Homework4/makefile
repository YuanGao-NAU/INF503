main : main.o smith_waterman.o BLAST.o
	g++ -o main main.o smith_waterman.o BLAST.o

BLAST.o : BLAST.cpp 
	g++ -c BLAST.cpp 

smith_waterman.o : smith_waterman.cpp 
	g++ -c smith_waterman.cpp 

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o smith_waterman.o BLAST.o
