#include "prefix_trie.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stack>

using namespace std;

prefix_trie::prefix_trie()
{
    this->root = NULL;
}

prefix_trie::prefix_trie(char **queries, int k, int n)
{
    if(queries == NULL)
    {
        this->root = NULL;
        return;
    }
    this->root = new Node;
    Node *temp = this->root;
    temp->A = temp->C = temp->G = temp->T = NULL;
    
    for(int i = 0; i < k; i ++)
    {
        for(int j = 0; j < n; j ++) 
        {
            // cout << "tree" << endl;
            // cout << queries[i][j] << endl;
            if(queries[i][j] == 'A')
            {
                if(temp->A == NULL)
                {
                    temp->A = new Node;
                    temp->A->A = temp->A->C = temp->A->G = temp->A->T = NULL;
                }
                temp = temp->A;
            }
            else if(queries[i][j] == 'C')
            {
                if(temp->C == NULL)
                {
                    temp->C = new Node;
                    temp->C->A = temp->C->C = temp->C->G = temp->C->T = NULL;
                }
                temp = temp->C;
            }
            else if(queries[i][j] == 'G')
            {
                if(temp->G == NULL)
                {
                    temp->G = new Node;
                    temp->G->A = temp->G->C = temp->G->G = temp->G->T = NULL;
                }
                temp = temp->G;
            }
            else if(queries[i][j] == 'T')
            {
                if(temp->T == NULL)
                {
                    temp->T = new Node;
                    temp->T->A = temp->T->C = temp->T->G = temp->T->T = NULL;
                }
                temp = temp->T;
            }
        }
        temp = this->root;
    }
}

prefix_trie::prefix_trie(const prefix_trie &obj)
{
    if(obj.root == NULL) {
        this->root = NULL;
        return;
    }

    stack<Node*> s1, s2;

    this->root = new Node;

    Node *temp1 = obj.root;
    Node *temp2 = this->root;

    while(temp1 != NULL) {
        if(temp1->A != NULL && temp2->A == NULL) {
            s1.push(temp1);
            s2.push(temp2);
            temp2->A = new Node;
            temp2 = temp2->A;
            temp1 = temp1->A;
        } else if(temp1->C != NULL && temp2->C == NULL) {
            s1.push(temp1);
            s2.push(temp2);
            temp2->C = new Node;
            temp2 = temp2->C;
            temp1 = temp1->C;
        } else if(temp1->G != NULL && temp2->G == NULL) {
            s1.push(temp1);
            s2.push(temp2);
            temp2->G = new Node;
            temp2 = temp2->G;
            temp1 = temp1->G;
        } else if(temp1->T != NULL && temp2->T == NULL) {
            s1.push(temp1);
            s2.push(temp2);
            temp2->T = new Node;
            temp2 = temp2->T;
            temp1 = temp1->T;
        } else {
            temp1 = s1.top();
            temp2 = s2.top();
            s1.pop();
            s2.pop();
        }
    }
}

void prefix_trie::delete_all_nodes(Node *root)
{
    stack<Node*> s;
    if(root == NULL) {
        return;
    }
    //Node *temp;
    if(root->A != NULL) {
        s.push(root->A);
    } 
    if(root->C != NULL) {
        s.push(root->C);
    } 
    if(root->G != NULL) {
        s.push(root->G);
    } 
    if(root->T != NULL) {
        s.push(root->T);
    }

    delete root;

    while(!s.empty()) {
        Node *temp = s.top();
        s.pop();
        if(temp->A != NULL) {
            s.push(temp->A);
        } 
        if(temp->C != NULL) {
            s.push(temp->C);
        } 
        if(temp->G != NULL) {
            s.push(temp->G);
        } 
        if(temp->T != NULL) {
            s.push(temp->T);
        }
        delete temp;
    }
}

prefix_trie::~prefix_trie()
{
    this->delete_all_nodes(this->root);
}

bool prefix_trie::search(char *segment, int mismatch) {
    stack<Node*> s1;
    stack<int> s2, s3;
    if(root == NULL) {
        cout << "root is NULL" << endl;
        return false;
    }

    int i = 0;
    int record = 0;

    if(root->A != NULL) {
        s1.push(root->A);
        if(segment[i] == 'A') {
            s2.push(0);
        } else {
            s2.push(1);
        }
        s3.push(i+1);
    } 
    if(root->C != NULL) {
        s1.push(root->C);
        if(segment[i] == 'C') {
            s2.push(0);
        } else {
            s2.push(1);
        }
        s3.push(i+1);
    } 
    if(root->G != NULL) {
        s1.push(root->G);
        if(segment[i] == 'G') {
            s2.push(0);
        } else {
            s2.push(1);
        }
        s3.push(i+1);
    } 
    if(root->T != NULL) {
        s1.push(root->T);
        if(segment[i] == 'T') {
            s2.push(0);
        } else {
            s2.push(1);
        }
        s3.push(i+1);
    }

    while(!s1.empty()) {
        Node *temp = s1.top();
        s1.pop();
        record = s2.top();                     //record the mismatch in each step
        s2.pop();
        int i = s3.top();                      //indicate which character we are comparing
        s3.pop();
        if(s1.size() == s2.size() && s2.size() == s3.size()) {
        if(record <= mismatch) {               //if record > mismatch, no need to explore the deeper nodes
            if(temp->A != NULL) {
                s1.push(temp->A);
                if(segment[i] == 'A') {
                    s2.push(0+record);
                } else {
                    s2.push(1+record);
                }
                s3.push(i+1);
            } 
            if(temp->C != NULL) {
                s1.push(temp->C);
                if(segment[i] == 'C') {
                    s2.push(0+record);
                } else {
                    s2.push(1+record);
                }
                s3.push(i+1);
            } 
            if(temp->G != NULL) {
                s1.push(temp->G);
                if(segment[i] == 'G') {
                    s2.push(0+record);
                } else {
                    s2.push(1+record);
                }
                s3.push(i+1);
            } 
            if(temp->T != NULL) {
                s1.push(temp->T);
                if(segment[i] == 'T') {
                    s2.push(0+record);
                } else {
                    s2.push(1+record);
                }
                s3.push(i+1);
            }
        }}

        if(temp->A == NULL && temp->C == NULL && temp->G == NULL && temp->T == NULL) {              //leaf node
            if(record <= mismatch) {
                return true;
            }
        }
    }
    return false;
    
}

int prefix_trie::get_node_num() {
    
    stack<Node*> s;
     if(root == NULL) {
        return 0;
    }
    int count = 0;
    //Node *temp;
    if(root->A != NULL) {
        s.push(root->A);
        count ++;
    } 
    if(root->C != NULL) {
        s.push(root->C);
        count ++;
    } 
    if(root->G != NULL) {
        s.push(root->G);
        count ++;
    } 
    if(root->T != NULL) {
        s.push(root->T);
        count ++;
    }

    while(!s.empty()) {
        Node *temp = s.top();
        s.pop();
        if(temp->A != NULL) {
            s.push(temp->A);
            count ++;
        } 
        if(temp->C != NULL) {
            s.push(temp->C);
            count ++;
        } 
        if(temp->G != NULL) {
            s.push(temp->G);
            count ++;
        } 
        if(temp->T != NULL) {
            s.push(temp->T);
            count ++;
        }
    }
    return count;
}