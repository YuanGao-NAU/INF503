#ifndef FASTAREADSET_DA_H
#define FASTAREADSET_DA_H

class FASTAreadset_DA
{
    private:
        bool *dat;
        int num_of_collisions;
        int num_of_elements;
        char **seqs;
        int num_of_seqs;
        int read_seqs(char *filename);
        int convert_char_to_int(char x);
        long int four_based_power(int p);
        void create_dat();
        void init();
        unsigned int calc_hash_value(char *seq);
    
    public:
        FASTAreadset_DA(char *filename);
        ~FASTAreadset_DA();
        bool search(char *seq);
        void insert(char *seq);
        int get_num_of_seqs();
        int get_collisions();
        int get_num_of_elements();
        float calc_alpha_t();
        void get_info();
};

#endif