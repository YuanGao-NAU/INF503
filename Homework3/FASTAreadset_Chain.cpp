#include "FASTAreadset_Chain.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

void FASTAreadset_Chain::init()
{
    table = NULL;
    num_of_collisions = 0;
    hash_table_size = 0;
    seqs = NULL;
    num_of_seqs = 0;
}

int FASTAreadset_Chain::read_seqs(char *filename)
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

int FASTAreadset_Chain::convert_char_to_int(char x)
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

unsigned int FASTAreadset_Chain::four_based_power(int p)
{
    int res = 1;
    while(p!=0)
    {
        res = 4*res;
        p--;
    }
    return res;
}

int FASTAreadset_Chain::calc_hash_value(char* seq)
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
    hash_value = hash_value % this->hash_table_size;
    return hash_value;
}

int FASTAreadset_Chain::calc_hash_value_div(char* seq)
{
    unsigned int hash_value_div = 0;
    unsigned int hash_value = 0;

    if(seq == "\0")
    {
        return -1;
    }

    for(int i=0; i<16; i++)
    {
        hash_value += this->convert_char_to_int(seq[i]) * this->four_based_power(i);
    }
    hash_value_div = hash_value / this->hash_table_size;
    return hash_value_div;
}

void FASTAreadset_Chain::create_hash_table()
{
    table = new hash_table[this->hash_table_size];
    for(int i=0; i<this->hash_table_size; i++)
    {
        table[i].hash = false;
        table[i].node = NULL;
    }

    for(int i=0; i<this->num_of_seqs; i++)
    {
        unsigned int hash_value = 0;
        unsigned int hash_value_div = 0;

        hash_value = this->calc_hash_value(seqs[i]);
        hash_value_div = this->calc_hash_value_div(seqs[i]);

        //cout << hash_value << '\t' << hash_value_div << endl;

        if(table[hash_value].hash == false)
        {
            table[hash_value].hash = true;
            table[hash_value].node = new Node;
            table[hash_value].node->div = hash_value_div;
            table[hash_value].node->next = NULL;
        }
        else
        {
            table[hash_value].hash = true;
            Node *new_node = new Node;
            new_node->div = hash_value_div;
            new_node->next = table[hash_value].node;
            table[hash_value].node = new_node;
            this->num_of_collisions ++;
        }
    }
}

void FASTAreadset_Chain::insert(char *seq)
{
    unsigned int hash_value = 0;
    unsigned int hash_value_div = 0;
    
    hash_value = this->calc_hash_value(seq);
    hash_value_div = this->calc_hash_value_div(seq);

    if(this->table[hash_value].hash == true)
    {
        table[hash_value].hash = true;
        Node *new_node = new Node;
        new_node->div = hash_value_div;
        new_node->next = table[hash_value].node;
        table[hash_value].node = new_node;
        this->num_of_collisions ++;
    }
    else
    {
        this->table[hash_value].hash = true;
        table[hash_value].node = new Node;
        table[hash_value].node->div = hash_value_div;
        table[hash_value].node->next = NULL;
    }

}

bool FASTAreadset_Chain::search(char *seq)
{
    unsigned int hash_value = 0;
    unsigned int hash_value_div = 0;

    hash_value = this->calc_hash_value(seq);
    hash_value_div = this->calc_hash_value_div(seq);

    if(this->table[hash_value].hash == true)
    {
        Node *temp = table[hash_value].node;
        while(temp != NULL)
        {
            if(temp->div == hash_value_div)
            {
                return true;
            }
            temp = temp->next;
        }
        return false;
    }
    else
    {
        return false;
    }

}

FASTAreadset_Chain::FASTAreadset_Chain(char *filename, int hash_table_size)
{
    this->init();
    int res = 0;
    res = this->read_seqs(filename);
    if(res != 0)
    {
        cout << "The file does not exist or is empty!\n";
        return;
    }

    if(hash_table_size <=0)
    {
        cout << "hash table size can't be 0 or negative.\n";
        return;
    }

    this->hash_table_size = hash_table_size;
    this->create_hash_table();

    return;
}

int FASTAreadset_Chain::get_num_of_seqs()
{
    return this->num_of_seqs;
}

FASTAreadset_Chain::~FASTAreadset_Chain()
{
    for(int i=0; i<this->num_of_seqs; i++)
    {
        delete[] seqs[i];
    }
    delete[] seqs;

    for(int i=0; i<this->hash_table_size; i++)
    {
        if(table[i].hash = true)
        {
            Node *temp1 = table[i].node;
            Node *temp2;
            
            while(temp1 != NULL)
            {
                temp2 = temp1->next;
                delete temp1;
                temp1 = temp2;
            }
        }
    }
}

int FASTAreadset_Chain::get_collisions()
{
    return this->num_of_collisions;
}

