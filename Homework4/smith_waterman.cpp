#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/stat.h>
#include "smith_waterman.h"

using namespace std;

int max_value(int a, int b)
{
    return a>b?a:b;
}

int** calculate_similarity_scoring(char *str1, char *str2)
{
    int rows, cols;
    rows = strlen(str1);
    cols = strlen(str2);

    int **mat = new int*[rows+1];               //consider gap as the first element of row and col

    for(int i = 0; i < rows+1; i++)
    {
        mat[i] = new int[cols+1];
        for(int j = 0; j < cols+1; j++)
        {
            mat[i][j] = 0;
        }
    }

    for(int i = 1; i < rows+1; i++)             //calculate the scores
    {
        for(int j = 1; j < cols+1; j++)
        {
            int potential_score = 0;
            if(str1[i-1] == str2[j-1])
            {
                potential_score = 2;
            }
            else
            {
                potential_score = -1;
            }
            
            int temp = 0;
                        //mat[i-1][j-1] + 2 or mat[i-1][j-1] + (-1) // a gap
            temp = max_value(mat[i-1][j-1] + potential_score, mat[i-1][j]+(-3));  
                                    // a gap
            temp = max_value(temp, mat[i][j-1]-3);
            temp = max_value(temp, 0);              //score can not be negative

            mat[i][j] = temp;

        }
    }

    // for(int i = 0; i < rows+1; i++)
    // {
    //     for(int j = 0; j < cols+1; j++)
    //     {
    //         cout << mat[i][j] << "\t";
    //     }
    //     cout << endl;
    // }

    return mat;
}

//seq1, seq2, A=1, C=2, G=3, T=4, gap = 0, end = -1
void backtracing(int **mat, int loc_row, int loc_col, char *str1, char *str2, int rows[], int cols[], int step, bool show_results)
{
    int next[3][2] = {{0, -1}, {-1, 0}, {-1, -1}};

    if(mat[loc_row][loc_col] == 0)
    {
        if(show_results == true)
        {
            for(int i = step-1; i > 0; i --)
            {
                if(i != step-1)
                {
                    if(rows[i] == rows[i-1])
                    {
                        cout << '_';
                    }
                    else
                    {
                        cout << str1[rows[i]];
                    }
                }
                else
                {
                    cout << str1[rows[i]];
                }
            }
            cout << endl;

            for(int i = step-1; i > 0; i --)
            {
                if(i != step-1)
                {
                    if(rows[i] == rows[i-1] || cols[i] == cols[i-1])
                    {
                        cout << ' ';
                    }
                    else
                    {
                        if(str1[rows[i]] == str2[cols[i]])
                        {
                            cout << '|';
                        }
                        else
                        {
                            cout << 'x';
                        }
                    }
                }
                else
                {
                    if(str1[rows[i]] == str2[cols[i]])
                    {
                        cout << '|';
                    }
                    else
                    {
                        cout << 'x';
                    }
                }
            }
            cout << endl;

            for(int i = step-1; i > 0; i --)
            {
                if(i != step-1)
                {
                    if(cols[i] == cols[i-1])
                    {
                        cout << '_';
                    }
                    else
                    {
                        cout << str2[cols[i]];
                    }
                }
                else
                {
                    cout << str2[cols[i]];
                }
            }
            cout << endl;
            cout << endl;
        }

        return;

    }

    if(step == 0)
    {
        rows[step] = loc_row;
        cols[step] = loc_col;
        step ++;
    }

    int tx, ty;
    for(int k = 0; k < 3; k ++)
    {
        tx = loc_row + next[k][0];
        ty = loc_col + next[k][1];

        if(k == 0 || k == 1)
        {
            if(mat[tx][ty] != mat[loc_row][loc_col] + 3)
            {
                //cout << tx << '\t' << ty << endl;
                continue;
            }
        }
        else
        {
            if(mat[tx][ty] != mat[loc_row][loc_col] - 2 && mat[tx][ty] != mat[loc_row][loc_col] + 1)
            {
                continue;
            }
            if(mat[tx][ty] == mat[loc_row][loc_col] - 2 && str1[loc_row-1] != str2[loc_col-1])
            {
                continue;
            }
            if(mat[tx][ty] == mat[loc_row][loc_col] + 1 && str1[loc_row-1] == str2[loc_col-1])
            {
                continue;
            }

        }

        rows[step] = tx;
        cols[step] = ty;
        step ++;

        //cout << step << '\t' << rows[step-1] << '\t' << cols[step-1] << '\t' << endl;
        backtracing(mat, tx, ty, str1, str2, rows, cols, step, show_results);

        rows[step-1] = 0;
        cols[step-1] = 0;
        step --;
    }
    return;
}

int smith_w_alg(int **mat, int rows, int cols, char *str1, char *str2, bool show_results)
{
    //step 1, find the maximum value in the matrix
    int i, j, k;
    int *loc_rows, *loc_cols;
    int max = 0;

    for(i = 1; i < rows+1; i++)
    {
        for(j = 1; j < cols+1; j++)
        {
            max = max_value(max, mat[i][j]);
        }
    }

    //step 2, find the locations of the maximum value
    int count = 0;

    loc_rows = new int[rows];
    loc_cols = new int[cols];

    for(i = 1; i < rows+1; i++)
    {
        for(j = 1; j < cols+1; j++)
        {
            if(mat[i][j] == max)
            {
                loc_rows[count] = i;
                loc_cols[count] = j;
                count++;
            }
        }
    }

    int rows_list[400];
    int cols_list[400];

    //cout << count << '\t' << loc_rows[0] << '\t' << loc_cols[0] << '\t' << endl;

    for(k = 0; k < count; k ++)
    {
        for(int i=0; i<400; i++)
        {
            rows_list[i] = 0;
            cols_list[i] = 0;
        }
        // cout << k << endl;
        int step = 0;
        backtracing(mat, loc_rows[k], loc_cols[k], str1, str2, rows_list, cols_list, step, show_results);
    }
    for(int i = 0; i < rows; i ++)
    {
        delete[] mat[i];
    }
    delete[] mat;
    
    return max;

}

long get_genome_filesize(char* filename)
{
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

char** get_random_seqs(int num)
{
    int i, n;
    time_t t;

    int *list = new int[num*50];
    char **seq = new char*[num];
    char base[2];

    for(i = 0; i < num; i++)
    {
        seq[i] = new char[51];
    }

    srand((unsigned) time(&t));

    for( i = 0 ; i < num*50 ; i++ ) {
        list[i] = rand() % 4;
        //cout << list[i];
    }

    for(i = 0; i < num*50; i ++)
    {
        if(list[i] == 0)
            strcpy(base, "A");
        else if(list[i] == 1)
            strcpy(base, "C");
        else if(list[i] == 2)
            strcpy(base, "G");
        else if(list[i] == 3)
            strcpy(base, "T");
        
        int seq_num = i/50;
        int base_loc = i - seq_num*50;
        strcpy(&seq[seq_num][base_loc], base);

        if(i%50 == 0 && i != 0)
        {
            seq[seq_num-1][50] = '\0';
        }

        if(i == num-1)
        {
            seq[seq_num][50] = '\0';
        }

    }

    return seq;
}