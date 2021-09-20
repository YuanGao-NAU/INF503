#ifndef BLAST_H
#define BLAST_H

struct position
{
    int where;
    position* next;
};

struct dat_element
{
    bool exist;
    position pos;
};

char** break_down_genome(char *filename, int &seed_num, char **output_genome);
int four_based_power(int p);
int convert_char_to_int(char x);
dat_element* create_dat(char **seqs, int seqs_size, int word_size);
char** get_reads(char *filename, int &reads);
char** get_k_mers_from_read(char *seq, int seq_size, int word_size);
char** extend_from_seed(int hash_value, dat_element* dat, char *genome, int &num_of_str);
bool search_dat(dat_element *dat, int word_size, int hash_value);
bool hash_in_read(int hash_value_excepted, char *seq, int seq_length);
char** random_fragments_from_genome(char *genome, int fragment_size, bool with_random_error);
int seed_based_sw_alg(char **seeds, char **reads, int seeds_num, int reads_num, char *genome, int word_size, int seq_sze, bool show_results);

//void best_match(int **mat, int loc_row, int loc_col, char *str1, char *str2, int rows[], int cols[], int step);

#endif