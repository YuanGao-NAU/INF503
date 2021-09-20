#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "smith_waterman.h"
#include "BLAST.h"

using namespace std;

int main(int argc, char **argv)
{

    if(argc != 5)
	{
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: 4 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./main <problem-flag> <SARS-COV2 genome file> <Readset file> <number of random sequences you want to generate>" << endl;
		cout << "Example:" << endl;
		cout << "./main problem1A SARS_COV2_genome_file_path readset_file_path 1000"  << endl;
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
        cout << "The fifth argument is: " << argv[4] << endl;
	}

    clock_t start,end;
	double totaltime;

    //1A
    int** mat;
    char *genome;
    int seeds_num;
    char **seeds;
    int reads_num;
    char **reads;
    int max = 0;

    seeds = break_down_genome(argv[2], seeds_num, &genome);
    reads = get_reads(argv[3], reads_num);

    if(strcmp(argv[1], "problem1A") == 0)
    {
        for(int i = 0; i < reads_num; i ++)
        {
            cout << "****************************results for # " <<  i << " read:********************************" << endl;
            int rows = strlen(genome);
            int cols = strlen(reads[i]);
            mat = calculate_similarity_scoring(genome, reads[i]);
            max = smith_w_alg(mat, rows, cols, genome, reads[i], true);
            cout << "the score for # " << i << "read is :" << max << endl;
        }
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
    
        for(int i = 0; i < reads_num; i ++)
        {
            delete[] reads[i];
        }
        delete[] reads;
    }

    //1B
    if(strcmp(argv[1], "problem1B") == 0)
    {
        start = clock();
        int seqs_num = atoi(argv[4]);
        reads = get_random_seqs(seqs_num);
        for(int i = 0; i < seqs_num; i ++)
        {   
            cout << "*************************************results for the # " << i << " randomly generated read:*************************************" << endl << endl;
            int rows = strlen(genome);
            int cols = strlen(reads[i]);
            mat = calculate_similarity_scoring(genome, reads[i]);
            max = smith_w_alg(mat, rows, cols, genome, reads[i], true);
            cout << "the score for # " << i << "read is :" << max << endl;
        }
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "total time for " << seqs_num << "random sequences is " << totaltime << "s" << endl;

        for(int i = 0; i < reads_num; i ++)
        {
            delete[] reads[i];
        }
        delete[] reads;
    }

    int word_size = 11;
    int seq_size = 50;

    dat_element* dat;
    dat = create_dat(seeds, seeds_num, 11);


    //2A
    if(strcmp(argv[1], "problem2A") == 0)
    {
        seed_based_sw_alg(seeds, reads, seeds_num, reads_num, genome, word_size, seq_size, true);
    }

    //2B
    if(strcmp(argv[1], "problem2B") == 0)
    {
        start = clock();
        int seqs_num = atoi(argv[4]);
        reads = get_random_seqs(seqs_num);
        int fragment_num = seed_based_sw_alg(seeds, reads, seeds_num, seqs_num, genome, word_size, seq_size, true);
        end = clock();
        totaltime = (double)((end - start)/CLOCKS_PER_SEC);
        cout << "total time for " << seqs_num << "random sequences is " << totaltime << "s" << endl;

        for(int i = 0; i < reads_num; i ++)
        {
            delete[] reads[i];
        }
        delete[] reads;
    }

    //2C
    if(strcmp(argv[1], "problem2C") == 0)
    {
        cout << "random select 100,000 fragments from SARS-COV2 genome:" << endl;
        int fragment_size = 100000;
        char** random_genome = random_fragments_from_genome(genome, fragment_size, false);
        int fragment_num = seed_based_sw_alg(seeds, random_genome, seeds_num, fragment_size, genome, word_size, seq_size, false);
        cout << "fragment found in SARS-COV2: " << fragment_num << endl;

        for(int i = 0; i < fragment_size; i ++)
        {
            delete[] random_genome[i];
        }
        delete[] random_genome;

        cout << "random select 100,000 fragments from SARS-COV2 genome with 5% mutation:" << endl;
        random_genome = random_fragments_from_genome(genome, fragment_size, true);
        fragment_num = seed_based_sw_alg(seeds, random_genome, seeds_num, fragment_size, genome, word_size, seq_size, false);
        cout << "fragment found in SARS-COV2: " << fragment_num << endl;

        for(int i = 0; i < fragment_size; i ++)
        {
            delete[] random_genome[i];
        }
        delete[] random_genome;
    }

    delete[] genome;
    delete[] seeds;
    
    return 0;
}