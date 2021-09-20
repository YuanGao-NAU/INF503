#ifndef FASTAREADSET_LL_H
#define FASTAREADSET_LL_H

#include <fstream>
using namespace std;

struct Node
{
    char* sequence;
    Node* next;
};

class FASTAreadset_LL
{
    private:
        Node* head;
        //long length; 
        long get_genome_filesize(char* filename);
        //long get_length();

    public:
        FASTAreadset_LL();
        //FASTAreadset_LL(char* filename);
        FASTAreadset_LL(char* filename, bool is_genome);
        FASTAreadset_LL(const FASTAreadset_LL &obj);
        int readset(char* filename);
        void init();
        ~FASTAreadset_LL();
        void print_seq_head(int n);
        void print_seq();
        Node* search_seq(char* seq);
        Node* get_chain();
};

#endif