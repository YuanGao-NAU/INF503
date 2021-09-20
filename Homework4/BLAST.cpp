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

char** break_down_genome(char *filename, int &seed_num, char **output_genome)
{
    long size = get_genome_filesize(filename);
    long length = 0;
    char *genome;
    char **seed;
    //cout << size << endl;
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

    seed = new char*[strlen(genome)-11+1];
    for(int i = 0; i < strlen(genome)-11+1; i ++)
    {
        seed[i] = new char[12];
        strncpy(seed[i], &genome[i], 11);
        seed[i][11] = '\0';
    }

    // output_genome = genome;
    *output_genome = genome;
    //delete[] genome;
    seed_num = strlen(genome)-11+1;

    return seed;
}

int convert_char_to_int(char x)
{
    if(x == 'A')
        return 0;
    else if(x == 'C')
        return 1;
    else if(x == 'G')
        return 2;
    else if(x == 'T')
        return 3;
    else
        return -1;
}

int four_based_power(int p)
{
    int res = 1;
    while(p!=0)
    {
        res = 4*res;
        p--;
    }
    return res;
}

dat_element* create_dat(char **seqs, int seqs_size, int word_size)
{
    dat_element *dat = new dat_element[four_based_power(word_size)];
    for(int i = 0; i < four_based_power(word_size); i ++)
    {
        dat[i].exist = false;
    }
    
    for(int i = 0; i < seqs_size; i ++)
    {
        int hash_value = 0;
        for(int j = 0; j < word_size; j ++)
        {
            hash_value = hash_value + convert_char_to_int(seqs[i][j])*four_based_power(j);
        }
        // cout << i << ", " << hash_value << endl;
        // cout << seqs_size << endl;

        if(dat[hash_value].exist == false)
        {
            dat[hash_value].exist = true;
            dat[hash_value].pos.where = i;
            dat[hash_value].pos.next = NULL;
        }
        else
        {
            position *temp1, *temp2;
            temp1 = new position;
            temp1->where = i;
            temp1->next = NULL;
            temp2 = dat[hash_value].pos.next;

            dat[hash_value].pos.next = temp1;
            temp1->next = temp2;
        }
    }
    return dat;
}

bool search_dat(dat_element *dat, int word_size, int hash_value)
{
    return dat[hash_value].exist;
}

char** get_reads(char *filename, int &reads)
{
    int count_lines = 0;
    ifstream instream;
    instream.open(filename);
    if(!instream.is_open())
    {
        cout << "can not open the file \"" << filename << "\", please check the file name!" << endl;
        return NULL; 
    }

    while(!instream.eof())
    {
        char test[50];
        count_lines++;
        instream >> test;
    }

    if(count_lines%2 == 1)                  // since each read has two lines, count_lines can't be odd
        count_lines = count_lines - 1;

    if(count_lines == 0)                    // if the file is empty, return
    {                    
        return NULL;
    }

    char **seqs = new char*[count_lines/2];
    instream.clear();
    instream.seekg(0, std::ios::beg);
    
    for(int i = 0; i < count_lines/2; i++)
    {
        seqs[i] = new char[51];
        instream.getline(seqs[i], 51);
        instream.getline(seqs[i], 51);
    }
    reads = count_lines/2;
    return seqs;
}

char** get_k_mers_from_read(char *seq, int seq_size, int word_size)
{
    char **seqs = new char*[seq_size- word_size + 1];

    for(int i = 0; i < seq_size- word_size + 1; i ++)
    {
        seqs[i] = new char[word_size + 1];
        strncpy(seqs[i], &seq[i], word_size);
        seqs[i][word_size] = '\0';
    }
    return seqs;
}

char** extend_from_seed(int hash_value, dat_element* dat, char *genome, int &num_of_str)
{
    position *temp;
    char **str = NULL;
    num_of_str = 0;

    if(dat[hash_value].exist != true)
        return NULL;

    temp = &dat[hash_value].pos;

    while(temp != NULL)
    {
        num_of_str++;
        temp = temp->next;
    }

    str = new char*[num_of_str];
    for(int i = 0; i < num_of_str; i++)
    {
        str[i] = new char[51];
    }

    int genome_len = strlen(genome);

    int i = 0;

    temp = &dat[hash_value].pos;
    
    while(temp != NULL)
    {
        int where = temp->where;

        if(where < 20)
        {
            strncpy(str[i], &genome[0], 50);
        }
        else if(genome_len - where < (20 + 12))
        {
            strncpy(str[i], &genome[genome_len - 51], 50);
        }
        else
        {
            strncpy(str[i], &genome[where - 20], 50);
        }
        i++;
        temp = temp->next;
    }
    return str;
}

