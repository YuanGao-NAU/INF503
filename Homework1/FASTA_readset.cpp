#include "FASTA_readset.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>

using namespace std;

FASTA_readset::FASTA_readset()
{
    this->initial();
}

FASTA_readset::FASTA_readset(char *filename)
{
    this->initial();
    cout << "creating object!" << endl;
    int count_lines = 0;
    ifstream instream;
    instream.open(filename);
    if(instream.fail())
    {
        sequences = NULL;
        headers = NULL;
        return;
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
        sequences = NULL;
        headers = NULL;
        return;
    }

    sequences = new char*[count_lines/2];
    headers = new char*[count_lines/2];

    instream.clear();
    instream.seekg(0, std::ios::beg);
    
    for(int i = 0; i < count_lines/2; i++)
    {
        headers[i] = new char[100];
        sequences[i] = new char[51];
        instream >> headers[i];
        instream >> sequences[i];
    }

    cout << "Got " << count_lines/2 << " reads." << endl;
    
    this->set_reads(count_lines/2);
    this->copy_seqs();
}

FASTA_readset::FASTA_readset(char *filename, int reads)
{
    this->initial();
    int count_lines = 0;
    ifstream instream;
    instream.open(filename);
    if(instream.fail())
    {
        sequences = NULL;
        headers = NULL;
        cout << "can not open the file!" << endl;
        return;
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
        cout << "the file is empty!" << endl;    
        sequences = NULL;
        headers = NULL;
        return;
    }

    if(reads*2 > count_lines)
    {
        cout << "no enough reads in the file!" << endl;
        sequences = NULL;
        headers = NULL;
        return;
    }

    instream.clear();
    instream.seekg(0, std::ios::beg);

    sequences = new char*[reads];
    headers = new char*[reads];

    for(int i = 0; i < reads; i++)
    {
        headers[i] = new char[100];
        sequences[i] = new char[51];
        instream >> headers[i];
        instream >> sequences[i];
    }

    cout << "Got " << reads << " reads." << endl;

    this->set_reads(reads);
    this->copy_seqs();
}

//void FASTA_readset::statistics(){}

void FASTA_readset::set_reads(int reads)
{
    this->reads = reads;
}

int FASTA_readset::get_reads()
{
    return this->reads;
} 

void FASTA_readset::print_headers()
{
    int reads;
    reads = this->get_reads();
    for(int i=0; i < reads; i++)
    {
        cout << this->headers[i] << endl;
    }

}

void FASTA_readset::print_sequences()
{
    int reads;
    reads = this->get_reads();
    for(int i=0; i < reads; i++)
    {
        cout << this->sequences[i] << endl;
    }
}

void FASTA_readset::set_total_unique_seqs()
{
    this->total_unique_sequences = this->reads;
}

int FASTA_readset::get_total_unique_seqs()
{
    return this->total_unique_sequences;
}

void FASTA_readset::set_reads_of_each_dataset()
{
    for(int i=0; i<14; i++)
    {
        this->reads_of_each_dataset[i] = 0;
    }

    int reads = this->get_reads();
    
    for(int i=0; i<reads; i++)
    {
        int len=0;
        int k = 0, m = 0;
        int* p = NULL;

        this->read_repeat_in_datasets(i+1);
        this->read_occurence_in_datasets(i+1);

        // while(headers[i][len] != '\0')         //get the length of each header
        //     len ++;
        for(int j=0; j<1000; j++)
        {
            if(headers[i][j] == '_')
            {
					//int count = int(headers[i][j+1]) - 48;		//48 is the ASCII code for 0
                this->reads_of_each_dataset[k] += this->p[k+1];
                this->unique_reads_of_each_dataset[k] += this->q[k];
                k++;
            }
            else if(headers[i][j] == '\0')
                break;
        }
        k = 0;
        len = 0;

    }
}

int* FASTA_readset::get_reads_of_each_dataset()
{
    return this->reads_of_each_dataset;
}

int* FASTA_readset::get_unique_reads_of_each_dataset()
{
    return this->unique_reads_of_each_dataset;
}

