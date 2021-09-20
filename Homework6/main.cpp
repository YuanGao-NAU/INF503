#include "SuffixTrie.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

long get_genome_filesize(char* filename);
char* get_genome(char *filename);
char** random_36_mers(char *genome, int number_of_sequence, int sequence_length, int mutation_percent);

int main(int argc, char** argv) {

    if(argc != 4)
	{
		cout << endl << endl << "=========================="<< endl;
		cout << "Error: 3 input parameters expected" <<endl;
		cout << "Proper usage is:" <<endl;
		cout << "./main <problem-flag> <SARS-COV2 genome file> <number_of_random_segment>" << endl;
		cout << "Example:" << endl;
		cout << "./main problem1A SARS_COV2_genome_file.txt 1000"  << endl;
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
        cout << "The forth argument is: " << argv[3] << endl;
	}

    char *genome = get_genome(argv[2]);
    SuffixTrie *suffixTrie = new SuffixTrie(genome, strlen(genome));
    if(strcmp(argv[1], "problem1A") == 0)
    {
        char str1[37] = "TTTTAAGTGTTATGGAGTGTCTCCTACTAAATTAAA";
        char str2[37] = "TCTACCAGTGTCTATGACCAAGACATCAGTAGATTG";
        char str3[37] = "TTTACAAGACTTCAGAGTTTAGATAATGTGGCTTTT";
        char str4[37] = "TACCAATTTACCTTTACAGCTAGTTTTTTCTACAGG";
        char str5[37] = "CCTTACCGCAGAGACAGAAGAAACAGCAAACTGTGA";

        cout << suffixTrie->search(str1, strlen(str1)) << endl;
        cout << suffixTrie->search(str2, strlen(str2)) << endl;
        cout << suffixTrie->search(str3, strlen(str3)) << endl;
        cout << suffixTrie->search(str4, strlen(str4)) << endl;
        cout << suffixTrie->search(str5, strlen(str5)) << endl;
    }

    if(strcmp(argv[1], "problem1B") == 0)
    {
        char **segments = random_36_mers(genome, atoi(argv[3]), 36, 0);
        int x = 0;
        for(int i = 0; i < atoi(argv[3]); i ++) {
            //cout << res[i] << endl;
            bool temp = suffixTrie->search(segments[i], strlen(segments[i]));
            if(temp == true) {
                x++;
            }
            delete[] segments[i];
        }
        cout << "found " << x << " in " << argv[3] << " sequences"<< endl;
        cout << "Total Nodes: " << suffixTrie->get_node_num() << endl;
        delete[] segments;
    }
    delete[] genome;
}

long get_genome_filesize(char* filename) {
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

char* get_genome(char *filename) {
    long size = get_genome_filesize(filename);
    long length = 0;
    char *genome;
    genome = new char[size];

    ifstream instream;
    char *temp = new char[1000];

    instream.open(filename);
    if(!instream.is_open())
    {
        cout << "can not open the file \"" << filename << "\", please check the file name!" << endl;
         return NULL;
    }

    instream.getline(temp, 1000);

    while(!instream.eof())
    {
        streampos oldpos = instream.tellg();
        instream.getline(temp, 1000);
        
        strcpy(&genome[length], temp);
        // cout << length << endl;
        length += strlen(temp);
    }
    delete[] temp;
    instream.close();
    return genome;
}

char** random_36_mers(char *genome, int number_of_sequence, int sequence_length, int mutation_percent) {
    if(number_of_sequence == 0 || genome == NULL)
        return NULL;

    int len = strlen(genome);

    if(mutation_percent != 0) {
        char temp1[4] = {"CGT"};
        char temp2[4] = {"AGT"};
        char temp3[4] = {"ACT"};
        char temp4[4] = {"ACG"};

        for(int i = 0; i < len-36; i ++) {
            
            int temp = rand() % len;
            if((temp/float(len))*100 <= mutation_percent ) {        
                int ran = rand() % 3;
                if(genome[i] == 'A')
                {
                    genome[i] = temp1[ran];
                }
                else if(genome[i] == 'C')
                {
                    genome[i] = temp2[ran];
                }
                else if(genome[i] == 'G')
                {
                    genome[i] = temp3[ran];
                }
                else if(genome[i] == 'T')
                {
                    genome[i] = temp4[ran];
                }
            }
        }
    }

    char** res = new char*[number_of_sequence];
    for(int i = 0; i < number_of_sequence; i ++) {
        res[i] = new char[sequence_length+1];
        int temp = rand() % (len - 36+1);
        strncpy(res[i], &genome[i], sequence_length);
        res[i][sequence_length] = '\0';
    }

    return res;
    
}