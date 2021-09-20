#ifndef SMITH_WATERMAN_H
#define SMITH_WATERMAN_H

int** calculate_similarity_scoring(char *str1, char *str2);
void backtracing(int **mat, int loc_row, int loc_col, char *str1, char *str2, int rows[], int cols[], int step, bool show_results);
int smith_w_alg(int **mat, int rows, int cols, char *str1, char *str2, bool show_results);
long get_genome_filesize(char* filename);
char** get_random_seqs(int nums);

#endif