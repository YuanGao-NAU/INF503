#include "FASTAreadset_DA.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

void FASTAreadset_DA::init()
{
    dat = NULL;
    num_of_collisions = 0;
    num_of_elements = 0;
    seqs = NULL;
    num_of_seqs = 0;
}

int FASTAreadset_DA::read_seqs(char *filename)
{
    int count_lines = 0;
    ifstream instream;
    instream.open(filename);
    if(instream.fail())
    {
        seqs = NULL;
        num_of_seqs = 0;
        return -1;
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
        seqs = NULL;
        num_of_seqs = 0;
        return -1;
    }

    seqs = new char*[count_lines/2];

    instream.clear();
    instream.seekg(0, std::ios::beg);
    
    for(int i = 0; i < count_lines/2; i++)
    {
        seqs[i] = new char[17];
        instream.getline(seqs[i], 17);
        instream.getline(seqs[i], 17);
        //instream >> seqs[i];
    }
    this->num_of_seqs = count_lines/2;
    return 0;
}

int FASTAreadset_DA::convert_char_to_int(char x)
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

long int FASTAreadset_DA::four_based_power(int p)
{
    long int res = 1;
    while(p!=0)
    {
        res = 4*res;
        p--;
    }
    return res;
}

unsigned int FASTAreadset_DA::calc_hash_value(char* seq)
{
    unsigned int hash_value = 0;

    if(seq == "\0")
    {
        return -1;
    }
    
    for(int i=0; i<16; i++)
    {
        hash_value += this->convert_char_to_int(seq[i]) * this->four_based_power(i);
    }
    return hash_value;
}

void FASTAreadset_DA::create_dat()
{
    unsigned int hash_value = 0;

    dat = new bool[this->four_based_power(16)];

    for(long int i=0; i<this->four_based_power(16); i++)
    {
        dat[i] = false;
    }

    cout << "init success!\n";

    for(int i=0; i<this->num_of_seqs; i++)
    {
        hash_value = FASTAreadset_DA::calc_hash_value(this->seqs[i]);
        if(dat[hash_value] == true)
        {
            this->num_of_collisions ++;
        }
        else
        {
            dat[hash_value] = true;
        }
    }

    cout << "record success!\n";

    for(long int i=0; i<this->four_based_power(16); i++)
    {
        if(dat[i] == true)
        {
            this->num_of_elements ++;
        }
    }
}

bool FASTAreadset_DA:: search(char *seq)
{
    unsigned int hash_value;
    hash_value = calc_hash_value(seq);
    return dat[hash_value];
}

void FASTAreadset_DA::insert(char *seq)
{
    unsigned int hash_value;
    hash_value = calc_hash_value(seq);
    if(dat[hash_value] == true)
    {
        cout << "element already existed!" << endl;
        return;
    }
    else
    {
        dat[hash_value] = true;
        cout << "insertion succeed!" << endl;
    }
}

FASTAreadset_DA::FASTAreadset_DA(char *filename)
{
    this->init();
    int res = 0;
    res = this->read_seqs(filename);
    if(res != 0)
    {
        cout << "The file does not exist or is empty!\n";
        return;
    }

    cout << "successfully read data from file: " << filename << endl;

    this->create_dat();

    return;
}

FASTAreadset_DA::~FASTAreadset_DA()
{
    delete[] dat;
    for(int i=0; i<this->num_of_seqs; i++)
    {
        delete[] this->seqs[i];
    }
    delete[] this->seqs;
}

int FASTAreadset_DA::get_num_of_seqs()
{
    return this->num_of_seqs;
}

int FASTAreadset_DA::get_collisions()
{
    return this->num_of_collisions;
}

int FASTAreadset_DA::get_num_of_elements()
{
    return this->num_of_elements;
}

float FASTAreadset_DA::calc_alpha_t()
{
    return (float(this->num_of_elements) / four_based_power(16));
}

void FASTAreadset_DA::get_info()
{
    cout << "The size of the direct access table is: " << this->four_based_power(16) << endl;
    cout << "There are " << this->get_collisions() << " collisions in the direct access table" << endl;
    cout << "There are " << this->get_num_of_elements() << " unique sequences in the direct access table." << endl;
    cout << "The alpha_T of the direct access table is: " << this->calc_alpha_t() << endl;
    cout << "number of sequences is: " << this->num_of_seqs << endl;
}
