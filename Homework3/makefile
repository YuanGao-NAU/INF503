main : main.o FASTAreadset_DA.o FASTAreadset_Chain.o
	g++ -o main main.o FASTAreadset_DA.o FASTAreadset_Chain.o

FASTAreadset_DA.o : FASTAreadset_DA.cpp 
	g++ -c FASTAreadset_DA.cpp 

FASTAreadset_Chain.o : FASTAreadset_Chain.cpp 
	g++ -c FASTAreadset_Chain.cpp 

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o FASTAreadset_DA.o FASTAreadset_Chain.o
