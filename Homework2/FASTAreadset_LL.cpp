#include "FASTAreadset_LL.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

using namespace std;

void FASTAreadset_LL::init()
{
    this->head = NULL;
    //this->length = 0;
}

int FASTAreadset_LL::readset(char* filename)
{
    this->init();
    ifstream instream;
    instream.open(filename);
    if(!instream.is_open())
    {
        cout << "can not open the file \"" << filename << "\", please check the file name!" << endl;
        return -1; 
    }

    Node* temp = NULL;

    char drop[50];

    if(!instream.eof())
    {
        this->head = new Node;
        this->head->sequence = new char[51];
        instream >> drop;
        instream >> this->head->sequence;
        head->next = NULL;
        temp = head;
    }
    
    while(!instream.eof())
    {
       Node* node = new Node;
       node->sequence = new char[51];
       instream >> drop;
       instream >> node->sequence;
       temp->next = node;
       temp = node;
    }
    return 0;
}

FASTAreadset_LL::FASTAreadset_LL()
{
    this->init();
}

// FASTAreadset_LL::FASTAreadset_LL(char* filename)
// {
//     int ret = 0;
//     ret = this->readset(filename);
//     if(ret != 0)
//     {
//         this->init();
//     }
// }

FASTAreadset_LL::FASTAreadset_LL(const FASTAreadset_LL &obj)
{
    this->init();
    Node *temp1, *temp2;
    temp1 = obj.head;
    if(temp1 == NULL)
    {
        return;
    }

    this->head = new Node;
    temp2 = this->head;
    temp2->sequence = new char[51];
    strcpy(temp2->sequence, temp1->sequence);

    temp1 = temp1->next;
    
    while(temp1 != NULL)
    {
        temp2->next = new Node;
        temp2 = temp2->next; 
        temp2->sequence = new char[51];
        strcpy(temp2->sequence, temp1->sequence);
        temp1 = temp1->next;
    }
}

FASTAreadset_LL::~FASTAreadset_LL()
{
    Node *temp1, *temp2;
    temp1 = head;
    temp2 = head;
    while(temp1 != NULL)
    {
        delete[] temp1->sequence;
        temp1 = temp1->next;
        delete[] temp2;
        temp2 = temp1;
    }
    cout << "memory released!" << endl;
}

Node* FASTAreadset_LL::search_seq(char *seq)
{
    Node *temp;
    temp = head;
    while(temp != NULL)
    {
        if(strcmp(temp->sequence, seq) == 0)
        {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

FASTAreadset_LL::FASTAreadset_LL(char* filename, bool is_genome)
{

    if(is_genome == false)
    {
        int ret = 0;
        ret = this->readset(filename);
        if(ret != 0)
        {
            this->init();
        }
        return;
    }

    long size = get_genome_filesize(filename);

    int initial_size = 1000;
    char *temp;
    ifstream instream;

    char *genome;
    genome = new char[size];

    long length = 0;
    int len = 0;

    temp = new char[initial_size];

    instream.open(filename);
    instream.getline(temp, 1000);

    while(!instream.eof())
    {
        streampos oldpos = instream.tellg();
        instream.getline(temp, 1000);
        while(strlen(temp) >= initial_size)
        {
            instream.seekg(oldpos);
            delete[] temp;
            initial_size = 2*initial_size;
            temp = new char[initial_size];
            instream.getline(temp, 1000);
        }
        strcpy(&genome[length], temp);
        length += strlen(temp);
    }
    delete[] temp;

    len = strlen(genome);
    if(len < 50)
    {
        this->init();
    }
    this->head = new Node;
    this->head->sequence = new char[51];
    Node *node_temp = head;

    for(int i=0; i<len-50; i++)
    {
        memcpy(node_temp->sequence, &genome[i], 50);
        node_temp->sequence[50] = '\0';
        node_temp->next = new Node;
        node_temp = node_temp->next;
        node_temp->sequence = new char[51];
    }

    memcpy(node_temp->sequence, &genome[len-50], 50);
    node_temp->sequence[50] = '\0';
    node_temp->next = NULL;
}

long FASTAreadset_LL::get_genome_filesize(char* filename)
{
    struct stat stat_buf;
    int rc = stat(filename, &stat_buf);
    return rc == 0 ? stat_buf.st_size : -1;
}

void FASTAreadset_LL::print_seq_head(int n)
{

    if(this->head == NULL)
    {
        cout << "No reads detected!" << endl;
    }

    Node *temp;
    temp = head;

    for(int i=0; i<n; i++)
    {
        cout << temp->sequence << endl;
        temp = temp->next;
        if(temp == NULL)
            return;
    }
}

void FASTAreadset_LL::print_seq()
{
    if(this->head == NULL)
    {
        cout << "No reads detected!" << endl;
    }

    Node* temp = head;

    while(temp != NULL)
    {
        cout << temp->sequence << endl;
        temp = temp->next;
    }
}

Node* FASTAreadset_LL::get_chain()
{
    return this->head;
}

// long FASTAreadset_LL::get_length()
// {
//     this->length = 0;
//     Node *temp = this->head;
//     while(temp != NULL)
//     {
//         this->length ++;
//         temp = temp->next;
//     }
// }