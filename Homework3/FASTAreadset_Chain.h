#ifndef FASTAREADSET_CHAIN_H
#define FASTAREADSET_CHAIN_H

struct Node
{
    int div;
    Node *next;
};

struct hash_table
{
    bool hash;
    Node *node;
};

class FASTAreadset_Chain
{
    private:
        char **seqs;
        hash_table *table;
        int num_of_collisions;
        int hash_table_size;
        int num_of_seqs;
        int read_seqs(char *filename);
        int calc_hash_value(char *seq);
        int calc_hash_value_div(char *seq);
        int convert_char_to_int(char x);
        unsigned int four_based_power(int p);
        void create_hash_table();
        void init();

    public:
        bool search(char *seq);
        void insert(char *seq);
        int get_num_of_seqs();
        FASTAreadset_Chain(char *filename, int hash_table_size);
        ~FASTAreadset_Chain();
        int get_collisions();

};

#endif

