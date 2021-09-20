#ifndef FASTA_READSET_H
#define FASTA_READSET_H

class FASTA_readset
{
    private:
        char **sequences;
        char **headers;
        char **ordered_seqs;
        int reads;
        int total_unique_sequences;
        int reads_of_each_dataset[14];
        int unique_reads_of_each_dataset[14];
        int nucleobase_of_each_dataset[14][4];              //number of A,G,C,T in each dataset
        int p[15];                                          //how many times one read repeats for each dataset, 
                                                            //the first element indicate the 
        int q[14];                                          //Does the sequence exist in each dataset?

        void quicksort_seqs(int left, int right);
        void read_repeat_in_datasets(int read);
        void read_occurence_in_datasets(int read);
        void initial();
        // void strcpy(char* dest, char* src);
        // int strcmp(char* str1, char* str2);

    public:
        FASTA_readset();
        FASTA_readset(char *filename);
        FASTA_readset(char *filename, int reads);
        ~FASTA_readset();
        //void statistics();
        void print_sequences();
        void print_headers();
        void set_reads(int reads);
        int get_reads();
        void set_total_unique_seqs();
        int get_total_unique_seqs();
        void set_reads_of_each_dataset();
        int* get_reads_of_each_dataset();
        int* get_unique_reads_of_each_dataset();
        void set_nucleobase_of_each_dataset();
        int* get_nucleobase_of_each_dataset();
        void sort_seqs();
        void copy_seqs();
        char** get_sorted_seqs();
        char** get_seqs();
        char** get_headers();
        void print_tail(int n, bool sorted);
        void print_head(int n, bool sorted);
        // int cmp_ori_sorted();
        // char** test();
};

#endif