void FASTA_readset::set_nucleobase_of_each_dataset()
{
    for(int i=0; i<14; i++)
    {
        for(int j=0; j<4; j++)
        {
            this->nucleobase_of_each_dataset[i][j] = 0;
            // cout << &(this->nucleobase_of_each_dataset[i][j]) << endl;
        }
    }

    int reads = this->get_reads();

    for(int i=0; i<reads; i++)
    {
        int len=0;
        int k = 0;

        this->read_repeat_in_datasets(i+1);

        // while(headers[i][len] != '\0')         //get the length of each header
        //     len ++;
        for(int j=0; j<1000; j++)
        {
            if(headers[i][j] == '_')
            {
                    // cout << "k=" << k << "," << "i=" << i << endl;
					//int count = int(headers[i][j+1]) - 48;
                for(int m=0; m<50; m++)
                {
                    switch(this->sequences[i][m])
                    {
                        case 'A':
                            this->nucleobase_of_each_dataset[k][0] += this->p[k+1];
                            //cout << "A" << endl;
                            break;
                        case 'G':
                            this->nucleobase_of_each_dataset[k][1] += this->p[k+1];
                            //cout << "G" << endl;
                            break;
                        case 'C':
                            this->nucleobase_of_each_dataset[k][2] += this->p[k+1];
                            //cout << "C" << endl;
                            break;
                        case 'T':
                            this->nucleobase_of_each_dataset[k][3] += this->p[k+1];
                            //cout << "T" << endl;
                            break;
                        default:
                            break;
                    }
                }
                k++;
            }
            else if(headers[i][j] == '\0')
            {
                break;
            }
        }
        k = 0;
    }

}

int* FASTA_readset::get_nucleobase_of_each_dataset()
{
    return &(this->nucleobase_of_each_dataset[0][0]);
}

void FASTA_readset::sort_seqs()
{
    this->quicksort_seqs(0, this->reads-1);
}

void FASTA_readset::copy_seqs()
{
    ordered_seqs = new char*[reads];
    
    for(int i=0; i<reads; i++)
    {
        ordered_seqs[i] = new char[51];
        strcpy(ordered_seqs[i], sequences[i]);
    }
}

void FASTA_readset::quicksort_seqs(int left, int right)
{
    int i, j, t;

    int left_flag = 1;
    int right_flag = 1;

    //cout << "left=" << left << ", right=" << right << endl;

    char temp[51], switch_temp[51];
    if(left > right)
        return;

    //temp = this->ordered_seqs[left];
    strcpy(temp, this->ordered_seqs[left]);

    i = left;
    j = right;

    while(i!=j)
    {
        while(strcmp(this->ordered_seqs[j], temp) >= 0 && i < j)
        {
            j--;
        }

        while(strcmp(this->ordered_seqs[i], temp) <= 0 && i < j)
        {
            i++;
        }

        if(i<j)
        {
            // cout << "i=" << i << ", j=" << j << endl;
            // cout << "this->ordered_seqs[i]=" << this->ordered_seqs[i] << endl;
            // cout << "this->ordered_seqs[j]=" << this->ordered_seqs[j] << endl;
            // cout << endl;

            // switch_temp = this->ordered_seqs[i];
            // this->ordered_seqs[i] = this->ordered_seqs[j];
            // this->ordered_seqs[j] = switch_temp;
            strcpy(switch_temp, this->ordered_seqs[i]);
            strcpy(this->ordered_seqs[i], this->ordered_seqs[j]);
            strcpy(this->ordered_seqs[j], switch_temp);

            // cout << "this->ordered_seqs[i]=" << this->ordered_seqs[i] << endl;
            // cout << "this->ordered_seqs[j]=" << this->ordered_seqs[j] << endl;
            // cout << endl;
        }
    }

    // this->ordered_seqs[left] = this->ordered_seqs[i];
    // this->ordered_seqs[i] = temp;

    strcpy(this->ordered_seqs[left], this->ordered_seqs[i]);
    strcpy(this->ordered_seqs[i], temp);

    quicksort_seqs(left, i-1);
    quicksort_seqs(i+1, right);

}

char** FASTA_readset::get_sorted_seqs()
{
    return this->ordered_seqs;
}

char** FASTA_readset::get_seqs()
{
    return this->sequences;
}

char** FASTA_readset::get_headers()
{
    return this->headers;
}

