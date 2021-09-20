#include <iostream>
#include <time.h>
#include <fstream>

using namespace std;

int main(int argc, char **argv)
{
    char** headers;
    char** sequences;

    clock_t start,end;
    double totaltime;

    start = clock();
    ifstream instream;
    instream.open(argv[1]);
    for(int i = 0; i < 1000000; i++)
    {
        instream;
        instream;
    }
    end = clock();
    totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
	cout << "time used for 1000000 reads is: " << totaltime << " ms"<< endl;

    instream.clear();
    instream.seekg(0, std::ios::beg);
    start = clock();
    for(int i = 0; i < 36000000; i++)
    {
        instream;
        instream;
    }
    end = clock();
    totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
	cout << "time used for 36000000 reads is: " << totaltime << " ms"<< endl;

    start = clock();
    headers = new char*[1000000];
    for(int i=0; i<1000000; i++)
    {
        headers[i] = new char[50];
    }
    end = clock();
    totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
	cout << "time used for allocating memory for 1000000 reads is: " << totaltime << " ms"<< endl;

    for(int i=0; i<1000000; i++)
    {
        delete[] headers[i];
    }
    delete[] headers;

    start = clock();
    headers = new char*[36000000];
    for(int i=0; i<36000000; i++)
    {
        headers[i] = new char[50];
    }
    end = clock();
    totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
	cout << "time used for allocating memory for 36000000 reads is: " << totaltime << " ms"<< endl;

    for(int i=0; i<36000000; i++)
    {
        delete[] headers[i];
    }
    delete[] headers;

    cout << "######################################" << endl;

    instream.clear();
    instream.seekg(0, std::ios::beg);
    start = clock();
    headers = new char*[1000000];
    sequences = new char*[1000000];
    for(int i=0; i<1000000; i++)
    {
        headers[i] = new char[50];
        sequences[i] = new char[50];
        instream >> headers[i];
        instream >> sequences[i];
    }
    end = clock();
    totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
	cout << "time used for allocating and writing 1000000 reads is: " << totaltime << " ms"<< endl;

    for(int i=0; i<1000000; i++)
    {
        delete[] headers[i];
        delete[] sequences[i];
    }
    delete[] headers;
    delete[] sequences;

    instream.clear();
    instream.seekg(0, std::ios::beg);
    start = clock();
    headers = new char*[36000000];
    sequences = new char*[36000000];
    for(int i=0; i<36000000; i++)
    {
        headers[i] = new char[50];
        sequences[i] = new char[50];
        instream >> headers[i];
        instream >> sequences[i];
    }
    end = clock();
    totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
	cout << "time used for allocating and writing 36000000 reads is: " << totaltime << " ms"<< endl;

    for(int i=0; i<36000000; i++)
    {
        delete[] headers[i];
        delete[] sequences[i];
    }
    delete[] headers;
    delete[] sequences;

    return 0;

}