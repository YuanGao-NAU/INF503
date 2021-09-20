#include "SuffixTrie.h"
#include <iostream>
#include <stdlib.h>
#include <fstream>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <stack>

using namespace std;

SuffixTrie::SuffixTrie() {
    this->root = NULL;
}

SuffixTrie::SuffixTrie(char *sequence, int len) {
    root = new Node;
    root->A = root->C = root->G = root->T = NULL;
    root->DS = new Node;
    root->DS->A = root->DS->C = root->DS->G = root->DS->T = root->DS->DS = NULL;
    Node *temp;
    char *tempStr = new char[len+1];
    for(int i = 0; i < strlen(sequence)-len+1; i ++) {
        for(int j = 0; j < len; j ++) {
            temp = root;
            strncpy(tempStr, &sequence[i+j], len-j);
            tempStr[len-j] = '\0';
            for(int k = 0; k < len-j; k ++) {
                if(tempStr[k] == 'A') {
                    if(temp->A == NULL) {
                        temp->A = new Node;
                        temp->A->A = temp->A->C = temp->A->G = temp->A->T = temp->A->DS = NULL;
                    }
                    temp = temp->A;
                    // temp->location=-1;
                } else if(tempStr[k] == 'C') {
                    if(temp->C == NULL) {
                        temp->C = new Node;
                        temp->C->A = temp->C->C = temp->C->G = temp->C->T = temp->C->DS = NULL;
                    }
                    temp = temp->C;
                    // temp->location=-1;
                } else if(tempStr[k] == 'G') {
                    if(temp->G == NULL) {
                        temp->G = new Node;
                        temp->G->A = temp->G->C = temp->G->G = temp->G->T = temp->G->DS = NULL;
                    }
                    temp = temp->G;
                    // temp->location=-1;
                } else if(tempStr[k] == 'T') {
                    if(temp->T == NULL) {
                        temp->T = new Node;
                        temp->T->A = temp->T->C = temp->T->G = temp->T->T = temp->T->DS = NULL;
                    }
                    temp = temp->T;
                    // temp->location=-1;
                }
            }
            temp->DS = new Node;
            temp->DS->A = temp->DS->C = temp->DS->G = temp->DS->T = temp->DS->DS = NULL;
        }
    }
    delete[] tempStr;
}

bool SuffixTrie::search(char *sequence, int len) {
    Node *temp = root;
    for(int i = 0; i < len; i ++) {
        if(sequence[i] == 'A') {
            if(temp->A != NULL) {
                temp = temp->A;
            } else {
                return false;
            }
        } else if(sequence[i] == 'C') {
            if(temp->C != NULL) {
                temp = temp->C;
            } else {
                return false;
            }
        } else if(sequence[i] == 'G') {
            if(temp->G != NULL) {
                temp = temp->G;
            } else {
                return false;
            }
        } else if(sequence[i] == 'T') {
            if(temp->T != NULL) {
                temp = temp->T;
            } else {
                return false;
            }
        }
    }
    return true;
}

SuffixTrie::~SuffixTrie() {
    delete_all_nodes();
}

void SuffixTrie::delete_all_nodes()
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
    if(root->DS != NULL) {
        delete root->DS;
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
        if(temp->DS != NULL) {
            delete temp->DS;
        }
        delete temp;
    }
}

int SuffixTrie::get_node_num() {
    
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
    if(root->DS != NULL) {
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
        if(temp->DS != NULL) {
            count ++;
        }
    }
    return count;
}