bool hash_in_read(int hash_value_excepted, char *seq, int seq_length)
{
    char str[12] = {"           "};
    for(int i = 0; i < seq_length; i ++)
    {
        strncpy(str, &seq[i], 11);
        int hash_value = 0;
        for(int j = 0; j < 11; j ++)
        {
            hash_value = hash_value + convert_char_to_int(str[j])*four_based_power(j);
        }
        if(hash_value_excepted == hash_value)
        {
            return true;
        }
    }
    return false;
}

char** random_fragments_from_genome(char *genome, int fragment_size, bool with_random_error)
{
    time_t t;

    srand((unsigned) time(&t));
    int size = 0;

    char **random_genome = new char*[fragment_size];

    char temp1[4] = {"CGT"};
    char temp2[4] = {"AGT"};
    char temp3[4] = {"ACT"};
    char temp4[4] = {"ACG"};

    while(genome[size] != '\0')
        size ++;

    if(with_random_error == false)
    {
        for(int i = 0; i < fragment_size; i ++)
        {
            random_genome[i] = new char[51];
            int temp = rand() % (size - 50 + 1);
            strncpy(random_genome[i], &genome[temp], 50);
            random_genome[i][50] = '\0';
        }
    }
    else
    {
        char *genome_temp = new char[size+1];
        strcpy(genome_temp, genome);
        for(int i = 0; i < size; i ++)
        {
            int temp = rand() % size;
            if(temp < size/20)          //5% chance to change the base
            {
                int ran = rand() % 3;
                if(genome_temp[i] == 'A')
                {
                    genome_temp[i] = temp1[ran];
                }
                else if(genome_temp[i] == 'C')
                {
                    genome_temp[i] = temp2[ran];
                }
                else if(genome_temp[i] == 'G')
                {
                    genome_temp[i] = temp3[ran];
                }
                else if(genome_temp[i] == 'T')
                {
                    genome_temp[i] = temp4[ran];
                }
            }
        }
        for(int i = 0; i < fragment_size; i ++)
        {
            random_genome[i] = new char[51];
            int temp = rand() % (size - 50 + 1);
            strncpy(random_genome[i], &genome_temp[temp], 50);
            //cout << "i = " << i << ", str = " << random_genome[i] << endl;
            //cout << &genome_temp[temp] << endl;
            random_genome[i][50] = '\0';
        }
        delete[] genome_temp;
    }
    return random_genome;
}


int seed_based_sw_alg(char **seeds, char **reads, int seeds_num, int reads_num, char *genome, int word_size, int seq_sze, bool show_results)
{
    char **k_mers;
    int num_of_str = 0;
    char **extend_str = NULL;
    int hash_value = 0;
    int **mat;
    int max;
    int *list = new int[reads_num];
    int fragment_num = 0;

    dat_element* dat;
    dat = create_dat(seeds, seeds_num, 11);

    for(int i = 0; i < reads_num; i++)
    {
        if(show_results == true)
        {
            cout << "**********************************results for the # " << i << " read:******************************************" << endl << endl;
        }
        k_mers = get_k_mers_from_read(reads[i], 50, word_size);
        list[i] = 0;
        for(int j = 0; j < 50-word_size+1; j ++)
        {
            hash_value = 0;
            for(int k = 0; k < word_size; k++)
            {
                hash_value = hash_value + convert_char_to_int(k_mers[j][k])*four_based_power(k);
            }
            if(dat[hash_value].exist)
            {
                extend_str = extend_from_seed(hash_value, dat, genome, num_of_str);
                if(extend_str != NULL)
                {
                    for(int k = 0; k < num_of_str; k ++)
                    {
                        int rows = strlen(extend_str[k]);
                        int cols = strlen(reads[i]);
                        mat = calculate_similarity_scoring(extend_str[k], reads[i]);
                        max = smith_w_alg(mat, rows, cols, extend_str[k], reads[i], show_results);
                
                        //cout << "read num = " << i << ", hash_value = " << hash_value << ", max = " << max << endl;
                        if(max == 100)          //all the 50 characters match
                        {
                            list[i] = 1;
                        }
                        //cout << "read num = " << i << ", j = " << j << endl;
                    }
                }
            }
        }
        if(list[i] == 1)
        {
            fragment_num ++;
        }
        //cout << "read num = " << i << ", fragment = " << fragment_num << endl;
    }
    delete[] list;
    return fragment_num;
}




