#include "FASTAreadset_LL.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

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

    clock_t start,end;
	double totaltime;

    if(strcmp(argv[1], "problem1A") == 0)
    {
        start = clock();
        FASTAreadset_LL readset(argv[2], false);
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
		cout << "time used for reading all the reads is: " << totaltime << " s"<< endl;
        sleep(20);
    }
    else if(strcmp(argv[1], "problem1B") == 0)
    {
        FASTAreadset_LL readset(argv[2], false);
    }
    else if(strcmp(argv[1], "problem1C") == 0)
    {
        cout << endl;
        FASTAreadset_LL readset(argv[2], false);
        cout << "first 10 segments from the file:" << endl;
        readset.print_seq_head(10);
        cout << endl;
        cout << "first 10 segments from the copied object:" << endl;
        FASTAreadset_LL copied_object(readset);
        copied_object.print_seq_head(10); 
        cout << endl;
    }
    else if(strcmp(argv[1], "problem1D") == 0)
    {
        char seq1[51] = "CTAGGTACATCCACACACAGCAGCGCATTATGTATTTATTGGATTTATTT";
        char seq2[51] = "GCGCGATCAGCTTCGCGCGCACCGCGAGCGCCGATTGCACGAAATGGCGC";
        char seq3[51] = "CGATGATCAGGGGCGTTGCGTAATAGAAACTGCGAAGCCGCTCTATCGCC";
        char seq4[51] = "CGTTGGGAGTGCTTGGTTTAGCGCAAATGAGTTTTCGAGGCTATCAAAAA";
        char seq5[51] = "ACTGTAGAAGAAAAAAGTGAGGCTGCTCTTTTACAAGAAAAAGTNNNNNN";

        Node *n1, *n2, *n3, *n4, *n5;

        FASTAreadset_LL readset(argv[2], false);
        n1 = readset.search_seq(seq1);
        n2 = readset.search_seq(seq2);
        n3 = readset.search_seq(seq3);
        n4 = readset.search_seq(seq4);
        n5 = readset.search_seq(seq5);

        if(n1 == NULL)
        {
            cout << seq1 << " not found!" << endl;
        }
        else
        {
            cout << seq1 << " found!" << endl;
        }

        if(n2 == NULL)
        {
            cout << seq2 << " not found!" << endl;
        }
        else
        {
            cout << seq2 << " found!" << endl;
        }

        if(n3 == NULL)
        {
            cout << seq3 << " not found!" << endl;
        }
        else
        {
            cout << seq3 << " found!" << endl;
        }

        if(n4 == NULL)
        {
            cout << seq4 << " not found!" << endl;
        }
        else
        {
            cout << seq4 << " found!" << endl;
        }

        if(n5 == NULL)
        {
            cout << seq5 << " not found!" << endl;
        }
        else
        {
            cout << seq5 << " found!" << endl;
        }
        sleep(20);
    }
    else if(strcmp(argv[1], "problem2A") == 0)
    {
        Node *temp;
        FASTAreadset_LL genome_set(argv[3], true);
        temp = genome_set.get_chain();
        
        int length = 0;
        while(temp != NULL)
        {
            length ++;
            temp = temp->next;
        }
        cout << "The number of 50-character fragments is: " << length << endl;
    }
    else if(strcmp(argv[1], "problem2B") == 0)
    {
        FASTAreadset_LL readset(argv[2], false);
        FASTAreadset_LL genome_set(argv[3], true);
        int nums = 0;
        int times = 100000;               //change this value to set how many times you want running the search
        int reads = 0;
        int segments = 0;

        Node *temp1;
        Node *temp2;

        temp1 = genome_set.get_chain();
        while(temp1 != NULL)
        {
            segments ++;
            temp1 = temp1->next;
        }

        temp2 = readset.get_chain();
        while(temp2 != NULL)
        {
            reads ++;
            temp2 = temp2->next;
        }

        cout << endl;
        cout << "Reads in the read set: " << reads << endl;
        cout << "segments in the genome file: " << segments << endl;
        cout << endl;

        temp1 = genome_set.get_chain();
        start = clock();

        for(int i=0; i<times; i++)
        {
            temp2 = readset.search_seq(temp1->sequence);
            if(temp2 != NULL)
            {
                nums ++;
                //cout << nums << endl;
            }
            temp1 = temp1->next;
        }
        cout << "Found " << nums << " 50-character fragments in readset!" << endl;

        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
		cout << "Time cost is: " << totaltime << " s"<< endl;
        
    }

    return 0;
}
