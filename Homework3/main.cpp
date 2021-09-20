#include "FASTAreadset_Chain.h"
#include "FASTAreadset_DA.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>

using namespace std;

long get_genome_filesize(char *filename);

char** get_genome_seqs(char *filename, int &num_of_sequence);

int main(int argc, char **argv)
{
	if(argc != 4)
	{
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: 4 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./homework <problem-flag> <FASTA_filepath> <genome_filepath>" << endl;
		cout << "Example:" << endl;
		cout << "./homework problem1A FASTAreadset_file_path genome_file_path"  << endl;
		cout << "=========================="<< endl << endl;
		cout << "exiting..." << endl;
		exit(-1);
	}
	else
	{
		cout << "The number of arguments passed: " << argc << endl;
		cout << "The first argument is: " << argv[0] << endl;
		cout << "The second argument is: " << argv[1] << endl; 
		cout << "The third argument is: " << argv[2] << endl;
        cout << "The fourth argument is: " << argv[3] << endl;
	}

    int num_of_seqs_in_genome;
    char **genome_seqs = get_genome_seqs(argv[3], num_of_seqs_in_genome);
    clock_t start,end;
	double totaltime;

    if(strcmp(argv[1], "problem1A") == 0)
    {
        FASTAreadset_DA readset(argv[2]);
        readset.get_info();
    }
    else if(strcmp(argv[1], "problem1B") == 0)
    {
        int frag_found = 0;
        FASTAreadset_DA readset(argv[2]);
        start = clock();
        for(int i=0; i<num_of_seqs_in_genome; i++)
        {
            if(readset.search(genome_seqs[i]) == true)
                frag_found ++;
        }
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "Total used to complete the entire search process is: " << totaltime << " s" << endl;
        cout << frag_found << " genome 16-mer fragments were found in the read set.\n";
    }
    else if(strcmp(argv[1], "problem2A") == 0)
    {
        start = clock();
        FASTAreadset_Chain readset(argv[2], 10000);
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "It takes " << totaltime << " s to read the sequences when the table size is 10,000\n";
        cout << readset.get_collisions() << " collisions found when the table size is 10,000\n";

        start = clock();
        FASTAreadset_Chain readset1(argv[2], 100000);
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "It takes " << totaltime << " s to read the sequences when the table size is 100,000\n";
        cout << readset1.get_collisions() << " collisions found when the table size is 100,000\n";

        start = clock();
        FASTAreadset_Chain readset2(argv[2], 1000000);
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "It takes " << totaltime << " s to read the sequences when the table size is 1,000,000\n";
        cout << readset2.get_collisions() << " collisions found when the table size is 1,000,000\n";

        start = clock();
        FASTAreadset_Chain readset3(argv[2], 10000000);
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "It takes " << totaltime << " s to read the sequences when the table size is 10,000,000\n";
        cout << readset3.get_collisions() << " collisions found when the table size is 10,000,000\n";
    }
    else if(strcmp(argv[1], "problem2B") == 0)
    {
        int frag_found = 0;
        FASTAreadset_Chain readset(argv[2], 10000000);
        start = clock();
        for(int i=0; i<num_of_seqs_in_genome; i++)
        {
            if(readset.search(genome_seqs[i]) == true)
                frag_found ++;
        }
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "Total used to complete the entire search process is: " << totaltime << " s" << endl;
        cout << frag_found << " genome 16-mer fragments were found in the read set.\n";
    }

    return 0;

}

long get_genome_filesize(char* filename)
{
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

char** get_genome_seqs(char *filename, int &num_of_sequence)
{
    char **seqs;
    char *temp;
    ifstream instream;
    int initial_size = 1000;
    long length = 0;
    int len = 0;

    long size = get_genome_filesize(filename);

    temp = new char[initial_size];
    char *genome = new char[size];

    instream.open(filename);
    instream.getline(temp, 1000);

    while(!instream.eof())
    {
        streampos oldpos = instream.tellg();
        instream.getline(temp, 1000);
        while(strlen(temp) >= initial_size)
        {
            instream.seekg(oldpos);
            delete[] temp;
            initial_size = 2*initial_size;
            temp = new char[initial_size];
            instream.getline(temp, 1000);
        }
        strcpy(&genome[length], temp);
        length += strlen(temp);
    }
    delete[] temp;

    len = strlen(genome);
    seqs = new char*[len-15];

    for(int i=0; i<len-16; i++)
    {
        seqs[i] = new char[17];
        memcpy(seqs[i], &genome[i], 16);
        seqs[i][16] = '\0';
    }
    seqs[len-16] = new char[17];
    memcpy(seqs[len-16], &genome[len-16], 16);
    seqs[len-16][16] = '\0';
    
    num_of_sequence = len - 16 + 1;

    return seqs;
}