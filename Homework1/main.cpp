#include "FASTA_readset.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <fstream>
#include <time.h>
#include <string.h>
#include <unistd.h>

using namespace std;

//int strcmp(char* str1, const char* str2);

int main(int argc, char **argv)
{
	if(argc != 3)
	{
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: 3 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./homework <problem-flag> <filepath>" << endl;
		cout << "Example:" << endl;
		cout << "./homework problem1A /common/contrib/classroom/inf503/hw_dataset.fa"  << endl;
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
	}

	// clock_t start,end;
	// start = clock();
	clock_t start,end;
	double totaltime;
	if(strcmp(argv[1], "problem1A") == 0)
	{
		start = clock();
		FASTA_readset readset(argv[2], 1000000);
		end = clock();
		totaltime = (double)((end - start)/CLOCKS_PER_SEC);
		cout << "time used for 1000000 reads is: " << totaltime << " s"<< endl;

		sleep(20);

		start = clock();
		//readset.print_tail(readset.get_reads());
	}

	else if(strcmp(argv[1], "problem1B") == 0)
	{
		start = clock();
		FASTA_readset readset(argv[2]);
		end = clock();
		totaltime = (double)((end - start)/CLOCKS_PER_SEC);
		cout << "time used for 36000000 reads is: " << totaltime << " s"<< endl;

		sleep(20);

		start = clock();
		//readset.print_tail(readset.get_reads());
	}

	// else if(strcmp(argv[1], "problem3A") == 0)
	// {	
	// 	FASTA_readset readset(argv[2]);
	// 	readset.set_total_unique_seqs();
	// 	cout << "Number of total unique sequences:" << endl;
	// 	cout << readset.get_total_unique_seqs() << endl;
	// 	cout << endl;
	// }
		
	// else if(strcmp(argv[1], "problem3B") == 0)
	// {
	// 	int *temp;
	// 	FASTA_readset readset(argv[2]);
	// 	readset.set_reads_of_each_dataset();
	// 	temp = readset.get_reads_of_each_dataset();
	// 	cout << "Number of reads for each dataset:" << endl;
	// 	for(int i=0; i<14; i++)
	// 	{
	// 		cout << "dataset " << i << ": " << temp[i] << " reads" <<endl;
	// 	}
	// 	cout << endl;
	// }

	// else if(strcmp(argv[1], "problem3C") == 0)
	// {
	// 	FASTA_readset readset(argv[2]);
	// 	int *temp1;
	// 	readset.set_nucleobase_of_each_dataset();
	// 	temp1 = readset.get_nucleobase_of_each_dataset();
	// 	cout << "Number of A, C, G and T in each dataset:" << endl;
	// 	for(int i=0; i<14; i++)
	// 	{
	// 		cout << "dataset " << i << ":" << endl;
	// 		cout << "Number of A: " << temp1[i*4+0] << endl;
	// 		cout << "Number of C: " << temp1[i*4+1] << endl;
	// 		cout << "Number of G: " << temp1[i*4+2] << endl;
	// 		cout << "Number of T: " << temp1[i*4+3] << endl;
	// 	}
	// 	cout << endl;
	// }

	else if(strcmp(argv[1], "problem1C") == 0)
	{	
		FASTA_readset readset(argv[2]);
		readset.set_total_unique_seqs();
		cout << "Number of total unique sequences:" << endl;
		cout << readset.get_total_unique_seqs() << endl;
		cout << endl;
	
		int *temp;
		readset.set_reads_of_each_dataset();
		temp = readset.get_reads_of_each_dataset();
		cout << "Number of reads for each dataset:" << endl;
		for(int i=0; i<14; i++)
		{
			cout << "dataset " << i << ": " << temp[i] << " reads" <<endl;
		}
		cout << endl;

		temp = readset.get_unique_reads_of_each_dataset();
		cout << "Number of unique reads for each dataset:" << endl;
		for(int i=0; i<14; i++)
		{
			cout << "dataset " << i << ": " << temp[i] << " unique reads" <<endl;
		}
		cout << endl;
	
		int *temp1;
		readset.set_nucleobase_of_each_dataset();
		temp1 = readset.get_nucleobase_of_each_dataset();
		cout << "Number of A, C, G and T in each dataset:" << endl;
		for(int i=0; i<14; i++)
		{
			cout << "dataset " << i << ":" << endl;
			cout << "Number of A: " << temp1[i*4+0] << endl;
			cout << "Number of C: " << temp1[i*4+1] << endl;
			cout << "Number of G: " << temp1[i*4+2] << endl;
			cout << "Number of T: " << temp1[i*4+3] << endl;
		}
		cout << endl;
	}

	else if(strcmp(argv[1], "problem1D") == 0)
	{
		FASTA_readset readset(argv[2]);
		start = clock();
	}

	else if(strcmp(argv[1], "problem1E") == 0)
	{
		char **temp;

		FASTA_readset readset(argv[2]);
		readset.sort_seqs();
		temp = readset.get_sorted_seqs();
		cout << "The first 20 lines of sorted output:" << endl;
		readset.print_head(20, true);
	}

	if (strcmp(argv[1], "problem1A") == 0 || strcmp(argv[1], "problem1B") == 0 || strcmp(argv[1], "problem1D") == 0)
	{
		end = clock();
		totaltime = (double)(1000 * (end - start)/CLOCKS_PER_SEC);
		cout << "time used for release the memory is about: " << totaltime << " ms"<< endl;
	}
	return 0;

	// int *p;
	// FASTA_readset readset(argv[2]);
	// for(int i=1; i<=readset.get_reads(); i++)
	// {
	// 	p = readset.get_seq_repeat_in_dataset(i);
	// 	for(int j=1; j<15; j++)
	// 	{
	// 		cout << p[j] << ' ';
	// 		if(p[j] > 100) return 0;
	// 	}
	// 	cout << endl;
	// }
}

// int strcmp(char* str1, const char* str2)
// {
//     int i = 0;
//     int len_str1 = 0, len_str2 = 0;

//     while(str1[len_str1] != '\0')
//         len_str1 ++;
//     while(str2[len_str2] != '\0')
//         len_str2 ++;

//     int len = (len_str1 < len_str2 ? len_str1:len_str2);

//     for(i=0; i<len; i++)
//     {
//         if(str1[i] < str2[i])
//         {
//             return -1;
//         }
//         else if(str1[i] > str2[i])
//         {
//             return 1;
//         }
//     }

//     if(len_str1 == len_str2)
//     {
//         return 0;
//     }

//     if(len == len_str1)
//     {
//         return -1;
//     }
//     else
//     {
//         return 1;
//     }

//     return 0;
// }