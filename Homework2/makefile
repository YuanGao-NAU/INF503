main : main.o FASTAreadset_LL.o
	g++ -o main main.o FASTAreadset_LL.o

FASTAreadset_LL.o : FASTAreadset_LL.cpp 
	g++ -c FASTAreadset_LL.cpp 

main.o : main.cpp
	g++ -c main.cpp

clean:
	rm main main.o FASTAreadset_LL.o
