#ifndef SUFFIXTRIE_H
#define SUFFIXTRIE_H

struct Node{
    Node *A;
    Node *C;
    Node *G;
    Node *T;
    Node *DS;
};

class SuffixTrie {
    
    private:
        Node *root;

    public:
        SuffixTrie();
        SuffixTrie(char *sequence, int len);
        bool search(char *sequence, int len);
        void delete_all_nodes();
        int get_node_num();
        ~SuffixTrie();
};

#endif