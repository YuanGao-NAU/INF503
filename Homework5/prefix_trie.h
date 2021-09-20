#ifndef PREFIX_TRIE_H
#define PREFIX_TRIE_H

struct Node
{
    Node *A;
    Node *C;
    Node *G;
    Node *T;
};

class prefix_trie
{
    private:
        Node *root;
        int node_num;
        void delete_all_nodes(Node *root);

    public:
        prefix_trie();
        prefix_trie(char **queries, int k, int n);
        //bool traverse(char *genome, int G);
        prefix_trie(const prefix_trie &obj);
        ~prefix_trie();
        bool search(char *segment, int mismatch);
        int get_node_num();
};

#endif