FASTA_readset::~FASTA_readset()
{
    for(int i=0; i<this->reads; i++)
    {

        if(this->sequences != NULL)
        {
            delete[] (this->sequences[i]);
        }
        if(this->headers != NULL)
        {
            delete[] (this->headers[i]);
        }
        if(this->ordered_seqs != NULL)   //sorted sequences, type: **
        {
            delete[] (this->ordered_seqs[i]);
        }
    }
    if(this->sequences != NULL)
    {
        delete[] this->sequences;
    }
    if(this->headers != NULL)
    {
        delete[] this->headers;
    }
    if(this->ordered_seqs != NULL)  
    {
        delete[] this->ordered_seqs;
    }
    cout << "memory released!" << endl;
}

void FASTA_readset::initial()
{
    this->sequences = NULL;
    this->headers = NULL;
    this->ordered_seqs = NULL;
    for(int i=0; i<14; i++)
    {
        q[i] = 0;
        p[i] = 0;
        reads_of_each_dataset[i] = 0;
        unique_reads_of_each_dataset[i] = 0;
        for(int j=0; j<14; j++)
        {
            nucleobase_of_each_dataset[i][j] = 0;
        }
    }
    reads = 0;
    total_unique_sequences = 0;
}

void FASTA_readset::read_repeat_in_datasets(int read)             //get repeat times of a specific read in each data set
{
    if(read > this->reads || read <= 0)
    {
        return;
    }

    char* header = this->headers[read-1];

    char temp[100];

    int len = 0, i=0, k=0;
    // while(header[len] != '\0')
    //     len++;

    for(int j=0; j<=1000; j++)
    {
        if(header[j] >= '0' && header[j] <= '9')
        {
            temp[k] = header[j];
            k++;
        }
        else if(header[j] == '_' || header[j] == '\0')
        {
            temp[k] = '\0';
            this->p[i] = atoi(temp);
            i++;
            k=0;
        }

        if(header[j] == '\0')
            break;
    }
}

void FASTA_readset::read_occurence_in_datasets(int read)            //whether a read occurs in each dataset
{
    if(read > this->reads || read <= 0)
    {
        return;
    }

    int k = 0;

    char* header = this->headers[read-1];
    for(int j=0; j<1000; j++)
    {
        if(header[j] == '_')
        {
            if(header[j+1] > '0' && header[j+1] < '9')                                     //we don't need to know what the exact number is, just exists or not
            {
                this->q[k] = 1;
            }
            else
            {
                this->q[k] = 0;
            }
            k++;
        }
        else if(header[j] == '\0')
        {
            break;
        }
    }

    // int sum = 0;
    // for(int i=0; i<14; i++)
    // {
    //     sum += this->q[i];
    // }
    // cout << sum << endl;
}

void FASTA_readset::print_tail(int n, bool sorted)
{
    if(n > this->reads)
    {
        cout << "no enough reads!" << endl;
    }
    //cout << "last " << n << " reads:" << endl;
    if(sorted == true)
    {
        for(int i=this->reads-n; i<this->reads; i++)
        {
            cout << ordered_seqs[i] << endl;
        }
        return;
    }
    else
    {
        for(int i=this->reads-n; i<this->reads; i++)
        {
            cout << sequences[i] << endl;
        }
        return;
    }
}

void FASTA_readset::print_head(int n, bool sorted)
{
    if(n > this->reads)
    {
        cout << "no enough reads!" << endl;
    }
    //cout << "first " << n << " reads:" << endl;
    if(sorted == true)
    {
        for(int i=0; i<n; i++)
        {
            cout << ordered_seqs[i] << endl;
        }
        return;
    }
    else
    {
        for(int i=0; i<n; i++)
        {
            cout << sequences[i] << endl;
        }
        return;
    }
}

// void FASTA_readset::strcpy(char* dest, char* src)
// {
//     int i = 0;
//     while(src[i] != '\0')
//     {
//         dest[i] = src[i];
//         i++;
//     }
//     dest[i] = '\0';
// }

// int FASTA_readset::strcmp(char* str1, char* str2)
// {
//     int i = 0;
//     int len_str1 = 0, len_str2 = 0;

//     while(str1[len_str1] != '\0')
//         len_str1 ++;
//     while(str2[len_str2] != '\0')
//         len_str2 ++;

//     int len = len_str1 < len_str2 ? len_str1:len_str2;

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